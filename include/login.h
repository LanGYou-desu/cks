#ifndef LOGIN_H
#define LOGIN_H

typedef struct user {
    char account[20];
    char password[20];
}USER;

/*µÇÂ¼*/
int login(int *flag);
void draw_login();

/*×¢²á*/
int user_register(int *flag);
void draw_register();

/*±£´æ×¢²áĞÅÏ¢*/
int save_user(USER temp);

/*ÅĞ¶ÏÕËºÅÃÜÂë*/
int Check_info(const char* filename,char *account,char *password);

/*»ñÈ¡ÕËºÅ*/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

/*»ñÈ¡ÃÜÂë*/
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

/*ÏÔÊ¾¹â±ê*/
void show_gb(int x,int y);

/*ÅĞ¶ÏÖØ¸´ÕËºÅ*/
int repeat_user(const char*filename,char *account);

#endif