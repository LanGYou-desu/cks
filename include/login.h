#ifndef LOGIN_H
#define LOGIN_H

/*��¼*/
int login(int *flag);
void draw_login();

/*ע��*/
int user_register(int *flag);
void draw_register();

/*��ȡ�˺�*/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

/*��ȡ����*/
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

#endif