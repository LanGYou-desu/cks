#define MOTPLAN_H
#ifdef MOTPLAN_H

/* �������� */
#define SCREEN_WIDTH 1024     /* ��Ļ��� */
#define SCREEN_HEIGHT 768     /* ��Ļ�߶� */
#define ROBOT_SIZE 50         /* �����˱߳� */
#define STEP_BASE 8           /* �������� */
#define MAX_NODES 5000        /* RRT���ڵ��� */
#define NEIGHBOR_RADIUS 50    /* ����뾶 */
#define GOAL_TOLERANCE 20     /* Ŀ���ݲ� */
#define CHARGE_STATION_INDEX 4 /* ���վ���� */
#define MIN_BATTERY 40.0      /* �͵�����ֵ */
#define CHARGE_RATE 2.0       /* ������� */
#define MAX_ROBOTS 3          /* ������������ */
#define MAX_STEER_STEP 30     /* �����չ���� */

/* �������� */
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