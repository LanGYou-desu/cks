#include"allfunc.h"

Robot* robot_list = NULL;   // 机器人链表头

float fmaxf(float a, float b) {
    return (a > b) ? a : b;
}

float fminf(float a, float b) {
    return (a < b) ? a : b;
}

/*******************************************************
 * 函数名称：calc_distance
 * 功能：计算两点间欧氏距离（浮点精度）
 *******************************************************/
float calc_distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*******************************************************
 * 函数名称：check_collision
 * 功能：检测移动后的碰撞
 * 参数：dx,dy - 计划移动量
 * 返回：1-碰撞 0-安全
 *******************************************************/
int check_collision(Robot* bot, int dx, int dy) {
    int i;

    int bot_left;
    int bot_right;
    int bot_top;
    int bot_bottom;

    int obs_left;
    int obs_right;
    int obs_top;
    int obs_bottom;

    // 计算新位置
    int new_x = bot->x + dx;
    int new_y = bot->y + dy;

    Robot* p = robot_list;
    float dist;

    /* 地图边界检测 */
    if(new_x < ROBOT_SIZE/2 || new_x > SCREEN_WIDTH - ROBOT_SIZE/2 ||
       new_y < ROBOT_SIZE/2 || new_y > SCREEN_HEIGHT - ROBOT_SIZE/2) {
        return 1;
    }

    /* 障碍物碰撞检测（AABB算法） */
    for(i=0; i<6; i++) {
        // 计算机器人新边界
        bot_left = new_x - ROBOT_SIZE/2;
        bot_right = new_x + ROBOT_SIZE/2;
        bot_top = new_y - ROBOT_SIZE/2;
        bot_bottom = new_y + ROBOT_SIZE/2;

        // 障碍物边界
        obs_left = obs[i].x1;
        obs_right = obs[i].x2;
        obs_top = obs[i].y1;
        obs_bottom = obs[i].y2;

        // 检测重叠
        if(bot_left < obs_right && 
           bot_right > obs_left &&
           bot_top < obs_bottom &&
           bot_bottom > obs_top) {
            return 1;
        }
    }

    /* 其他机器人碰撞检测 */
    p = robot_list;
    while(p) {
        if(p != bot) {
            // 计算中心点间距
            dist = calc_distance(new_x, new_y, p->x, p->y);
            if(dist < ROBOT_SIZE) {
                return 1;
            }
        }
        p = p->next;
    }

    return 0;
}

/*******************************************************
 * 函数名称：path_adjust
 * 功能：路径修正（避障核心算法）
 * 参数：dx,dy - 输出调整后的移动量
 *******************************************************/
void path_adjust(Robot* bot, int* dx, int* dy) {
    int i;
    float repel_x = 0, repel_y = 0;
    int base_step = STEP_BASE;
    float dir_x = 0, dir_y = 0;
    float dist, force;
    int obs_cx, obs_cy;
    float vec_x, vec_y;
    float final_dir_x, final_dir_y;
    float length;

    // 计算目标方向
    if(bot->tx != bot->x || bot->ty != bot->y) {
        dist = calc_distance(bot->x, bot->y, bot->tx, bot->ty);
        dir_x = (bot->tx - bot->x) / dist;
        dir_y = (bot->ty - bot->y) / dist;
    }

    // 障碍物排斥力
    for(i=0; i<6; i++) {
        // 障碍物中心
        obs_cx = (obs[i].x1 + obs[i].x2)/2;
        obs_cy = (obs[i].y1 + obs[i].y2)/2;
        
        // 到障碍物的向量
        vec_x = bot->x - obs_cx;
        vec_y = bot->y - obs_cy;
        dist = calc_distance(bot->x, bot->y, obs_cx, obs_cy);
        
        // 在100像素内产生排斥力
        if(dist < 100.0f) {
            force = (100.0f - dist) / 100.0f;
            repel_x += vec_x * force * 0.5f;
            repel_y += vec_y * force * 0.5f;
        }
    }

    // 合成方向向量
    final_dir_x = dir_x * base_step + repel_x;
    final_dir_y = dir_y * base_step + repel_y;
    
    // 归一化处理
    length = sqrt(final_dir_x*final_dir_x + final_dir_y*final_dir_y);
    if(length > 0) {
        final_dir_x /= length;
        final_dir_y /= length;
    }

    // 转换为整数步长
    *dx = (int)(final_dir_x * base_step);
    *dy = (int)(final_dir_y * base_step);
}

