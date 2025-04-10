#include"allfunc.h"

Robot* robotList = NULL; // ����������ͷָ��
int node_count = 0;      // RRT�ڵ������

double fmin(double a, double b) {
    return (a < b) ? a : b;
}

double fmax(double a, double b) {
    return (a > b) ? a : b;
}

/*******************************************************
 * ���ܣ���ײ���
 * ������x,y - ��������
 *       self - Ҫ�ų��Ļ�����ָ��
 * ���أ�1-��ײ 0-��ȫ
 *******************************************************/
int collision_check(int x, int y, struct Robot* self)
{
    struct Robot* curr;  /* �������ָ�� */
    int i;               /* ѭ�������� */
    
    /* �߽��� */
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
        return 0;  /* ������������� */
    }

    /* �ϰ����� */
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

    /* �����˼���ײ��� */
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
 * ���ܣ��߶���ײ���
 * ������x1,y1 - �������
 *       x2,y2 - �յ�����
 *       self - Ҫ�ų��Ļ�����
 * ���أ�1-����ײ 0-����ײ
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

    /* ���߶��𲽼�� */
    for(i=0; i<=steps; i++) {
        if(collision_check((int)x, (int)y, self))
            return 1;
        x += x_inc;
        y += y_inc;
    }
    return 0;
}

/*******************************************************
 * ���ܣ���RRT����Ѱ������ڵ�
 * ������tree - ���ĸ��ڵ�
 *       x,y - Ŀ������
 * ���أ�����Ľڵ�ָ��
 *******************************************************/
RRTNode* get_nearest_node(RRTNode* tree, int x, int y)
{
    RRTNode* nearest = tree;
    float min_dist = 1e9;
    RRTNode* current = tree;

    /* ����������Ѱ������ڵ� */
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
 * ���ܣ������½ڵ㣨����������
 * ������x1,y1 - �������
 *       x2,y2 - Ŀ������
 *       new_x,new_y - ���������
 * ���أ�1-�ɹ����� 0-ʧ��
 *******************************************************/
int steer(int x1, int y1, int x2, int y2, int* new_x, int* new_y)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float step;
    float dist = sqrt(dx*dx + dy*dy);
    
    if(dist == 0) return 0;

    /* �����½ڵ����� */
    step = (dist > MAX_STEER_STEP) ? MAX_STEER_STEP : dist;
    *new_x = x1 + (dx / dist) * step;
    *new_y = y1 + (dy / dist) * step;
    
    return 1;
}

/*******************************************************
 * ���ܣ�RRT*·���滮�����㷨
 * ������robot - ��ǰ������ָ��
 *       start_x/y - �������
 *       goal_x/y - Ŀ������
 * ���أ����ɵ�·�������ڵ�
 *******************************************************/
