#define ROBOLIST_H
#ifdef ROBOLIST_H

/* RRT���ڵ�ṹ */
typedef struct RRTNode {
    int x, y;             /* �ڵ����� */
    float cost;           /* ����ɱ� */
    struct RRTNode* parent; /* ���ڵ�ָ�� */
} RRTNode;

/* ������״̬ö�� */
typedef enum {
    STATE_WORKING,   /* ������ */
    STATE_TO_CHARGE, /* ǰ����� */
    STATE_CHARGING,  /* ����� */
    STATE_RETURNING  /* �������� */
} RobotState;

//·���滮�㷨�����˽ṹ��
typedef struct Robot{
    int id;               /* ������ID */
    int x, y;             /* ��ǰλ�� */
    int tx, ty;           /* ��ǰĿ�� */
    int orig_tx, orig_ty; /* ԭʼĿ�� */
    float battery;        /* ��ǰ���� */
    RobotState state;     /* ��ǰ״̬ */
    FILE* logfile;        /* ��־�ļ�ָ�� */
    RRTNode* path;        /* ��ǰ·�� */
    struct Robot* next;   /* ����ָ�� */
}Robot;

//�����˽ṹ
typedef struct{
    int id;//�����˱��
    int x;
    int y;
    int flag;//��־λ��0��ʾδ��ռ�ã�1��ʾװ��һ����2��ʾװ�ض�����3��ʾװ���������
    float energy;//����
}ROBO;

//����ṹ
typedef struct{
    ROBO robot;
    struct RONODE *next;
}RONODE;

//����ͷ
typedef struct{
    RONODE *head;
    int length;
}ROHEAD;

//��ʼ������
ROHEAD* init_robolist(int robonum);

//��������
ROHEAD* create_robolist(ROHEAD* hp);

//��������
void traversal_robolist(ROHEAD* hp);

//�ͷ�����
void free_robolist(ROHEAD* hp);

//ת������
void turn_list(ROHEAD *hp,Robot *robot);

//ת������(����)
void turn_list_back(ROHEAD *hp,Robot *robot);

//����·���滮�㷨����������
Robot* createRoboList(ROHEAD *hp);

//�ͷ�·���滮�㷨����������
void freeRoboList(Robot* head);

//Ѱ��Ŀ�������
Robot* findRobot(Robot* head, int id);

//�޸�Ŀ������
void satTarget(Robot *p, int tx, int ty);

#endif