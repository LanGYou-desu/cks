#include"allfunc.h"

Robot *robotlist = NULL; // 全局机器人链表头指针

/*******************************************************
* 碰撞检测函数
*******************************************************/
int checkCollision(int x, int y, int exclude_id) 
{
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
    {
        return 1;
    }

    /* 障碍物检测（排除充电站当机器人处于充电状态时）*/
    while(r) 
    {
        if(r->id == exclude_id && r->state == 2) 
        {
            is_charging = 1;
            break;
        }
        r = r->next;
    }

    for(i=0; i<6; i++) 
    {
        if(is_charging && i == 4) 
        {
            continue; 
        }
        
        if(right>obs[i].x1 && left<obs[i].x2 && bottom>obs[i].y1 && top<obs[i].y2)
        {
            return 1;
        }   

        if(right>obs[i].x1 && left<obs[i].x2 && bottom>obs[i].y1 && top<obs[i].y2)
        {
            return 1;
        }    
    }

    current = robotlist;
    while(current) 
    {
        if(current->id != exclude_id) 
        {
            dx = abs(current->x - x);
            dy = abs(current->y - y);
            if(dx<ROBOT_SIZE && dy<ROBOT_SIZE) 
            {
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}

/*******************************************************
* 力场计算函数
*******************************************************/
void calculateForces(Robot* robot, float* dx, float* dy) 
{
    float fx, fy, ftx, fty, target_dist, att_factor, rep_factor, social_factor;
    int i, near_x, near_y;
    Robot* other;

    int charge_x, charge_y;
    float obs_dist, charge_dist, other_dist, border_dist;
    float length;
    
    fx = (float)robot->x;
    fy = (float)robot->y;
    ftx = (float)robot->tx;
    fty = (float)robot->ty;
    *dx = *dy = 0.0f;

    /* 改进的目标引力计算 */
    target_dist = distance(robot->x, robot->y, robot->tx, robot->ty);
    if(target_dist < TARGET_RADIUS) 
    {
        // 进入目标区域后停止引力计算
        *dx = *dy = 0.0f;
    } 
    else 
    {
        att_factor = fminf(target_dist/200.0f, 1.0f);
        *dx += (ftx - fx) * ATTRACT_GAIN * att_factor;
        *dy += (fty - fy) * ATTRACT_GAIN * att_factor;
    }

    /* 出生点和充电站附近位置修正 */
    if(robot->y>=610&&robot->tx<512)
    {
        *dx=*dx-0.1f;
        *dy=*dy+0.1f;
    }
    else if(robot->y>=610&&robot->tx>512)
    {
        *dx=*dx+0.1f;
        *dy=*dy+0.1f;
    }
    else if(robot->y<=185&&robot->tx<512)
    {
        *dx=*dx-0.1f;
        *dy=*dy-0.1f;
    }
    else if(robot->y<=185&&robot->tx>512)
    {
        *dx=*dx+0.1f;
        *dy=*dy-0.1f;
    }

    /* 障碍物斥力 */
    for(i=0; i<6; i++) 
    {
        if(robot->state==1 && i==4) 
        {
            continue; // 前往充电时忽略充电站
        }
        
        near_x = (robot->x<obs[i].x1) ? obs[i].x1 : (robot->x>obs[i].x2) ? obs[i].x2 : robot->x;
        near_y = (robot->y<obs[i].y1) ? obs[i].y1 : (robot->y>obs[i].y2) ? obs[i].y2 : robot->y;
        
        obs_dist = distance(robot->x, robot->y, near_x, near_y);
        if(obs_dist < REPULSE_RANGE) 
        {
            rep_factor = 1.0 - (obs_dist/REPULSE_RANGE);
            *dx += (fx-(double)near_x)*REPULSE_GAIN*rep_factor/obs_dist;
            *dy += (fy-(double)near_y)*REPULSE_GAIN*rep_factor/obs_dist;
        }
    }

    // 左边界斥力
    if(robot->x < BORDER_RANGE) 
    {
        border_dist = (double)robot->x;
        rep_factor = 1.0 - (border_dist/BORDER_RANGE);
        *dx += BORDER_REPULSE_GAIN * rep_factor;
    }
    // 右边界斥力
    if(robot->x > SCREEN_WIDTH - BORDER_RANGE) 
    {
        border_dist = (double)(SCREEN_WIDTH - robot->x);
        rep_factor = 1.0 - (border_dist/BORDER_RANGE);
        *dx -= BORDER_REPULSE_GAIN * rep_factor;
    }
    // 上边界斥力
    if(robot->y < BORDER_RANGE) 
    {
        border_dist = (double)robot->y;
        rep_factor = 1.0 - (border_dist/BORDER_RANGE);
        *dy += BORDER_REPULSE_GAIN * rep_factor;
    }
    // 下边界斥力
    if(robot->y > SCREEN_HEIGHT - BORDER_RANGE) 
    {
        border_dist = (double)(SCREEN_HEIGHT - robot->y);
        rep_factor = 1.0 - (border_dist/BORDER_RANGE);
        *dy -= BORDER_REPULSE_GAIN * rep_factor;
    }

    /* 机器人间斥力 */
    other = robotlist;
    while(other) 
    {
        if(other->id!=robot->id && other->state!=2) 
        {
            other_dist = distance(robot->x, robot->y, other->x, other->y);
            if(other_dist < REPULSE_RANGE) 
            {
                social_factor = 1.0f - (other_dist/REPULSE_RANGE);
                *dx += (fx-(float)other->x)*SOCIAL_GAIN*social_factor/other_dist;
                *dy += (fy-(float)other->y)*SOCIAL_GAIN*social_factor/other_dist;
            }
        }
        other = other->next;
    }

    length = sqrt(*dx**dx + *dy**dy);
    if(length > 0.001f) 
    {
        *dx /= length;
        *dy /= length;
    }
}

/*******************************************************
* 路径平滑与防循环处理
*******************************************************/
void smoothPath(Robot* robot, float* dx, float* dy) 
{
    int i;
    float avg_dx=0.0f, avg_dy=0.0f, length;

    float angle = 0;
    float new_dx = 0;
    float new_dy = 0;

    robot->hist_dx[robot->hist_index] = (int)(*dx*100.0f);
    robot->hist_dy[robot->hist_index] = (int)(*dy*100.0f);
    robot->hist_index = (robot->hist_index+1)%HISTORY_SIZE;

    for(i=0; i<HISTORY_SIZE; i++) 
    {
        avg_dx += (float)robot->hist_dx[i]/100.0f;
        avg_dy += (float)robot->hist_dy[i]/100.0f;
    }
    avg_dx /= HISTORY_SIZE;
    avg_dy /= HISTORY_SIZE;

    *dx = SMOOTH_FACTOR*avg_dx + (1-SMOOTH_FACTOR)**dx;
    *dy = SMOOTH_FACTOR*avg_dy + (1-SMOOTH_FACTOR)**dy;

    length = sqrt(*dx**dx + *dy**dy);
    if(length > 0.001f) 
    {
        *dx /= length;
        *dy /= length;
    }

    /* 防循环扰动 */
    if(robot->escape_count > 0) 
    {
        angle = (rand()%100 - 50)*RANDOM_ANGLE;
        new_dx = *dx*cos(angle) - *dy*sin(angle);
        new_dy = *dx*sin(angle) + *dy*cos(angle);
        *dx = new_dx;
        *dy = new_dy;
    }
}

/* 瞬移条件判断 */
int shouldTeleport(Robot* robot) 
{
    int charge_x, charge_y;
    // 充电目标特殊处理
    if(robot->state == 1) 
    {
        charge_x = (obs[4].x1 + obs[4].x2)/2;
        charge_y = (obs[4].y1 + obs[4].y2)/2;
        return distance(robot->x, robot->y, charge_x, charge_y) <= CHARGE_RADIUS;
    }
    // 普通目标判断
    return distance(robot->x, robot->y, robot->tx, robot->ty) <= TARGET_RADIUS;
}

/*******************************************************
* 移动控制与防循环触发
*******************************************************/
void moveTowards(Robot* robot, float dx, float dy) 
{
    float step=STEP_BASE, new_x, new_y;
    int i, final_x, final_y, try_x, try_y;
    float target_dist;
    double predict_x, predict_y;
    int valid;

    target_dist = distance(robot->x, robot->y, robot->tx, robot->ty);
    /* 到达检测（包含充电站特殊处理）*/
    if(target_dist <= TARGET_RADIUS || (robot->state == 1 && target_dist <= CHARGE_RADIUS)) 
    {
        robot->x = robot->tx; // 对齐精确坐标
        robot->y = robot->ty;
        robot->reached = 1;   // 标记到达状态
        return;
    }

    /* 瞬移检测（增加障碍物检查）*/
    if(shouldTeleport(robot)) 
    {
        valid = 1;
        // 瞬移前进行碰撞检测
        if(robot->state == 1) 
        {
            valid = !checkCollision((obs[4].x1+obs[4].x2)/2, (obs[4].y1+obs[4].y2)/2, robot->id);
        } 
        else 
        {
            valid = !checkCollision(robot->tx, robot->ty, robot->id);
        }
        
        if(valid) 
        {
            /* 瞬移逻辑 */
            if(shouldTeleport(robot))
             {
                if(robot->state == 1) 
                {
                    // 对齐充电站中心坐标
                    robot->x = (obs[4].x1 + obs[4].x2)/2 + 50;
                    robot->y = (obs[4].y1 + obs[4].y2)/2;
                } 
                else 
                {
                    // 普通目标直接传送
                    robot->prev_x = robot->x; 
                    robot->prev_y = robot->y;
                    robot->x = robot->tx;
                    robot->y = robot->ty;
                }
                robot->reached = 1; // 标记到达状态
                return; // 跳过后续移动逻辑
            }   
        }
        // 如果瞬移位置有障碍则继续正常移动
    }

    /* 防循环检测 */
    if(robot->x == robot->prev_x && robot->y == robot->prev_y) 
    {
        if(++robot->same_pos_count > ESCAPE_ATTEMPTS) 
        {
            robot->escape_count = ESCAPE_ATTEMPTS*2;
            robot->tx = rand()%SCREEN_WIDTH;  // 强制改变目标
            robot->ty = rand()%SCREEN_HEIGHT;
        }
    } 
    else 
    {
        robot->same_pos_count = 0;
    }

    /* 近目标阻尼 */
    if(target_dist < 100.0f) 
    {
        step *= (1.0f - DAMPING_FACTOR*(100.0f - target_dist)/100.0f);
    }

    /* 步长调整 */
    if(robot->state==1) 
    {
        step *= 1.2f;
    }
    /* 路径预测 */
    for(i=1; i<=5; i++) 
    { 
        predict_x = robot->x + dx*step*i;
        predict_y = robot->y + dy*step*i;
        if(checkCollision((int)predict_x, (int)predict_y, robot->id)) 
        {
            // 增强减速幅度
            step *= 0.6; 
            // 增加侧向力扰动
            dx += (rand()%100 - 50)*0.01;
            dy += (rand()%100 - 50)*0.01;
            break;
        }
    }

    new_x = (float)robot->x + dx*step;
    new_y = (float)robot->y + dy*step;
    final_x = (int)round(new_x);
    final_y = (int)round(new_y);

    if(!checkCollision(final_x, final_y, robot->id)) 
    {
        robot->prev_x = robot->x;
        robot->prev_y = robot->y;
        robot->x = final_x;
        robot->y = final_y;
        robot->battery -= STEP_POWER;
        if(robot->escape_count > 0) 
        {
            robot->escape_count--;
        }
    } 
    else 
    {
        try_x = robot->x + (int)(dy*step);
        try_y = robot->y - (int)(dx*step);
        if(!checkCollision(try_x, try_y, robot->id)) 
        {
            robot->x = try_x;
            robot->y = try_y;
        } 
        else 
        {
            try_x = robot->x - (int)(dy*step);
            try_y = robot->y + (int)(dx*step);
            if(!checkCollision(try_x, try_y, robot->id))
            {
                robot->x = try_x;
                robot->y = try_y;
            }
        }
        robot->escape_count++;
    }
}

/*******************************************************
* 充电处理函数
*******************************************************/
void handleCharging(Robot* robot) 
{
    int charge_x = (obs[4].x1 + obs[4].x2)/2;
    int charge_y = (obs[4].y1 + obs[4].y2)/2 + 55;
    float charge_dist = distance(robot->x, robot->y, charge_x, charge_y);

    /* 已到达机器人不处理充电逻辑 */
    if(robot->reached) 
    {
        return;
    }

    switch(robot->state) 
    {
        case 1: // 前往充电站
            if(charge_dist <= CHARGE_RADIUS) 
            {
                robot->state = 2;
                robot->x = charge_x; // 强制对齐充电站中心
                robot->y = charge_y;
            }
            break;

        case 2: // 充电中
            robot->battery += CHARGE_SPEED;
            if(robot->battery >= 100.0f) 
            {
                robot->battery = 100.0f;
                robot->state = 0;
                robot->tx = robot->orig_tx;
                robot->ty = robot->orig_ty;
            }
            break;

        case 0:
            if(robot->battery < CHARGE_POWER) 
            {
                robot->state = 1;
                robot->orig_tx = robot->tx;
                robot->orig_ty = robot->ty;
                robot->tx = charge_x;
                robot->ty = charge_y;
            }
    }

    if(robot->state == 2 && robot->battery >= 100.0) 
    {
        robot->reached = 0; // 恢复可移动状态
    }
}

/*******************************************************
* 主循环
*******************************************************/
void mainLoop(int robonum) 
{
    int steps=0, idle_steps=0, all_reached;
    int any_moved=0, reached_count=0;
    int prev_x=0, prev_y=0;
    float dx, dy;
    Robot* current;
    Robot* r;

    while(steps++ < MAX_STEPS && !allRobotsReached()) 
    {
        current = robotlist;
        any_moved = 0;  // 重置移动标志
        reached_count = 0;

        while(current) 
        {
            prev_x = current->x;
            prev_y = current->y;
            
            /* 移动逻辑 */
            if(current->state != 2) 
            {
                calculateForces(current, &dx, &dy);
                smoothPath(current, &dx, &dy);
                moveTowards(current, dx, dy);
            }
            handleCharging(current);

            /* 记录每个时间步的位置 */
            fprintf(current->logfile, "%d,%d,%d\n", current->x, current->y, current->cargo_type);
            fflush(current->logfile); // 确保日志文件及时写入

            bar1(current->prev_x-25,current->prev_y-25,current->prev_x+25,current->prev_y+25,0XFFFF);
            draw_robot(current->x,current->y,current->cargo_type);

            /* 状态检测 */
            if(current->x != prev_x || current->y != prev_y) 
            {
                any_moved = 1;
            }
            if(current->state == 0 && distance(current->x, current->y, current->tx, current->ty) < STEP_BASE) 
            {
                current->x = current->tx;
                current->y = current->ty;
                current->reached = 1;
                reached_count++;
            }
            
            current = current->next;
        }

        /* 终止条件判断 */
        all_reached = (reached_count == robonum);
        if(all_reached || (any_moved == 0 && ++idle_steps > IDLE_LIMIT))
        {
            // 在break前增加最后一次全体记录
            r = robotlist;
            while(r) 
            {
                r->x=r->tx;
                r->y=r->ty;
                fprintf(r->logfile, "%d,%d,%d\n", r->x, r->y, r->cargo_type);
                fflush(r->logfile); // 确保日志文件及时写入

                bar1(r->prev_x-25,r->prev_y-25,r->prev_x+25,r->prev_y+25,0XFFFF);
                draw_robot(r->x,r->y,r->cargo_type);
                r = r->next;
            }
            all_reach();
            break;
        }
        delay(1);
    }

    /* 最终位置确认写入 */
    current = robotlist;
    while(current) 
    {
        current->x=current->tx;
        current->y=current->ty;

        bar1(current->prev_x-25,current->prev_y-25,current->prev_x+25,current->prev_y+25,0XFFFF);
        draw_robot(current->x,current->y,0);

        fprintf(current->logfile, "%d,%d,%d\n", current->x, current->y, current->cargo_type);
        // 确保即使崩溃也记录最终状态
        fflush(current->logfile); 
        current = current->next;
    }
}

/*******************************************************
* 所有机器人到达目标处理
*******************************************************/
void all_reach() 
{
    Robot* current = robotlist;
    while(current) 
    {
        /* 重置状态 */
        current->reached = 0;
        current->state = 0;
        
        current = current->next;
    }
}

/*******************************************************
* 全局状态检查函数 
*******************************************************/
int allRobotsReached() 
{
    Robot* current = robotlist;
    while(current) 
    {
        if(!current->reached) return 0;
        current = current->next;
    }
    return 1;
}

/*******************************************************
* 辅助函数
*******************************************************/
float distance(int x1, int y1, int x2, int y2) 
{
    return sqrt(pow((float)(x2-x1),2) + pow((float)(y2-y1),2));
}

float fminf(float a,float b)
{
    return a<b?a:b;
}

float fmaxf(float a,float b)
{
    return a>b?a:b;
}

double round(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
