#define DRAW_H
#ifdef DRAW_H

/*����������*/
void draw_commoninput(int x,int y,int len,char *s);

/*����������»���*/
void put_inputline(int x,int y,int len);

/*������ť*/
void draw_button(int x1,int y1,int x2,int y2);

/*���Ʒ���ȷ�Ͻ���*/
void draw_return_comfirm(int i);

/*��ʾ���*/
void show_gb(int x,int y);

/*������ʾ��*/
void draw_showbox(int x,int y);

/*����������*/
void draw_robot(int x,int y,int flag);   

/*���������ϵĻ���*/
void draw_item(int x,int y,int type,int floor,int flag);

/*���������*/
void draw_mainselector();


#endif