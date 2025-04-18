#define MOTPLAN_H
#ifdef MOTPLAN_H

/* ���������궨�� */
#define ATTRACT_GAIN     30.0f    // Ŀ������ϵ��
#define REPULSE_GAIN     200.0f   // �ϰ������ϵ��
#define SOCIAL_GAIN      150.0f   // �����˼����ϵ��
#define REPULSE_RANGE    100      // �������÷�Χ
#define SMOOTH_FACTOR     0.3f    // ·��ƽ��ϵ��
#define RANDOM_ANGLE      0.5f    // ����Ŷ��Ƕ�(����)
#define BORDER_REPULSE_GAIN  500.0    // �߽����ϵ��
#define BORDER_RANGE         30       // �߽�������÷�Χ

/* ϵͳ���� */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT    768
#define ROBOT_SIZE        50
#define STEP_BASE         10
#define CHARGE_POWER      30
#define HISTORY_SIZE       5
#define CHARGE_SPEED     0.5f
#define MAX_ROBOTS        3
#define MAX_STEPS       500
#define IDLE_LIMIT      100
#define ESCAPE_ATTEMPTS   5

#define TARGET_RADIUS     25     // Ŀ�����Ч�뾶
#define CHARGE_RADIUS     50     // ���վ��Ч�뾶
#define DAMPING_FACTOR    0.2f   // ��Ŀ������ϵ��
#define TARGET_RADIUS     25     // ˲�ƴ����뾶


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