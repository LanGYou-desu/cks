#ifndef LOGIN_H
#define LOGIN_H

typedef struct user {
    char account[20];
    char password[20];
}USER;

/*��¼*/
int login(int *flag);
void draw_login();

/*ע��*/
int user_register(int *flag);
void draw_register();

/*����ע����Ϣ*/
int save_user(USER temp);

/*�ж��˺�����*/
int Check_info(const char* filename,char *account,char *password);

/*��ȡ�˺�*/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

/*��ȡ����*/
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

/*��ʾ���*/
void show_gb(int x,int y);

/*�ж��ظ��˺�*/
int repeat_user(const char*filename,char *account);

#endif