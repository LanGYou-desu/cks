#define SHOW_MOCK_H
#ifdef SHOW_MOCK_H

/*��ʾ�켣*/
void draw_trace(int robonum);

/*ģ�����ݳ���*/
void watchMockin(int robonum,int speed,int *item);

/*ģ�����ݳ���*/
void watchMockout(int robonum,int speed,int *item);

/*���ٳ��*/
void quick_charge(ROHEAD *rohp);

/*�ֶ�����*/
void rehand(int flag,int *item);

#endif