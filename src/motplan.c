#include"allfunc.h"

Robot* robotList = NULL; // 机器人链表头指针
int node_count = 0;      // RRT节点计数器

double fmin(double a, double b) {
    return (a < b) ? a : b;
}

double fmax(double a, double b) {
    return (a > b) ? a : b;
}

/*******************************************************
 * 功能：碰撞检测
 * 参数：x,y - 检测点坐标
 *       self - 要排除的机器人指针
 * 返回：1-碰撞 0-安全
 *******************************************************/
int collision_check(int x, int y, struct Robot* self)
{
    struct Robot* curr;  /* 链表遍历指针 */
    int i;               /* 循环计数器 */
    
    /* 边界检测 */
    if(x < ROBOT_SIZE/2 || x > SCREEN_WIDTH - ROBOT_SIZE/2 ||
       y < ROBOT_SIZE/2 || y > SCREEN_HEIGHT - ROBOT_SIZE/2)
    {
        return 1;
    }

    if(x >= obs[CHARGE_STATION_INDEX].x1 && 
        x <= obs[CHARGE_STATION_INDEX].x2 &&
        y >= obs[CHARGE_STATION_INDEX].y1 && 
        y <= obs[CHARGE_STATION_INDEX].y2)
    {
        return 0;  /* 允许进入充电区域 */
    }

    /* 障碍物检测 */
    for(i=0; i<6; i++)
    {
        if(x + ROBOT_SIZE/2 > obs[i].x1 &&
           x - ROBOT_SIZE/2 < obs[i].x2 &&
           y + ROBOT_SIZE/2 > obs[i].y1 &&
           y - ROBOT_SIZE/2 < obs[i].y2)
        {
            return 1;
        }
    }

    /* 机器人间碰撞检测 */
    curr = robotList;
    while(curr != NULL)
    {
        if(curr != self)
        {
            int dx = abs(x - curr->x);
            int dy = abs(y - curr->y);
            if(dx < ROBOT_SIZE && dy < ROBOT_SIZE)
            {
                return 1;
            }
        }
        curr = curr->next;
    }

    return 0;
}

/*******************************************************
 * 功能：线段碰撞检测
 * 参数：x1,y1 - 起点坐标
 *       x2,y2 - 终点坐标
 *       self - 要排除的机器人
 * 返回：1-有碰撞 0-无碰撞
 *******************************************************/
int collision_check_line(int x1, int y1, int x2, int y2, struct Robot* self)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = x1, y = y1;
    int i;

    /* 沿线段逐步检测 */
    for(i=0; i<=steps; i++) {
        if(collision_check((int)x, (int)y, self))
            return 1;
        x += x_inc;
        y += y_inc;
    }
    return 0;
}

/*******************************************************
 * 功能：在RRT树中寻找最近节点
 * 参数：tree - 树的根节点
 *       x,y - 目标坐标
 * 返回：最近的节点指针
 *******************************************************/
RRTNode* get_nearest_node(RRTNode* tree, int x, int y)
{
    RRTNode* nearest = tree;
    float min_dist = 1e9;
    RRTNode* current = tree;

    /* 遍历整棵树寻找最近节点 */
    while(current) {
        float dist = pow(current->x - x, 2) + pow(current->y - y, 2);
        if(dist < min_dist) {
            min_dist = dist;
            nearest = current;
        }
        current = current->parent;
    }
    return nearest;
}

/*******************************************************
 * 功能：生成新节点（步进函数）
 * 参数：x1,y1 - 起点坐标
 *       x2,y2 - 目标坐标
 *       new_x,new_y - 输出新坐标
 * 返回：1-成功生成 0-失败
 *******************************************************/
int steer(int x1, int y1, int x2, int y2, int* new_x, int* new_y)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float step;
    float dist = sqrt(dx*dx + dy*dy);
    
    if(dist == 0) return 0;

    /* 计算新节点坐标 */
    step = (dist > MAX_STEER_STEP) ? MAX_STEER_STEP : dist;
    *new_x = x1 + (dx / dist) * step;
    *new_y = y1 + (dy / dist) * step;
    
    return 1;
}

/*******************************************************
 * 功能：RRT*路径规划核心算法
 * 参数：robot - 当前机器人指针
 *       start_x/y - 起点坐标
 *       goal_x/y - 目标坐标
 * 返回：生成的路径树根节点
 *******************************************************/
