#define MOTPLAN_H
#ifdef MOTPLAN_H

/* ���������궨�� */
#define ATTRACT_GAIN      0.8f    // Ŀ������ϵ��
#define REPULSE_GAIN     200.0f   // �ϰ������ϵ��
#define SOCIAL_GAIN      150.0f   // �����˼����ϵ��
#define REPULSE_RANGE    150      // �������÷�Χ
#define SMOOTH_FACTOR     0.3f    // ·��ƽ��ϵ��
#define RANDOM_ANGLE      0.5f    // ����Ŷ��Ƕ�(����)

/* ϵͳ���� */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT    768
#define ROBOT_SIZE        50
#define STEP_BASE          8
#define CHARGE_POWER      30
#define HISTORY_SIZE       5
#define CHARGE_SPEED     0.5f
#define MAX_ROBOTS        3
#define MAX_STEPS     10000
#define IDLE_LIMIT      100
#define ESCAPE_ATTEMPTS   5

#define TARGET_RADIUS     10     // Ŀ�����Ч�뾶
#define CHARGE_RADIUS     15     // ���վ��Ч�뾶
#define DAMPING_FACTOR    0.2f   // ��Ŀ������ϵ��

/* �������� */
int checkCollision(int x, int y, int exclude_id);
void calculateForces(Robot* robot, float* dx, float* dy);
void smoothPath(Robot* robot, float* dx, float* dy);
void moveTowards(Robot* robot, float dx, float dy);
void handleCharging(Robot* robot);
void mainLoop();
float distance(int x1, int y1, int x2, int y2);
float fminf(float a,float b);
float fmaxf(float a,float b);
double round(double r);

#endif