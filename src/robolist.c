#include"allfunc.h"

ROHEAD* init_robolist(int robonum)
{
    ROHEAD *hp = (ROHEAD*)malloc(sizeof(ROHEAD));
    hp->head = NULL;
    hp->length = robonum;
    return hp;
}

ROHEAD* create_robolist(ROHEAD* hp)
{
    int i;
    RONODE *p, *prev = NULL;

    // Ϊÿ���ڵ�����ڴ沢��ʼ��
    for (i = 0; i < hp->length; i++)
    {
        p = (RONODE*)malloc(sizeof(RONODE)); // �����½ڵ�
        if (p == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }

        // ��ʼ���ڵ�����
        p->robot.id = i + 1;// �����˱��
        p->robot.x = 340-64*i;
        p->robot.y = 710;
        p->robot.flag = 0;
        p->robot.energy = 100;
        p->next = NULL;

        if (i == 0) 
        {
            // ��һ���ڵ���Ϊͷ�ڵ�
            hp->head = p;
        } 
        else 
        {
            // ��ǰһ���ڵ�� next ָ��ǰ�ڵ�
            prev->next = p;
        }

        // ���� prev ָ��
        prev = p;
    }

    return hp;
}

void traversal_robolist(ROHEAD* hp)
{
    RONODE *p = hp->head;
    while (p != NULL)
    {
        p = p->next;
    }
}

void free_robolist(ROHEAD *hp)
{
    RONODE *p = hp->head, *q;

    if (hp == NULL) return;
    
    while (p != NULL)
    {
        q = p->next;
        free(p); // �ͷŵ�ǰ�ڵ�
        p = q;   // �ƶ�����һ���ڵ�
    }
    free(hp); // �ͷ�����ͷ
}

void turn_list(ROHEAD *hp,Robot *robot)
{
    int i;
    RONODE *p1 = hp->head;
    Robot *p2 = robot;
    char fname[30];

    char removefile[3][30]={
        "C:\\cks\\path\\robot1.log",
        "C:\\cks\\path\\robot2.log",
        "C:\\cks\\path\\robot3.log"
    };
    //ɾ��ԭ����־�ļ�
    for(i=0;i<3;i++)
    {
        remove(removefile[i]);
    }

    while (p1 != NULL)
    {
        p2->id = p1->robot.id;
        p2->x = p1->robot.x;
        p2->y = p1->robot.y;
        p2->battery = p1->robot.energy;

        //������־�ļ�
        sprintf(fname, "C:\\cks\\path\\robot%d.log", p2->id);
        p2->logfile = fopen(fname, "a");
        setvbuf(robot->logfile, NULL, _IONBF, 0); // �޻���ģʽ
        if(p2->logfile == NULL) {
            printf("Error: Cannot create log file for robot %d\n", p2->id);
        }

        p1 = p1->next;
        p2 = p2->next;
    }
}

void turn_list_back(ROHEAD *hp,Robot *robot)
{
    RONODE *p1 = hp->head;
    Robot *p2 = robot;

    while (p1 != NULL)
    {
        p1->robot.id = p2->id;
        p1->robot.x = p2->x;
        p1->robot.y = p2->y;
        p1->robot.energy = p2->battery;
        
        p1 = p1->next;
        p2 = p2->next;
    }
}

Robot* createRoboList(ROHEAD *hp)
{
    int i;
    //�����µ�����ڵ�
    Robot *p = NULL;
    Robot *head = (Robot*)malloc(sizeof(Robot));
   
    //��ʼ��ͷ�ڵ�����
    head->id = 0;
    head->x = 0;
    head->y = 0;
    head->tx = 0;
    head->ty = 0;
    head->orig_tx = 0;
    head->orig_ty = 0;
    head->prev_x = 0;
    head->prev_y = 0;
    head->hist_index = 0;
    head->escape_count = 0;
    head->same_pos_count = 0;
    head->battery = 0;
    head->reached = 0;
    head->state = 0; // ��ʼ״̬Ϊ������
    head->logfile = NULL;
    head->next = NULL;

    p = head;//��ǰ�ڵ�ָ��

    //����Դ��������������
    for (i = 1; i < hp->length; i++) 
    {
        p->next = (Robot*)malloc(sizeof(Robot));
        if (p->next == NULL) 
        {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }

        p = p->next; //�ƶ����½ڵ�
        p->id = 0;
        p->x = 0;
        p->y = 0;
        p->tx = 0;
        p->ty = 0;
        p->orig_tx = 0;
        p->orig_ty = 0;
        p->prev_x = 0;
        p->prev_y = 0;
        p->hist_index = 0;
        p->escape_count = 0;
        p->same_pos_count = 0;
        p->battery = 0;
        p->reached = 0;
        p->state = 0; // ��ʼ״̬Ϊ������
        p->logfile = NULL;
        p->next = NULL;
    }

    return head;//��������ͷ�ڵ�
}

void setTarget(Robot *p,int tx,int ty)
{
        p->tx = tx; //����Ŀ������
        p->ty = ty;
        p->orig_tx = tx; //����ԭʼĿ������
        p->orig_ty = ty;
        p->state = 0; //����״̬Ϊ������
}

Robot* findRobot(Robot *head, int id)
{
    Robot *p = head;
    while (p != NULL) 
    {
        if (p->id == id) 
        {
            return p; //�ҵ�Ŀ�������
        }
        p = p->next; //�ƶ�����һ���ڵ�
    }
    return NULL; //δ�ҵ�Ŀ�������
}


void freeRoboList(Robot *head)
{
    Robot *p = head, *q;

    while (p != NULL) 
    {
        q = p->next; 
        free(p);     
        free(p->logfile); //�ͷ���־�ļ�ָ��
        p = q;       
    }
}