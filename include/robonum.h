#define ROBONUM_H
#ifdef ROBONUM_H

/*���������ò˵�*/
int robo_menu(int *flag,int *robonum,ROHEAD **rohp);

/*���ƻ��������ò˵�*/
void draw_robo_menu();

/*������ת��Ϊ�ַ���*/
char* itoa(int value, char* string, int radix);

#endif