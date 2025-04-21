#ifndef LOGIN_H
#define LOGIN_H

/*µÇÂ¼*/
int login(int *flag);
void draw_login();

/*×¢²á*/
int user_register(int *flag);
void draw_register();

/*»ñÈ¡ÕËºÅ*/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

/*»ñÈ¡ÃÜÂë*/
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

#endif