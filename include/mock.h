#define MOCK_H
#ifdef MOCK_H

/*ģ�����˵�*/
int mock_menu(int *flag, int *robonum, int *item, ROHEAD *rohp, SHHEAD *shhp); 

/*����ģ�����˵�*/
void draw_mock_menu(int *robonum, int *item);

/*�����ֶ���ť*/
void draw_hand(int *item);

/*�ж��Ƿ���ģ��*/
int judge_mock(int robonum, int *item);

/*���һ��ܽڵ�*/
SHNODE *find_shelf(int type,SHHEAD *hp);

/*���»���*/
void update_shelf(int type,SHHEAD *hp);

#endif