#define MOTPLAN_H
#ifdef MOTPLAN_H

/* ���������궨�� */
#define ATTRACT_GAIN      5.0f        // Ŀ������ϵ��
#define REPULSE_GAIN     250.0f       // �ϰ������ϵ��
#define SOCIAL_GAIN      125.0f       // �����˼����ϵ��
#define REPULSE_RANGE    100          // �������÷�Χ
#define SMOOTH_FACTOR     0.3f        // ·��ƽ��ϵ��
#define RANDOM_ANGLE      1.5f        // ����Ŷ��Ƕ�(����)
#define BORDER_REPULSE_GAIN  500.0    // �߽����ϵ��
#define BORDER_RANGE         30       // �߽�������÷�Χ

#define TARGET_RADIUS     75          // Ŀ�����Ч�뾶
#define CHARGE_RADIUS     150         // ���վ��Ч�뾶
#define DAMPING_FACTOR    0.2f        // ��Ŀ������ϵ��
#define TARGET_RADIUS     100         // ˲�ƴ����뾶

/* ϵͳ���� */
#define SCREEN_WIDTH    1024          // ��Ļ���
#define SCREEN_HEIGHT    768          // ��Ļ�߶�
#define ROBOT_SIZE        50          // �����˴�С
#define STEP_BASE         10          // ��������
#define CHARGE_POWER      30          // �����ֵ
#define STEP_POWER       0.02f        // ÿ����������
#define CHARGE_SPEED     50.0f        // ����ٶ�
#define MAX_ROBOTS         3          // ������������
#define HISTORY_SIZE       5          // �켣��ʷ����
#define MAX_STEPS        500          // �����
#define IDLE_LIMIT       100          // ������ʱ��
#define ESCAPE_ATTEMPTS    5          // ����ӱܳ��Դ���

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