#define ROBOLIST_H
#ifdef ROBOLIST_H

//路径规划算法机器人结构体
typedef struct Robot {
    int id;                // 唯一标识符
    int x, y;              // 当前中心坐标（整数）
    int tx, ty;            // 当前目标坐标
    int orig_tx, orig_ty;  // 原始目标坐标（充电前）
    int prev_x, prev_y;    // 上次记录坐标（用于路径平滑）
    int hist_dx[5];        // X方向移动历史
    int hist_dy[5];        // Y方向移动历史
    int hist_index;        // 历史记录索引
    int escape_count;      // 脱困尝试计数器
    int same_pos_count;    // 相同位置计数器
    float battery;         // 剩余电量（0-100）
    int cargo_type;        // 携带货物类型
    int reached;           // 是否到达目标
    int state;             // 0-工作中 1-前往充电 2-充电中
    FILE* logfile;         // 日志文件指针
    struct Robot* next;    // 链表指针
} Robot;

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
void setTarget(Robot *p, int tx, int ty);

#endif