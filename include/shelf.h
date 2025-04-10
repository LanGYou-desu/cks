#define SHELF_H
#ifdef SHELF_H

//���ܽṹ
typedef struct{
    int type;
    int x;
    int y;
    int num;
    int item[2][5];
}SHELF;

//����ṹ
typedef struct{
    SHELF shelf;
    struct NODE *next;
}SHNODE;

//����ͷ
typedef struct{
    SHNODE *head;
    int length;
}SHHEAD;

//��ʼ����������
SHHEAD* init_shelflist();

//������������
SHHEAD* create_shelflist(SHHEAD* hp,int *item);

//���û�������
void reset_shelf(SHHEAD* hp,int *item);

//�ͷŻ�������
void free_shelf(SHHEAD *shhp);

#endif