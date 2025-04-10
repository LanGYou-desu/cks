#define ROBONUM_H
#ifdef ROBONUM_H

/*机器人设置菜单*/
int robo_menu(int *flag,int *robonum,ROHEAD **rohp);

/*绘制机器人设置菜单*/
void draw_robo_menu();

/*将整数转换为字符串*/
char* itoa(int value, char* string, int radix);

#endif