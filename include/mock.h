#define MOCK_H
#ifdef MOCK_H

/*ģ�����˵�*/
int mock_menu(int *flag, int *robonum, int *item, ROHEAD *rohp, SHHEAD *shhp); 

/*����ģ�����˵�*/
void draw_mock_menu(int *robonum, int *item);

/*�����ֶ���ť*/
void draw_hand(int *item);

/*���ƹ���ѡ��*/
void draw_mock_select();
void draw_selecter();

/*�ж��Ƿ���ģ��*/
int judge_mock(int robonum, int *item);

/*�����*/
int random_num(void);

/*���һ��ܽڵ�*/
SHNODE *find_shelf(int type,SHHEAD *hp);

/*���»���*/
void update_shelf(int type,SHHEAD *hp);

/*Ϊ�������趨Ŀ���*/
void setRobotPoint(Robot *robot, int id, int pointid);

/*��ʾ�켣*/
void draw_trace(int robonum);

#endif