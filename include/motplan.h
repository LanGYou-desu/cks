#define MOTPLAN_H
#ifdef MOTPLAN_H

/* 力场参数宏定义 */
#define ATTRACT_GAIN      5.0f        // 目标引力系数
#define REPULSE_GAIN     250.0f       // 障碍物斥力系数
#define SOCIAL_GAIN      125.0f       // 机器人间斥力系数
#define REPULSE_RANGE    100          // 斥力作用范围
#define SMOOTH_FACTOR     0.3f        // 路径平滑系数
#define RANDOM_ANGLE      1.5f        // 随机扰动角度(弧度)
#define BORDER_REPULSE_GAIN  500.0    // 边界斥力系数
#define BORDER_RANGE         30       // 边界斥力作用范围

#define TARGET_RADIUS     75          // 目标点有效半径
#define CHARGE_RADIUS     100         // 充电站有效半径
#define DAMPING_FACTOR    0.2f        // 近目标阻尼系数
#define TARGET_RADIUS     100          // 瞬移触发半径

/* 系统常量 */
#define SCREEN_WIDTH    1024          // 屏幕宽度
#define SCREEN_HEIGHT    768          // 屏幕高度
#define ROBOT_SIZE        50          // 机器人大小
#define STEP_BASE         10          // 基础步长
#define CHARGE_POWER      30          // 充电阈值
#define HISTORY_SIZE       5          // 轨迹历史长度
#define CHARGE_SPEED     10.0f        // 充电速度
#define MAX_ROBOTS         3          // 最大机器人数量
#define MAX_STEPS        600          // 最大步数
#define IDLE_LIMIT       100          // 最大空闲时间
#define ESCAPE_ATTEMPTS    5          // 最大逃避尝试次数

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