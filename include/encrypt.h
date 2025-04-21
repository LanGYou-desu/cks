#define ENCRYPT_H
#ifdef ENCRYPT_H

typedef struct user {
    char account[20];
    char password[20];
}USER;

// 循环左移n位
unsigned char rotate_left(unsigned char byte, int n);

// 循环右移n位
unsigned char rotate_right(unsigned char byte, int n);

// 加密数组
void encrypt_string(unsigned char *str, unsigned char key);

// 解密数组
void decrypt_string(unsigned char *str, unsigned char key);

/*保存注册信息*/
int save_user(USER temp);

/*判断账号密码*/
int Check_info(const char* filename,char *account,char *password);

/*判断重复账号*/
int repeat_user(const char*filename,char *account);

#endif