RRTNode* rrt_star(struct Robot* robot, int start_x, int start_y, int goal_x, int goal_y)
{
    RRTNode* root = NULL;       /* 根节点 */
    RRTNode* nearest = NULL;    /* 最近节点 */
    RRTNode* new_node = NULL;   /* 新节点 */
    RRTNode* min_node = NULL;   /* 最优父节点 */
    RRTNode* current = NULL;    /* 遍历指针 */
    RRTNode* path = NULL;       /* 最终路径 */
    int i, rand_x, rand_y;      /* 循环变量和随机坐标 */
    int new_x, new_y;           /* 新节点坐标 */
    float min_cost, d, cost;    /* 路径成本计算 */

    /* 初始化根节点 */
    root = (RRTNode*)malloc(sizeof(RRTNode));
    if(root == NULL) exit(1);
    root->x = start_x;
    root->y = start_y;
    root->cost = 0.0;
    root->parent = NULL;
    node_count = 1;

    for(i=0; i<MAX_NODES; i++)
    {
        /* 随机采样（10%概率直接采样目标点） */
        if(rand()%100 < 10)
        {
            rand_x = goal_x;
            rand_y = goal_y;
        }
        else
        {
            rand_x = rand() % SCREEN_WIDTH;
            rand_y = rand() % SCREEN_HEIGHT;
        }

        /* 寻找最近节点 */
        nearest = get_nearest_node(root, rand_x, rand_y);

        /* 生成新节点 */
        if(!steer(nearest->x, nearest->y, rand_x, rand_y, &new_x, &new_y))
            continue;

        /* 碰撞检测 */
        if(collision_check(new_x, new_y, robot))
            continue;

        /* 寻找最优父节点 */
        min_node = nearest;
        min_cost = nearest->cost + distance(nearest->x, nearest->y, new_x, new_y);
        current = root;
        while(current != NULL)
        {
            d = distance(current->x, current->y, new_x, new_y);
            if(d < NEIGHBOR_RADIUS)
            {
                cost = current->cost + d;
                if(cost < min_cost && !collision_check_line(current->x, current->y, new_x, new_y, robot))
                {
                    min_cost = cost;
                    min_node = current;
                }
            }
            current = current->parent;
        }

        /* 创建新节点 */
        new_node = (RRTNode*)malloc(sizeof(RRTNode));
        new_node->x = new_x;
        new_node->y = new_y;
        new_node->cost = min_cost;
        new_node->parent = min_node;
        node_count++;

        /* 重新布线优化 */
        current = root;
        while(current != NULL)
        {
            d = distance(current->x, current->y, new_x, new_y);
            if(d < NEIGHBOR_RADIUS)
            {
                cost = new_node->cost + d;
                if(cost < current->cost && !collision_check_line(new_x, new_y, current->x, current->y, robot))
                {
                    current->parent = new_node;
                    current->cost = cost;
                }
            }
            current = current->parent;
        }

        /* 检查是否到达目标区域 */
        if(distance(new_x, new_y, goal_x, goal_y) < GOAL_TOLERANCE)
        {
            /* 构建返回路径 */
            RRTNode* node = new_node;
            while(node != NULL)
            {
                RRTNode* temp = (RRTNode*)malloc(sizeof(RRTNode));
                temp->x = node->x;
                temp->y = node->y;
                temp->parent = path;
                path = temp;
                node = node->parent;
            }
            free_tree(root);
            return path;
        }
    }

    free_tree(root);
    return NULL;
}

/*******************************************************
 * 功能：机器人移动控制
 * 参数：robot - 要移动的机器人指针
 *******************************************************/
void move_robot(struct Robot* robot)
{
    float step;  /* 实际步长 */
    int dx, dy;  /* 移动方向 */
    float dist;  /* 到路径点距离 */

    /* 低电量处理 */
    if(robot->battery < MIN_BATTERY && robot->state != STATE_CHARGING)
    {
        OBS cs = obs[CHARGE_STATION_INDEX];
        robot->state = STATE_TO_CHARGE;
        robot->tx = (cs.x1 + cs.x2)/2;
        robot->ty = (cs.y1 + cs.y2)/2;
        free_tree(robot->path);
        robot->path = rrt_star(robot, robot->x, robot->y, robot->tx, robot->ty);
    }

    /* 路径跟踪 */
    if(robot->path != NULL)
    {
        dx = robot->path->x - robot->x;
        dy = robot->path->y - robot->y;
        dist = sqrt(dx*dx + dy*dy);

        if(dist > STEP_BASE)
        {
            /* 计算实际步长（带随机扰动） */
            step = STEP_BASE * (0.8 + 0.4*(rand()/(float)RAND_MAX));
            robot->x += (dx / dist) * step;
            robot->y += (dy / dist) * step;

            /* 电量消耗 */
            if(robot->state != STATE_CHARGING)
                robot->battery = fmax(0, robot->battery - 0.1);
        }
        else
        {
            /* 到达路径点，前进到下一个节点 */
            RRTNode* temp = robot->path;
            robot->path = robot->path->parent;
            free(temp);
        }
    }

    log_path(robot);
}

/*******************************************************
 * 功能：机器人充电处理
 * 参数：robot - 需要充电的机器人指针
 *******************************************************/
