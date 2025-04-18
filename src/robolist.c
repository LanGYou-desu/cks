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

    // 为每个节点分配内存并初始化
    for (i = 0; i < hp->length; i++)
    {
        p = (RONODE*)malloc(sizeof(RONODE)); // 分配新节点
        if (p == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }

        // 初始化节点数据
        p->robot.id = i + 1;// 机器人编号
        p->robot.x = 340-64*i;
        p->robot.y = 710;
        p->robot.flag = 0;
        p->robot.energy = 100;
        p->next = NULL;

        if (i == 0) 
        {
            // 第一个节点作为头节点
            hp->head = p;
        } 
        else 
        {
            // 将前一个节点的 next 指向当前节点
            prev->next = p;
        }

        // 更新 prev 指针
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
        free(p); // 释放当前节点
        p = q;   // 移动到下一个节点
    }
    free(hp); // 释放链表头
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
    //删除原有日志文件
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

        //创建日志文件
        sprintf(fname, "C:\\cks\\path\\robot%d.log", p2->id);
        p2->logfile = fopen(fname, "a");
        setvbuf(robot->logfile, NULL, _IONBF, 0); // 无缓冲模式
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
    //创建新的链表节点
    Robot *p = NULL;
    Robot *head = (Robot*)malloc(sizeof(Robot));
   
    //初始化头节点数据
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
    head->state = 0; // 初始状态为工作中
    head->logfile = NULL;
    head->next = NULL;

    p = head;//当前节点指针

    //遍历源链表并创建新链表
    for (i = 1; i < hp->length; i++) 
    {
        p->next = (Robot*)malloc(sizeof(Robot));
        if (p->next == NULL) 
        {
            printf("内存分配失败！\n");
            exit(1);
        }

        p = p->next; //移动到新节点
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
        p->state = 0; // 初始状态为工作中
        p->logfile = NULL;
        p->next = NULL;
    }

    return head;//返回链表头节点
}

void setTarget(Robot *p,int tx,int ty)
{
        p->tx = tx; //设置目标坐标
        p->ty = ty;
        p->orig_tx = tx; //保存原始目标坐标
        p->orig_ty = ty;
        p->state = 0; //设置状态为工作中
}

Robot* findRobot(Robot *head, int id)
{
    Robot *p = head;
    while (p != NULL) 
    {
        if (p->id == id) 
        {
            return p; //找到目标机器人
        }
        p = p->next; //移动到下一个节点
    }
    return NULL; //未找到目标机器人
}


void freeRoboList(Robot *head)
{
    Robot *p = head, *q;

    while (p != NULL) 
    {
        q = p->next; 
        free(p);     
        free(p->logfile); //释放日志文件指针
        p = q;       
    }
}