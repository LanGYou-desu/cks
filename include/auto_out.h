#define AUTO_IN_H
#ifdef AUTO_IN_H

/*�Զ�����*/
int auto_out(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp);

/*�����Զ��������*/
void draw_auto_out(ROHEAD *rohp);

/*��ʼ������*/
void init_item(int *item,SHHEAD *shhp);

/*������Ʒ*/
void item_out(SHHEAD *hp,int type);

/*����ģ��*/
void path_out(Robot *robot);

#endif