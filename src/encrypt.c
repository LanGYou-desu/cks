#include"allfunc.h"

// 循环左移n位
unsigned char rotate_left(unsigned char byte, int n) {
    return (byte << n) | (byte >> (8 - n));
}

// 循环右移n位
unsigned char rotate_right(unsigned char byte, int n) {
    return (byte >> n) | (byte << (8 - n));
}

// 加密字符串（确保加密后无\0）
void encrypt_string(unsigned char *str, unsigned char key) {
    int i;
    int len = strlen(str) + 1; // 包含终止符\0
    for (i = 0; i < len; i++) {
        // 加密操作：左移3位 + 异或密钥
        str[i] = rotate_left(str[i], 3);
        str[i] ^= key;
        
        // 避免加密后出现0x00：若为0x00，替换为0xFF（可自定义）
        if (str[i] == '\n') {
            str[i] = 0xFF; // 解密时需还原
        }
    }
}

// 解密字符串（还原加密时的0x00）
void decrypt_string(unsigned char *str, unsigned char key) {
    int i;
    int len = strlen(str) + 1; // 加密后的字符串长度可能不准确，需提前记录
    for (i = 0; i < len; i++) {
        // 还原加密时的0x00替换
        if (str[i] == 0xFF) {
            str[i] = '\n';
        }
        
        // 解密操作：异或密钥 + 右移3位
        str[i] ^= key;
        str[i] = rotate_right(str[i], 3);
    }
}

/**********************
功能说明：保存用户信息函数 
参数说明：用户结构体 
返回值说明:0：保存成功   -1： 保存失败 
**********************/
int save_user(USER temp)
{
    if (repeat_user("C://cks/user/user.dat", temp.account) == 1) {
        FILE *fp = fopen("C://cks/user/user.dat", "a");
        if (fp == NULL) {
            prt_hz24(410, 380, "无法打开文件！", 10, "HZK\\Hzk24h");
            return -1;
        }
        encrypt_string(temp.password, 0xA5); // 加密密码，使用0xA5作为密钥
        fprintf(fp, "%s %s\n", temp.account, temp.password);
        fclose(fp);
        return 0;
    } 
	else if(repeat_user("C://cks/user/user.dat", temp.account) == 0){
        prt_hz24(420, 380, "用户已存在！", 10, "HZK\\Hzk24h");
        return -1;
    }
}


/********************************************
功能说明：登录信息对比校验函数 
参数说明：用户线性表，用户名，密码 
返回值说明:0:  有该用户，且密码正确   -1： 用户不存在或密码错误
**********************/
int Check_info(const char *filename, char *account, char *password)
{
    char line[40];
    char expected[40];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1; // 文件不存在，用户不存在
    }

    encrypt_string(password, 0xA5); // 加密密码，使用0xA5作为密钥

    strcpy(expected, account);
    strcat(expected, " ");
    strcat(expected, password);
    strcat(expected, "\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strcmp(line, expected) == 0) {
            fclose(fp);
            return 0; // 找到匹配用户
        }
    }

    fclose(fp);
    return -1; // 用户不存在或密码错误
}

/********************************************
功能说明：重复注册校验函数
参数说明：用户线性表，用户名 
返回值说明:0:  有该用户   1： 无该用户
**********************/
int repeat_user(const char* filename, char *account)
{
    int i = 0;
    char line[40];
    char temp[20];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1; // 文件打开失败，假设用户不存在
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        i = 0;
        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
        {
            temp[i] = line[i];
            i++;
        }
        temp[i] = '\0'; // 确保字符串以 '\0' 结尾
        if (strcmp(temp, account) == 0)
        {
            fclose(fp);
            return 0; // 找到匹配用户
        }
    }
    fclose(fp);
    return 1; // 未找到匹配用户
}