/*******************************************************
 * 函数名称：robot_update
 * 功能：更新单个机器人状态
 *******************************************************/
void robot_update(Robot* bot) {
    int dx = 0, dy = 0;

    /* 状态预处理 */
    switch(bot->state) {
        case 0: // 正常工作状态
            // 低电量检测（带滞后防止震荡）
            if(bot->battery <= LOW_BATTERY + 5.0f) {
                // 仅当未保存目标时记录原始位置
                if(bot->orig_tx == 0 && bot->orig_ty == 0) {
                    bot->orig_tx = bot->tx;
                    bot->orig_ty = bot->ty;
                }
                // 设置充电站坐标（障碍物4中心）
                bot->tx = (obs[4].x1 + obs[4].x2)/2;
                bot->ty = (obs[4].y1 + obs[4].y2)/2;
                bot->state = 1;
            }
            break;
            
        case 1: // 前往充电站状态
            handle_charging(bot); // 检查是否到达
            break;
            
        case 2: // 充电中状态
            handle_charging(bot); // 处理充电过程
            return; // 跳过移动逻辑
    }

    /* 路径规划与移动（非充电状态）*/ 
    if(bot->state != 2) {
        path_adjust(bot, &dx, &dy);
        
        // 分步碰撞检测
        if(!check_collision(bot, dx, dy)) {
            bot->x += dx;
            bot->y += dy;
            bot->battery = fmaxf(bot->battery - BATTERY_COST, 0.0f);
        } else {
            // 碰撞后退避策略
            dx = -dx / 2;
            dy = -dy / 2;
            if(!check_collision(bot, dx, dy)) {
                bot->x += dx;
                bot->y += dy;
            }
        }
    }

    /* 记录状态 */
    log_write(bot);
}

void handle_charging(Robot* bot) {
    // 计算充电站中心坐标（障碍物4）
    const int charge_cx = (obs[4].x1 + obs[4].x2)/2;
    const int charge_cy = (obs[4].y1 + obs[4].y2)/2;

    /* 状态1：正在前往充电站 */
    if(bot->state == 1) {
        // 到达判定（3像素容差）
        if(abs(bot->x - charge_cx) <= 3 && 
           abs(bot->y - charge_cy) <= 3) {
            bot->state = 2;  // 进入充电状态
            bot->x = charge_cx; // 对齐中心
            bot->y = charge_cy;
        }
    }
    
    /* 状态2：充电中 */
    if(bot->state == 2) {
        // 充电速率处理（避免溢出）
        if(bot->battery < 100.0f) {
            bot->battery += CHARGE_RATE;
            if(bot->battery > 100.0f) {
                bot->battery = 100.0f;
            }
        }
        
        // 充满电恢复工作
        if(bot->battery >= 100.0f) {
            bot->state = 0;  // 返回工作状态
            bot->tx = bot->orig_tx; // 恢复原始目标
            bot->ty = bot->orig_ty;
            
            // 重置原始目标防止残留数据
            bot->orig_tx = 0;
            bot->orig_ty = 0;
            
            // 触发一次日志记录
            log_write(bot);
        }
    }
}


/*******************************************************
 * 函数名称：log_write
 * 功能：写入状态日志
 *******************************************************/
void log_write(Robot* bot) {
    fprintf(bot->logfile, "%d %d\n",bot->x, bot->y); 
    fflush(bot->logfile); // 确保实时写入
}

/*******************************************************
 * 函数名称：main_loop
 * 功能：主循环控制
 *******************************************************/
void main_loop(void) {
    Robot* current;
    while(!kbhit()) { // 按任意键退出
        current = robot_list;
        while(current) {
            robot_update(current);
            bar1(current->x - ROBOT_SIZE/2, current->y - ROBOT_SIZE/2, 
                current->x + ROBOT_SIZE/2, current->y + ROBOT_SIZE/2, 
                0XFFFF); // 清除旧位置
            draw_robot(current->x, current->y, 0); // 绘制机器人
            current = current->next;
        }
        delay(1); // 约10Hz更新频率
    }
}
