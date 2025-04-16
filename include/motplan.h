#define MOTPLAN_H
#ifdef MOTPLAN_H

/* 力场参数宏定义 */
#define ATTRACT_GAIN     30.0f    // 目标引力系数
#define REPULSE_GAIN     200.0f   // 障碍物斥力系数
#define SOCIAL_GAIN      150.0f   // 机器人间斥力系数
#define REPULSE_RANGE    100      // 斥力作用范围
#define SMOOTH_FACTOR     0.3f    // 路径平滑系数
#define RANDOM_ANGLE      0.5f    // 随机扰动角度(弧度)
#define BORDER_REPULSE_GAIN  500.0    // 边界斥力系数
#define BORDER_RANGE         30       // 边界斥力作用范围

/* 系统常量 */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT    768
#define ROBOT_SIZE        50
#define STEP_BASE          8
#define CHARGE_POWER      30
#define HISTORY_SIZE       5
#define CHARGE_SPEED     0.5f
#define MAX_ROBOTS        3
#define MAX_STEPS       500
#define IDLE_LIMIT      100
#define ESCAPE_ATTEMPTS   5

#define TARGET_RADIUS     25     // 目标点有效半径
#define CHARGE_RADIUS     50     // 充电站有效半径
#define DAMPING_FACTOR    0.2f   // 近目标阻尼系数
#define TARGET_RADIUS     25     // 瞬移触发半径


int checkCollision(int x, int y, int exclude_id);
int shouldTeleport(Robot* robot);
void calculateForces(Robot* robot, float* dx, float* dy);
void smoothPath(Robot* robot, float* dx, float* dy);
void moveTowards(Robot* robot, float dx, float dy);
void handleCharging(Robot* robot);
void mainLoop(int robonum);
void all_reach();
int allRobotsReached();
float distance(int x1, int y1, int x2, int y2);
float fminf(float a,float b);
float fmaxf(float a,float b);
double round(double r);

#endif