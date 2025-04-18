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

    // Ϊÿ���ڵ�����ڴ沢��ʼ��
    for (i = 0; i < hp->length; i++)
    {
        p = (SHNODE*)malloc(sizeof(SHNODE)); // �����½ڵ�
        if (p == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }

        // ��ʼ���ڵ�����
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

void reset_shelf(SHHEAD* hp,int *item)
{
    SHNODE *p = hp->head;
    int i = 0;

    while (p != NULL) 
    {
        //���û����ϵ���Ʒ����
        p->shelf.num = item[i];
        //���û����ϵ���Ʒ
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