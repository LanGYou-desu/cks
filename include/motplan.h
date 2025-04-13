#define MOTPLAN_H
#ifdef MOTPLAN_H

/* �������� */
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768
#define ROBOT_SIZE      50     // �����˱߳�
#define STEP_BASE       8      // ��������
#define CHARGE_RATE     100.0f   // �������
#define LOW_BATTERY     20.0f  // �͵�����ֵ
#define BATTERY_COST    0.05f   // ÿ���ĵ���

/* ����ԭ������ */
float fmaxf(float a, float b);
float fminf(float a, float b);
void robot_init(int id, int x, int y);
void robot_update(Robot* bot);
void main_loop(void);
float calc_distance(int x1, int y1, int x2, int y2);
int check_collision(Robot* bot, int dx, int dy);
void path_adjust(Robot* bot, int* dx, int* dy);
void handle_charging(Robot* bot);
void log_write(Robot* bot);

#endif