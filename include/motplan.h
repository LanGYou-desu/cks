#define MOTPLAN_H
#ifdef MOTPLAN_H

/* 常量定义 */
#define SCREEN_WIDTH 1024     /* 屏幕宽度 */
#define SCREEN_HEIGHT 768     /* 屏幕高度 */
#define ROBOT_SIZE 50         /* 机器人边长 */
#define STEP_BASE 8           /* 基础步长 */
#define MAX_NODES 5000        /* RRT最大节点数 */
#define NEIGHBOR_RADIUS 50    /* 邻域半径 */
#define GOAL_TOLERANCE 20     /* 目标容差 */
#define CHARGE_STATION_INDEX 4 /* 充电站索引 */
#define MIN_BATTERY 40.0      /* 低电量阈值 */
#define CHARGE_RATE 2.0       /* 充电速率 */
#define MAX_ROBOTS 3          /* 最大机器人数量 */
#define MAX_STEER_STEP 30     /* 最大扩展步长 */

/* 函数声明 */
double fmin(double a, double b);
double fmax(double a, double b);
int collision_check(int x, int y, struct Robot* self);
RRTNode* rrt_star(struct Robot* robot, int start_x, int start_y, int goal_x, int goal_y);
void move_robot(struct Robot* robot);
void update_state(struct Robot* robot);
void main_loop(void);
void charge_robot(struct Robot* robot);
int distance(int x1, int y1, int x2, int y2);
RRTNode* get_nearest_node(RRTNode* tree, int x, int y);
int steer(int x1, int y1, int x2, int y2, int* new_x, int* new_y);
void free_tree(RRTNode* node);
void log_path(struct Robot* robot);
int collision_check_line(int x1, int y1, int x2, int y2, struct Robot* self);

#endif