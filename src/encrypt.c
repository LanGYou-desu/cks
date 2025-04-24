#include"allfunc.h"

// ѭ������nλ
unsigned char rotate_left(unsigned char byte, int n) 
{
    return (byte << n) | (byte >> (8 - n));
}

// ѭ������nλ
unsigned char rotate_right(unsigned char byte, int n) 
{
    return (byte >> n) | (byte << (8 - n));
}

// �����ַ�����ȷ�����ܺ���\0��
void encrypt_string(unsigned char *str, unsigned char key) {

    int i;
    int len = strlen(str) + 1; // ������ֹ��\0
    for (i = 0; i < len; i++) 
    {
        // ���ܲ���������3λ + �����Կ
        str[i] = rotate_left(str[i], 3);
        str[i] ^= key;
        
        // ������ܺ����0x00����Ϊ0x00���滻Ϊ0xFF�����Զ��壩
        if (str[i] == '\n') 
        {
            str[i] = 0xFF; // ����ʱ�軹ԭ
        }
    }
}

// �����ַ�������ԭ����ʱ��0x00��
void decrypt_string(unsigned char *str, unsigned char key) 
{
    int i;
    int len = strlen(str) + 1; // ���ܺ���ַ������ȿ��ܲ�׼ȷ������ǰ��¼
    for (i = 0; i < len; i++) 
    {
        // ��ԭ����ʱ��0x00�滻
        if (str[i] == 0xFF) 
        {
            str[i] = '\n';
        }
        
        // ���ܲ����������Կ + ����3λ
        str[i] ^= key;
        str[i] = rotate_right(str[i], 3);
    }
}

/**********************
����˵���������û���Ϣ���� 
����˵�����û��ṹ�� 
����ֵ˵��:0������ɹ�   -1�� ����ʧ�� 
**********************/
int save_user(USER temp)
{
    if (repeat_user("user/user.dat", temp.account) == 1) 
    {
        FILE *fp = fopen("user/user.dat", "a");
        if (fp == NULL) 
        {
            prt_hz24(410, 380, "�޷����ļ���", 10, "HZK\\Hzk24h");
            return -1;
        }
        encrypt_string(temp.password, 0xA5); // �������룬ʹ��0xA5��Ϊ��Կ
        fprintf(fp, "%s %s\n", temp.account, temp.password);
        fclose(fp);
        return 0;
    } 
	else if(repeat_user("user/user.dat", temp.account) == 0)
    {
        prt_hz24(420, 380, "�û��Ѵ��ڣ�", 10, "HZK\\Hzk24h");
        return -1;
    }
}


/********************************************
����˵������¼��Ϣ�Ա�У�麯�� 
����˵�����û����Ա��û��������� 
����ֵ˵��:0:  �и��û�����������ȷ   -1�� �û������ڻ��������
**********************/
int Check_info(const char *filename, char *account, char *password)
{
    char line[40];
    char expected[40];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        return -1; // �ļ������ڣ��û�������
    }

    encrypt_string(password, 0xA5); // �������룬ʹ��0xA5��Ϊ��Կ

    strcpy(expected, account);
    strcat(expected, " ");
    strcat(expected, password);
    strcat(expected, "\n");

    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        if (strcmp(line, expected) == 0) 
        {
            fclose(fp);
            return 0; // �ҵ�ƥ���û�
        }
    }

    fclose(fp);
    return -1; // �û������ڻ��������
}

/********************************************
����˵�����ظ�ע��У�麯��
����˵�����û����Ա��û��� 
����ֵ˵��:0:  �и��û�   1�� �޸��û�
**********************/
int repeat_user(const char* filename, char *account)
{
    int i = 0;
    char line[40];
    char temp[20];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        return 1; // �ļ���ʧ�ܣ������û�������
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        i = 0;
        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
        {
            temp[i] = line[i];
            i++;
        }
        temp[i] = '\0'; // ȷ���ַ����� '\0' ��β
        if (strcmp(temp, account) == 0)
        {
            fclose(fp);
            return 0; // �ҵ�ƥ���û�
        }
    }
    fclose(fp);
    return 1; // δ�ҵ�ƥ���û�
}