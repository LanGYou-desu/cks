#define AUTO_IN_H
#ifdef AUTO_IN_H

/*�Զ����*/
int auto_in(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp);

/*�����Զ�������*/
void draw_auto_in(ROHEAD *rohp);

/*�����Ʒ*/
void item_in(SHHEAD *hp,int type);

/*���ģ��*/
void path_in(Robot *robot, int robonum);

#endif