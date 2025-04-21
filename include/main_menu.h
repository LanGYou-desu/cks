#define MAIN_MENU_H
#ifdef MAIN_MENU_H

/*绘制主菜单*/
void draw_main_menu();

/*主菜单*/
int main_menu(int *flag,int *robonum,int *item);

/*绘制返回确认界面*/
void draw_return_comfirm(int i);

/*生成报告*/
void report();

#endif