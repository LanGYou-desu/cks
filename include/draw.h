#define DRAW_H
#ifdef DRAW_H

/*画出输入栏*/
void draw_commoninput(int x,int y,int len,char *s);

/*画出输入框下划线*/
void put_inputline(int x,int y,int len);

/*画出按钮*/
void draw_button(int x1,int y1,int x2,int y2);

/*绘制返回确认界面*/
void draw_return_comfirm(int i);

/*显示光标*/
void show_gb(int x,int y);

/*画出显示框*/
void draw_showbox(int x,int y);

/*画出机器人*/
void draw_robot(int x,int y,int flag);   

/*画出货架上的货物*/
void draw_item(int x,int y,int type,int floor,int flag);

/*画出侧边栏*/
void draw_mainselector();


#endif