void charge_robot(struct Robot* robot)
{
    /* 获取充电站坐标 */
    OBS charge_station = obs[CHARGE_STATION_INDEX];
    int cs_center_x = (charge_station.x1 + charge_station.x2) / 2;
    int cs_center_y = (charge_station.y1 + charge_station.y2) / 2;

    /* 检查是否准确到达充电位置 */
    if(abs(robot->x - cs_center_x) <= STEP_BASE && 
       abs(robot->y - cs_center_y) <= STEP_BASE)
    {
        /* 执行充电操作 */
        robot->battery += CHARGE_RATE;
        
        /* 限制电量最大值 */
        if(robot->battery >= 100.0f)
        {
            robot->battery = 100.0f;
            
            /* 恢复原始目标 */
            robot->tx = robot->orig_tx;
            robot->ty = robot->orig_ty;
            
            /* 更新状态为返回工作 */
            robot->state = STATE_RETURNING;
            
            /* 重新规划路径 */
            free_tree(robot->path);
            robot->path = rrt_star(robot, robot->x, robot->y, 
                                 robot->tx, robot->ty);
            
            /* 记录充电完成日志 */
            if(robot->logfile)
            {
                fprintf(robot->logfile, "Charging complete at (%d,%d)\n", 
                        robot->x, robot->y);
            }
        }
    }
    else
    {
        /* 如果未准确到达充电位置，继续微调位置 */
        int dx = cs_center_x - robot->x;
        int dy = cs_center_y - robot->y;
        float dist = sqrt(dx*dx + dy*dy);
        
        if(dist > 0)
        {
            /* 精确对准充电站中心 */
            robot->x += (dx / dist) * fmin(STEP_BASE/2, dist);
            robot->y += (dy / dist) * fmin(STEP_BASE/2, dist);
        }
    }
}


/*******************************************************
 * 功能：更新机器人状态机
 * 参数：robot - 要更新的机器人指针
 *******************************************************/
void update_state(struct Robot* robot)
{
    int dist_to_target;  /* 到目标点距离 */

    switch(robot->state)
    {
        case STATE_WORKING:
            dist_to_target = distance(robot->x, robot->y, robot->tx, robot->ty);
            if(dist_to_target < GOAL_TOLERANCE)
            {
                /* 生成新目标 */
                robot->tx = 100 + rand() % (SCREEN_WIDTH - 200);
                robot->ty = 100 + rand() % (SCREEN_HEIGHT - 200);
                free_tree(robot->path);
                robot->path = rrt_star(robot, robot->x, robot->y, robot->tx, robot->ty);
            }
            break;

        case STATE_TO_CHARGE:
            if(distance(robot->x, robot->y, robot->tx, robot->ty) < GOAL_TOLERANCE)
            {
                robot->state = STATE_CHARGING;
            }
            break;

        case STATE_CHARGING:
            robot->battery = fmin(100.0, robot->battery + CHARGE_RATE);
            if(robot->battery >= 100.0)
            {
                robot->state = STATE_RETURNING;
                robot->tx = robot->orig_tx;
                robot->ty = robot->orig_ty;
                free_tree(robot->path);
                robot->path = rrt_star(robot, robot->x, robot->y, robot->tx, robot->ty);
            }
            break;

        case STATE_RETURNING:
            if(distance(robot->x, robot->y, robot->tx, robot->ty) < GOAL_TOLERANCE)
            {
                robot->state = STATE_WORKING;
            }
            break;
    }
}

/*******************************************************
 * 功能：主循环（独立函数）
 *******************************************************/
void main_loop(void)
{
    int frame = 0;         /* 帧计数器 */
    struct Robot* curr;    /* 链表遍历指针 */

    while(!kbhit())  /* 按任意键退出 */
    {
        frame++;
        printf("Frame: %d\n", frame);

        curr = robotList;
        while(curr != NULL)
        {
            update_state(curr);
            move_robot(curr);

            printf("Robot %d: (%d,%d) Bat:%.1f%% State:%d\n",
                   curr->id, curr->x, curr->y, curr->battery, curr->state);

            curr = curr->next;
        }

        delay(100);  /* 控制循环速度 */
    }
}

/*******************************************************
 * 辅助函数：计算两点间欧氏距离
 * 参数：x1,y1 - 起点坐标
 *       x2,y2 - 终点坐标
 * 返回：整数距离值
 *******************************************************/
int distance(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

/*******************************************************
 * 辅助函数：释放RRT树内存
 * 参数：node - 树根节点
 *******************************************************/
void free_tree(RRTNode* node)
{
    RRTNode* temp;
    while(node != NULL)
    {
        temp = node;
        node = node->parent;
        free(temp);
    }
}

/*******************************************************
 * 辅助函数：记录路径日志
 * 参数：robot - 要记录的机器人指针
 *******************************************************/
void log_path(struct Robot* robot)
{
    if(robot->logfile != NULL)
    {
        fprintf(robot->logfile, "%d,%d,%.1f,%d\n",
                robot->x, robot->y, robot->battery, robot->state);
    }
}