#define ROBOLIST_H
#ifdef ROBOLIST_H

/* RRT树节点结构 */
typedef struct RRTNode {
    int x, y;             /* 节点坐标 */
    float cost;           /* 到达成本 */
    struct RRTNode* parent; /* 父节点指针 */
} RRTNode;

/* 机器人状态枚举 */
typedef enum {
    STATE_WORKING,   /* 工作中 */
    STATE_TO_CHARGE, /* 前往充电 */
    STATE_CHARGING,  /* 充电中 */
    STATE_RETURNING  /* 返回任务 */
} RobotState;

//路径规划算法机器人结构体
typedef struct Robot{
    int id;               /* 机器人ID */
    int x, y;             /* 当前位置 */
    int tx, ty;           /* 当前目标 */
    int orig_tx, orig_ty; /* 原始目标 */
    float battery;        /* 当前电量 */
    RobotState state;     /* 当前状态 */
    FILE* logfile;        /* 日志文件指针 */
    RRTNode* path;        /* 当前路径 */
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