#define ROBOLIST_H
#ifdef ROBOLIST_H

//·���滮�㷨�����˽ṹ��
typedef struct Robot {
    int id;                // Ψһ��ʶ��
    int x, y;              // ��ǰ�������꣨������
    int tx, ty;            // ��ǰĿ������
    int orig_tx, orig_ty;  // ԭʼĿ�����꣨���ǰ��
    int prev_x, prev_y;    // �ϴμ�¼���꣨����·��ƽ����
    int hist_dx[5];        // X�����ƶ���ʷ
    int hist_dy[5];        // Y�����ƶ���ʷ
    int hist_index;        // ��ʷ��¼����
    int escape_count;      // �������Լ�����
    int same_pos_count;    // ��ͬλ�ü�����
    float battery;         // ʣ�������0-100��
    int cargo_type;        // Я����������
    int state;             // 0-������ 1-ǰ����� 2-�����
    FILE* logfile;         // ��־�ļ�ָ��
    struct Robot* next;    // ����ָ��
} Robot;

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