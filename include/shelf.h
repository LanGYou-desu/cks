#define SHELF_H
#ifdef SHELF_H

//货架结构
typedef struct{
    int type;
    int x;
    int y;
    int num;
    int item[2][5];
}SHELF;

//链表结构
typedef struct{
    SHELF shelf;
    struct NODE *next;
}SHNODE;

//链表头
typedef struct{
    SHNODE *head;
    int length;
}SHHEAD;

//初始化货架链表
SHHEAD* init_shelflist();

//创建货架链表
SHHEAD* create_shelflist(SHHEAD* hp,int *item);

//重置货架链表
void reset_shelf(SHHEAD* hp,int *item);

//释放货架链表
void free_shelf(SHHEAD *shhp);

#endif