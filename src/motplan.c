#include"allfunc.h"

Robot *robotlist = NULL; // 全局机器人链表头指针

/*******************************************************
* 碰撞检测函数
*******************************************************/
int checkCollision(int x, int y, int exclude_id) {
    int left, right, top, bottom, i;
    Robot* current;

    Robot* r = robotlist;
    int is_charging = 0;

    int dx, dy;

    left = x - ROBOT_SIZE/2;
    right = x + ROBOT_SIZE/2;
    top = y - ROBOT_SIZE/2;
    bottom = y + ROBOT_SIZE/2;

    if(left<0 || right>SCREEN_WIDTH || top<0 || bottom>SCREEN_HEIGHT)
        return 1;

    /* 障碍物检测（排除充电站当机器人处于充电状态时）*/
    while(r) {
        if(r->id == exclude_id && r->state == 2) {
            is_charging = 1;
            break;
        }
        r = r->next;
    }

    for(i=0; i<6; i++) {
        if(is_charging && i == 4) continue; 
        
        if(right>obs[i].x1 && left<obs[i].x2 && 
           bottom>obs[i].y1 && top<obs[i].y2)
            return 1;

        if(right>obs[i].x1 && left<obs[i].x2 && 
           bottom>obs[i].y1 && top<obs[i].y2)
            return 1;
    }

    current = robotlist;
    while(current) {
        if(current->id != exclude_id) {
            dx = abs(current->x - x);
            dy = abs(current->y - y);
            if(dx<ROBOT_SIZE && dy<ROBOT_SIZE) return 1;
        }
        current = current->next;
    }
    return 0;
}

/*******************************************************
* 力场计算函数（使用宏定义参数）
*******************************************************/
void calculateForces(Robot* robot, float* dx, float* dy) {
    float fx, fy, ftx, fty, target_dist, att_factor;
    int i, near_x, near_y;
    Robot* other;

    int charge_x, charge_y;
    float rep_factor, social_factor;
    float obs_dist, charge_dist, other_dist;
    float length;
    
    fx = (float)robot->x;
    fy = (float)robot->y;
    ftx = (float)robot->tx;
    fty = (float)robot->ty;
    *dx = *dy = 0.0f;

    /* 改进的目标引力计算 */
    target_dist = distance(robot->x, robot->y, robot->tx, robot->ty);
    if(target_dist < TARGET_RADIUS) {
        // 进入目标区域后停止引力计算
        *dx = *dy = 0.0f;
    } else {
        att_factor = fminf(target_dist/200.0f, 1.0f);
        *dx += (ftx - fx) * ATTRACT_GAIN * att_factor;
        *dy += (fty - fy) * ATTRACT_GAIN * att_factor;
    }

    /* 充电站特殊处理 */
    if(robot->state == 1) { // 前往充电状态
        charge_x = (obs[4].x1 + obs[4].x2)/2;
        charge_y = (obs[4].y1 + obs[4].y2)/2;
        charge_dist = distance(robot->x, robot->y, charge_x, charge_y);
    }

    /* 障碍物斥力 */
    for(i=0; i<6; i++) {
        if(i == 4) continue;

        near_x = (robot->x<obs[i].x1) ? obs[i].x1 : 
                (robot->x>obs[i].x2) ? obs[i].x2 : robot->x;
        near_y = (robot->y<obs[i].y1) ? obs[i].y1 : 
                (robot->y>obs[i].y2) ? obs[i].y2 : robot->y;
        
        obs_dist = distance(robot->x, robot->y, near_x, near_y);
        if(obs_dist < REPULSE_RANGE) {
            rep_factor = 1.0f - (obs_dist/REPULSE_RANGE);
            *dx += (fx-(float)near_x)*REPULSE_GAIN*rep_factor/obs_dist;
            *dy += (fy-(float)near_y)*REPULSE_GAIN*rep_factor/obs_dist;
        }
    }

    /* 机器人间斥力 */
    other = robotlist;
    while(other) {
        if(other->id!=robot->id && other->state!=2) {
            other_dist = distance(robot->x, robot->y, other->x, other->y);
            if(other_dist < REPULSE_RANGE) {
                social_factor = 1.0f - (other_dist/REPULSE_RANGE);
                *dx += (fx-(float)other->x)*SOCIAL_GAIN*social_factor/other_dist;
                *dy += (fy-(float)other->y)*SOCIAL_GAIN*social_factor/other_dist;
            }
        }
        other = other->next;
    }

    length = sqrt(*dx**dx + *dy**dy);
    if(length > 0.001f) {
        *dx /= length;
        *dy /= length;
    }
}

/*******************************************************
* 路径平滑与防循环处理
*******************************************************/
void smoothPath(Robot* robot, float* dx, float* dy) {
    int i;
    float avg_dx=0.0f, avg_dy=0.0f, length;

    float angle = 0;
    float new_dx = 0;
    float new_dy = 0;

    robot->hist_dx[robot->hist_index] = (int)(*dx*100.0f);
    robot->hist_dy[robot->hist_index] = (int)(*dy*100.0f);
    robot->hist_index = (robot->hist_index+1)%HISTORY_SIZE;

    for(i=0; i<HISTORY_SIZE; i++) {
        avg_dx += (float)robot->hist_dx[i]/100.0f;
        avg_dy += (float)robot->hist_dy[i]/100.0f;
    }
    avg_dx /= HISTORY_SIZE;
    avg_dy /= HISTORY_SIZE;

    *dx = SMOOTH_FACTOR*avg_dx + (1-SMOOTH_FACTOR)**dx;
    *dy = SMOOTH_FACTOR*avg_dy + (1-SMOOTH_FACTOR)**dy;

    length = sqrt(*dx**dx + *dy**dy);
    if(length > 0.001f) {
        *dx /= length;
        *dy /= length;
    }

    /* 防循环扰动 */
    if(robot->escape_count > 0) {
        angle = (rand()%100 - 50)*RANDOM_ANGLE;
        new_dx = *dx*cos(angle) - *dy*sin(angle);
        new_dy = *dx*sin(angle) + *dy*cos(angle);
        *dx = new_dx;
        *dy = new_dy;
    }
}

