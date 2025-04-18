#include"allfunc.h"

SHHEAD* init_shelflist()
{
    SHHEAD *hp = (SHHEAD*)malloc(sizeof(SHHEAD));
    hp->head = NULL;
    hp->length = 3;
    return hp;
}

SHHEAD* create_shelflist(SHHEAD* hp,int *item)
{
    int i;
    SHNODE *p, *prev = NULL;

    // 为每个节点分配内存并初始化
    for (i = 0; i < hp->length; i++)
    {
        p = (SHNODE*)malloc(sizeof(SHNODE)); // 分配新节点
        if (p == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }

        // 初始化节点数据
        p->shelf.type = i + 1;

        p->shelf.x=shelfpoint[i].x;
        p->shelf.y=shelfpoint[i].y;

        p->shelf.num = 0;

        p->shelf.item[0][0] = 0;
        p->shelf.item[0][1] = 0;
        p->shelf.item[0][2] = 0;
        p->shelf.item[0][3] = 0;
        p->shelf.item[0][4] = 0;
        p->shelf.item[1][0] = 0;
        p->shelf.item[1][1] = 0;
        p->shelf.item[1][2] = 0;
        p->shelf.item[1][3] = 0;
        p->shelf.item[1][4] = 0;

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

void reset_shelf(SHHEAD* hp,int *item)
{
    SHNODE *p = hp->head;
    int i = 0;

    while (p != NULL) 
    {
        //重置货架上的物品数量
        p->shelf.num = item[i];
        //重置货架上的物品
        p->shelf.item[0][0] = 0;
        p->shelf.item[0][1] = 0;
        p->shelf.item[0][2] = 0;
        p->shelf.item[0][3] = 0;
        p->shelf.item[0][4] = 0;
        p->shelf.item[1][0] = 0;
        p->shelf.item[1][1] = 0;
        p->shelf.item[1][2] = 0;
        p->shelf.item[1][3] = 0;
        p->shelf.item[1][4] = 0;

        i++;
        p = p->next;
    }
}

void free_shelf(SHHEAD *hp)
{
    SHNODE *p = hp->head,*q;

    if (hp == NULL) return;

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(hp);
}