RRTNode* rrt_star(struct Robot* robot, int start_x, int start_y, int goal_x, int goal_y)
{
    RRTNode* root = NULL;       /* ���ڵ� */
    RRTNode* nearest = NULL;    /* ����ڵ� */
    RRTNode* new_node = NULL;   /* �½ڵ� */
    RRTNode* min_node = NULL;   /* ���Ÿ��ڵ� */
    RRTNode* current = NULL;    /* ����ָ�� */
    RRTNode* path = NULL;       /* ����·�� */
    int i, rand_x, rand_y;      /* ѭ��������������� */
    int new_x, new_y;           /* �½ڵ����� */
    float min_cost, d, cost;    /* ·���ɱ����� */

    /* ��ʼ�����ڵ� */
    root = (RRTNode*)malloc(sizeof(RRTNode));
    if(root == NULL) exit(1);
    root->x = start_x;
    root->y = start_y;
    root->cost = 0.0;
    root->parent = NULL;
    node_count = 1;

    for(i=0; i<MAX_NODES; i++)
    {
        /* ���������10%����ֱ�Ӳ���Ŀ��㣩 */
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

        /* Ѱ������ڵ� */
        nearest = get_nearest_node(root, rand_x, rand_y);

        /* �����½ڵ� */
        if(!steer(nearest->x, nearest->y, rand_x, rand_y, &new_x, &new_y))
            continue;

        /* ��ײ��� */
        if(collision_check(new_x, new_y, robot))
            continue;

        /* Ѱ�����Ÿ��ڵ� */
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

        /* �����½ڵ� */
        new_node = (RRTNode*)malloc(sizeof(RRTNode));
        new_node->x = new_x;
        new_node->y = new_y;
        new_node->cost = min_cost;
        new_node->parent = min_node;
        node_count++;

        /* ���²����Ż� */
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

        /* ����Ƿ񵽴�Ŀ������ */
        if(distance(new_x, new_y, goal_x, goal_y) < GOAL_TOLERANCE)
        {
            /* ��������·�� */
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
 * ���ܣ��������ƶ�����
 * ������robot - Ҫ�ƶ��Ļ�����ָ��
 *******************************************************/
void move_robot(struct Robot* robot)
{
    float step;  /* ʵ�ʲ��� */
    int dx, dy;  /* �ƶ����� */
    float dist;  /* ��·������� */

    /* �͵������� */
    if(robot->battery < MIN_BATTERY && robot->state != STATE_CHARGING)
    {
        OBS cs = obs[CHARGE_STATION_INDEX];
        robot->state = STATE_TO_CHARGE;
        robot->tx = (cs.x1 + cs.x2)/2;
        robot->ty = (cs.y1 + cs.y2)/2;
        free_tree(robot->path);
        robot->path = rrt_star(robot, robot->x, robot->y, robot->tx, robot->ty);
    }

    /* ·������ */
    if(robot->path != NULL)
    {
        dx = robot->path->x - robot->x;
        dy = robot->path->y - robot->y;
        dist = sqrt(dx*dx + dy*dy);

        if(dist > STEP_BASE)
        {
            /* ����ʵ�ʲ�����������Ŷ��� */
            step = STEP_BASE * (0.8 + 0.4*(rand()/(float)RAND_MAX));
            robot->x += (dx / dist) * step;
            robot->y += (dy / dist) * step;

            /* �������� */
            if(robot->state != STATE_CHARGING)
                robot->battery = fmax(0, robot->battery - 0.1);
        }
        else
        {
            /* ����·���㣬ǰ������һ���ڵ� */
            RRTNode* temp = robot->path;
            robot->path = robot->path->parent;
            free(temp);
        }
    }

    log_path(robot);
}

/*******************************************************
 * ���ܣ������˳�紦��
 * ������robot - ��Ҫ���Ļ�����ָ��
 *******************************************************/
void charge_robot(struct Robot* robot)
{
    /* ��ȡ���վ���� */
    OBS charge_station = obs[CHARGE_STATION_INDEX];
    int cs_center_x = (charge_station.x1 + charge_station.x2) / 2;
    int cs_center_y = (charge_station.y1 + charge_station.y2) / 2;

    /* ����Ƿ�׼ȷ������λ�� */
    if(abs(robot->x - cs_center_x) <= STEP_BASE && 
       abs(robot->y - cs_center_y) <= STEP_BASE)
    {
        /* ִ�г����� */
        robot->battery += CHARGE_RATE;
        
        /* ���Ƶ������ֵ */
        if(robot->battery >= 100.0f)
        {
            robot->battery = 100.0f;
            
            /* �ָ�ԭʼĿ�� */
            robot->tx = robot->orig_tx;
            robot->ty = robot->orig_ty;
            
            /* ����״̬Ϊ���ع��� */
            robot->state = STATE_RETURNING;
            
            /* ���¹滮·�� */
            free_tree(robot->path);
            robot->path = rrt_star(robot, robot->x, robot->y, 
                                 robot->tx, robot->ty);
            
            /* ��¼��������־ */
            if(robot->logfile)
            {
                fprintf(robot->logfile, "Charging complete at (%d,%d)\n", 
                        robot->x, robot->y);
            }
        }
    }
    else
    {
        /* ���δ׼ȷ������λ�ã�����΢��λ�� */
        int dx = cs_center_x - robot->x;
        int dy = cs_center_y - robot->y;
        float dist = sqrt(dx*dx + dy*dy);
        
        if(dist > 0)
        {
            /* ��ȷ��׼���վ���� */
            robot->x += (dx / dist) * fmin(STEP_BASE/2, dist);
            robot->y += (dy / dist) * fmin(STEP_BASE/2, dist);
        }
    }
}


/*******************************************************
 * ���ܣ����»�����״̬��
 * ������robot - Ҫ���µĻ�����ָ��
 *******************************************************/
void update_state(struct Robot* robot)
{
    int dist_to_target;  /* ��Ŀ������ */

    switch(robot->state)
    {
        case STATE_WORKING:
            dist_to_target = distance(robot->x, robot->y, robot->tx, robot->ty);
            if(dist_to_target < GOAL_TOLERANCE)
            {
                /* ������Ŀ�� */
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
 * ���ܣ���ѭ��������������
 *******************************************************/
void main_loop(void)
{
    int frame = 0;         /* ֡������ */
    struct Robot* curr;    /* �������ָ�� */

    while(!kbhit())  /* ��������˳� */
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

        delay(100);  /* ����ѭ���ٶ� */
    }
}

/*******************************************************
 * �������������������ŷ�Ͼ���
 * ������x1,y1 - �������
 *       x2,y2 - �յ�����
 * ���أ���������ֵ
 *******************************************************/
int distance(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

/*******************************************************
 * �����������ͷ�RRT���ڴ�
 * ������node - �����ڵ�
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
 * ������������¼·����־
 * ������robot - Ҫ��¼�Ļ�����ָ��
 *******************************************************/
void log_path(struct Robot* robot)
{
    if(robot->logfile != NULL)
    {
        fprintf(robot->logfile, "%d,%d,%.1f,%d\n",
                robot->x, robot->y, robot->battery, robot->state);
    }
}