/*******************************************************
* 移动控制与防循环触发
*******************************************************/
void moveTowards(Robot* robot, float dx, float dy) {
    float step=STEP_BASE, new_x, new_y;
    int i, final_x, final_y, try_x, try_y;
    float target_dist;

    /* 防循环检测 */
    if(robot->x == robot->prev_x && robot->y == robot->prev_y) {
        if(++robot->same_pos_count > ESCAPE_ATTEMPTS) {
            robot->escape_count = ESCAPE_ATTEMPTS*2;
            robot->tx = rand()%SCREEN_WIDTH;  // 强制改变目标
            robot->ty = rand()%SCREEN_HEIGHT;
        }
    } else {
        robot->same_pos_count = 0;
    }

    /* 到达目标检测 */
    target_dist = distance(robot->x, robot->y, robot->tx, robot->ty);
    if(target_dist <= TARGET_RADIUS) {
        robot->x = robot->tx; // 直接对齐目标
        robot->y = robot->ty;
        fprintf(robot->logfile, "%d,%d\n", robot->x, robot->y);
        return;
    }

    /* 近目标阻尼 */
    if(target_dist < 100.0f) {
        step *= (1.0f - DAMPING_FACTOR*(100.0f - target_dist)/100.0f);
    }

    /* 步长调整 */
    if(robot->state==1) step *= 1.2f;
    for(i=1; i<=3; i++) {
        new_x = (float)robot->x + dx*step*i;
        new_y = (float)robot->y + dy*step*i;
        if(checkCollision((int)new_x, (int)new_y, robot->id)) {
            step *= 0.7f;
            break;
        }
    }

    new_x = (float)robot->x + dx*step;
    new_y = (float)robot->y + dy*step;
    final_x = (int)round(new_x);
    final_y = (int)round(new_y);

    if(!checkCollision(final_x, final_y, robot->id)) {
        robot->prev_x = robot->x;
        robot->prev_y = robot->y;
        robot->x = final_x;
        robot->y = final_y;
        robot->battery -= 0.1f;
        if(robot->escape_count > 0) robot->escape_count--;
    } else {
        try_x = robot->x + (int)(dy*step);
        try_y = robot->y - (int)(dx*step);
        if(!checkCollision(try_x, try_y, robot->id)) {
            robot->x = try_x;
            robot->y = try_y;
        } else {
            try_x = robot->x - (int)(dy*step);
            try_y = robot->y + (int)(dx*step);
            if(!checkCollision(try_x, try_y, robot->id)) {
                robot->x = try_x;
                robot->y = try_y;
            }
        }
        robot->escape_count++;
    }

    bar1(robot->prev_x-25,robot->prev_y-25,robot->prev_x+25,robot->prev_y+25,0XFFFF);
    draw_robot(robot->x,robot->y,0);

    fprintf(robot->logfile, "%d,%d\n", robot->x, robot->y);
}

/*******************************************************
* 充电处理函数
*******************************************************/
void handleCharging(Robot* robot) {
    int charge_x = (obs[4].x1 + obs[4].x2)/2;
    int charge_y = (obs[4].y1 + obs[4].y2)/2;
    float charge_dist = distance(robot->x, robot->y, charge_x, charge_y);

    switch(robot->state) {
        case 1: // 前往充电站
            if(charge_dist <= CHARGE_RADIUS) {
                robot->state = 2;
                robot->x = charge_x; // 强制对齐充电站中心
                robot->y = charge_y;
            }
            break;
        case 2: // 充电中
            robot->battery += CHARGE_SPEED;
            if(robot->battery >= 100.0f) {
                robot->battery = 100.0f;
                robot->state = 0;
                robot->tx = robot->orig_tx;
                robot->ty = robot->orig_ty;
            }
            break;
        case 0:
            if(robot->battery < CHARGE_POWER) {
                robot->state = 1;
                robot->orig_tx = robot->tx;
                robot->orig_ty = robot->ty;
                robot->tx = charge_x;
                robot->ty = charge_y;
            }
    }
}

/*******************************************************
* 主循环（含自动终止条件）
*******************************************************/
void mainLoop() {
    int steps=0, idle_steps=0, all_reached;
    int any_moved=0, reached_count=0;
    int prev_x=0, prev_y=0;
    float dx, dy;
    Robot* current;

    while(steps++ < MAX_STEPS) {
        current = robotlist;

        while(current) {
            prev_x=current->x;
            prev_y=current->y;
            
            if(current->state != 2) {
                calculateForces(current, &dx, &dy);
                smoothPath(current, &dx, &dy);
                moveTowards(current, dx, dy);
            }
            handleCharging(current);

            if(current->x!=prev_x || current->y!=prev_y) any_moved=1;
            if(current->state==0 && 
               distance(current->x, current->y, current->tx, current->ty)<STEP_BASE)
                reached_count++;

            current = current->next;
        }

        all_reached = (reached_count==MAX_ROBOTS);
        if(all_reached || (any_moved==0 && ++idle_steps>IDLE_LIMIT))
            break;

        delay(100);
    }
}

/*******************************************************
* 辅助函数
*******************************************************/
float distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((float)(x2-x1),2) + pow((float)(y2-y1),2));
}

float fminf(float a,float b){
    return a<b?a:b;
}

float fmaxf(float a,float b){
    return a>b?a:b;
}

double round(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
