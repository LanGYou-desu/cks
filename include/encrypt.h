#define ENCRYPT_H
#ifdef ENCRYPT_H

typedef struct user {
    char account[20];
    char password[20];
}USER;

// ѭ������nλ
unsigned char rotate_left(unsigned char byte, int n);

// ѭ������nλ
unsigned char rotate_right(unsigned char byte, int n);

// ��������
void encrypt_string(unsigned char *str, unsigned char key);

// ��������
void decrypt_string(unsigned char *str, unsigned char key);

/*����ע����Ϣ*/
int save_user(USER temp);

/*�ж��˺�����*/
int Check_info(const char* filename,char *account,char *password);

/*�ж��ظ��˺�*/
int repeat_user(const char*filename,char *account);

#endif