#define ROBOLIST_H
#ifdef ROBOLIST_H

//路径规划算法机器人结构体
typedef struct Robot{
    int id;               /* 机器人ID */
    int x, y;             /* 当前位置 */
    int tx, ty;           /* 当前目标 */
    int orig_tx, orig_ty; /* 原始目标 */
    float battery;        /* 当前电量 */
    int state;            /* 机器人状态 */
    FILE* logfile;        /* 日志文件指针 */
    struct Robot* next;   /* 链表指针 */
}Robot;

//机器人结构
typedef struct{
    int id;//机器人编号
    int x;
    int y;
    int flag;//标志位，0表示未被占用，1表示装载一类货物，2表示装载二类货物，3表示装载三类货物
    float energy;//能量
}ROBO;

//链表结构
typedef struct{
    ROBO robot;
    struct RONODE *next;
}RONODE;

//链表头
typedef struct{
    RONODE *head;
    int length;
}ROHEAD;

//初始化链表
ROHEAD* init_robolist(int robonum);

//创建链表
ROHEAD* create_robolist(ROHEAD* hp);

//遍历链表
void traversal_robolist(ROHEAD* hp);

//释放链表
void free_robolist(ROHEAD* hp);

//转换链表
void turn_list(ROHEAD *hp,Robot *robot);

//转换链表(反向)
void turn_list_back(ROHEAD *hp,Robot *robot);

//创建路径规划算法机器人链表
Robot* createRoboList(ROHEAD *hp);

//释放路径规划算法机器人链表
void freeRoboList(Robot* head);

//寻找目标机器人
Robot* findRobot(Robot* head, int id);

//修改目标坐标
void satTarget(Robot *p, int tx, int ty);

#endif