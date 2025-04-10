#include "allfunc.h"

int user_register(int *flag)
{
    USER temp = {0};        //��ʱ�û���Ϣ
	char judge[20] = {0};   //�����ж������Ƿ�һ��

    mouse_off(&mouse);
	draw_register();
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(325,177,705,225) == 1)
        {
            mouse_off(&mouse);
            bar1(325,177,705,225,0xFFFF);
			put_inputline(325,225,380);
            strcpy(temp.account,"\0");
            input(325,177,temp.account,18,325,177,705,225);//��ȡ�˺�
			mouse_on(mouse);
        }
		else if(mouse_press(325,302,705,350) == 1)
		{
			mouse_off(&mouse);
			bar1(325,302,705,350,0xFFFF);
			put_inputline(325,350,380);
			strcpy(temp.password,"\0");
			Getcode(325,302,temp.password,18,325,302,705,350);//��ȡ����
			mouse_on(mouse);
		}
		else if(mouse_press(325,427,705,475) == 1)
		{
			mouse_off(&mouse);
			bar1(325,427,705,475,0xFFFF);
			put_inputline(325,475,380);
			strcpy(judge,"\0");
			Getcode(325,427,judge,18,325,427,705,475);//��ȡ����
			mouse_on(mouse);
		}
		else if(mouse_press(0,0,100,50) == 1)
		{
			*flag = 0;
			return 0;
		}
		if(mouse_press(374,595,653,690) == 1)
		{
			if(strcmp(temp.account,"\0") == 0 || strcmp(temp.password,"\0") == 0 || strcmp(judge,"\0") == 0)
			{
				mouse_off(&mouse);	
				prt_hz24(410,380,"����д������Ϣ��",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 2;
				return 0;
			}
			else if(strcmp(temp.password,judge) != 0)
			{
				mouse_off(&mouse);
				prt_hz24(410,380,"�������벻һ�£�",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 2;
				return 0;
			}
			else
			{
				if(save_user(temp) == 0)
				{
					mouse_off(&mouse);
					prt_hz24(440,380,"ע��ɹ���",10,"HZK\\Hzk24h");
					delay(500);
					*flag = 0;
					return 0;
				}
				else{
					delay(500);
					*flag = 2;
					return 0;
				}
			}
		}
    }
}

void draw_register()
{
	bar1(0,0,1024,768,0XFFFF);
	bar1(0,0,100,50,0X67FC);
	draw_button(374,595,653,690);
    puthz(470,619,"ע��",48,48,0X0000);
	puthz(18,9,"����",32,32,0X0000);
    draw_commoninput(325,225,380,"�������˺�");
    draw_commoninput(325,350,380,"����������");
    draw_commoninput(325,475,380,"���ٴ�ȷ������");
}

int login(int *flag)
{
	USER temp = {0};        //��ʱ�û���Ϣ

	mouse_off(&mouse);
	draw_login();
	mouse_on(mouse);

	while(1)
	{
		mouse_show(&mouse);
		if(mouse_press(325,222,705,270) == 1)
		{
			mouse_off(&mouse);
			bar1(325,222,705,270,0xFFFF);
			put_inputline(325,270,380);
			strcpy(temp.account,"\0");
			input(325,222,temp.account,18,325,222,705,270);//��ȡ�˺�
			mouse_on(mouse);
		}
		else if(mouse_press(325,377,705,425) == 1)
		{
			mouse_off(&mouse);
			bar1(325,377,705,425,0xFFFF);
			put_inputline(325,425,380);
			strcpy(temp.password,"\0");
			Getcode(325,377,temp.password,18,325,377,705,425);//��ȡ����
			mouse_on(mouse);
		}
		else if(mouse_press(0,0,100,50) == 1)
		{
			*flag = 0;
			return 0;
		}
		if(mouse_press(374,595,653,690) == 1)
		{
			if(strcmp(temp.account,"\0") == 0 || strcmp(temp.password,"\0") == 0)
			{
				mouse_off(&mouse);
				prt_hz24(410,325,"����д������Ϣ��",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 1;
				return 0;
			}
			else
			{
				if(Check_info("C://cks/user/user.dat",temp.account,temp.password) == 0)
				{
					mouse_off(&mouse);
					prt_hz24(440,325,"��¼�ɹ���",10,"HZK\\Hzk24h");
					login_flag = 1;
					delay(500);
					*flag = 3;
					return 0;
				}
				else
				{
					mouse_off(&mouse);
					prt_hz24(385,325,"�û������ڻ��������",10,"HZK\\Hzk24h");
					delay(500);
					*flag = 1;
					return 0;
				}
			}
		}
	}
}

void draw_login()
{
	bar1(0,0,1024,768,0XFFFF);
	bar1(0,0,100,50,0X67FC);
	draw_button(374,595,653,690);
	puthz(18,9,"����",32,32,0X0000);
	puthz(470,619,"��¼",48,48,0X0000);
	draw_commoninput(325,270,380,"�������˺�");
	draw_commoninput(325,425,380,"����������");
}


/***����꺯��***/
void show_gb(int x,int y)
{
	Line1(x,y-3,x,y+29,0);
}



/***��ȡ�û�������***/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1)//x1,y1Ϊ��������Ͻ����꣬nameΪ��������ַ��������飬numΪ���鳤��
{
	char showtemp[2]= {0,0};//��ʾ�ַ�
	int key;    			//����ֵ
	int i=0,k,temp;
	int border=x1+4;	    //border��ʾ��ʾͼƬ����߽�
	x1=x1+4;
	y1=y1+15;

	for(i=strlen(name)-1;i>=0;i--)
	{
		*showtemp=name[i];
		prt_asc16_ch(x1+i*8,y1-2,showtemp[0],0);  //��ʾ֮ǰ������ַ������Ա��޸�.
	}                       

	i=strlen(name);         

	while(bioskey(1))		//������뻺����
	{
		bioskey(0);
	}

	border+=8*i;            //���λ��
	
	while(1)     									   /*�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��*/
    {
	    show_gb(border,y1);                            //�����˸ 
		if(bioskey(1)==0||!MouseGet(&mouse))		   //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)				           //��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))       //����Ƿ����������
				{
					break;
				}
			}
		}
		if(bioskey(1))                                 //����Ƿ�������,�������
		{
			temp=bioskey(0)&0x00ff;                    //��ȡ������ַ�ASCII��
			if(temp!='\r'&&temp!='\n')	               //������벻Ϊ�س�����������������������
			{
				if(('0'<=temp&&temp<='9'||('a'<=temp&&temp<='z')/*||temp=='_'*/)&&i<num)	//���Ϊ���ֻ���ĸ���»��ߣ����¼
				{
					bar1(border,y1,border+8, y1+32, 0xffff);   //��չ��λ��
					name[i]=temp;				               //�ַ���������ַ���			
					
					*showtemp=temp;                            //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
					prt_asc16(border,y1-2,showtemp,0);         
					i++;
					name[i]='\0';		//����ַ�����β
					border+=8;          //���λ�ú���
					show_gb(border,y1); //��ʾ���
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//�����ļ��������ִ�Сд����������ļ�����Ҫ���û������ļ��� 
				{						             	//����ע��ʱ�Ͳ����ִ�Сд�� 
					bar1(border,y1,border+8, y1+32, 0xffff);
					temp+=32;                   //��дתСд
					name[i]=temp;				//�ַ���������ַ���			
					
					*showtemp=temp;             //���²���ͬ��
					prt_asc16(border,y1-2,showtemp,0);
					i++;
					name[i]='\0';		
					border+=8;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//����Ƿ�Ϊ�˸������������ǰһ���ַ�
				{
					border-=8;                      //���λ��ǰ��
					bar1(border,y1,border+8, y1+32, 0xffff);//��չ��λ��
					i--;                                    //�ַ������ȼ�һ
					name[i]='\0';                           //�ַ�����β
					bar1(border,y1,border+8, y1+32, 0xffff);//��չ��λ��
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!mouse_press(a1,b1,c1,d1)&&MouseGet(&mouse))		//���������������Ĳ��֣��˳�
		{
			break;
		}
		bar1(border,y1,border+8, y1+32, 0xffff);            //��չ��λ��
		if(bioskey(1)==0||!MouseGet(&mouse))			    //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)				                //��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;                                  //����Ƿ�����������������˳�forѭ�������˳���ʱ
				}
			}
		}
	} 
	bar1(border,y1,border+8, y1+32, 0xffff);//��չ��λ��
}





/* ��ȡ���뺯�� */
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1)//x1,y1Ϊ��������Ͻ����꣬nameΪ��������ַ��������飬numΪ���鳤��
{
	char showtemp[2]= {0,0};
	int key;    			//����ֵ
	int i=0,k,temp;
	int border=x1+4;	    //border��ʾ��ʾͼƬ����߽�
	x1=x1+4;
	y1=y1+16;
	for(i=strlen(code)-1;i>=0;i--)
	{
		*showtemp=code[i];
		Put_Asc16_Size(x1+i*16,y1-2,2,2,'*',0);//��ʾ֮ǰ������ַ������Ա��޸�.
	}
	i=strlen(code);

	while(bioskey(1))					//������뻺����
	{
		bioskey(0);
	}

	border+=16*i;  //���λ��

	while(1)     													//�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��
   {
	   show_gb(border,y1);
		if(bioskey(1)==0||!MouseGet(&mouse))			//��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)	   			//��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
		if(bioskey(1))   //����Ƿ�������,�������
		{
			temp=bioskey(0)&0x00ff;
			if(temp!='\r'&&temp!='\n')	//������벻Ϊ�س�����������������������
			{
				if(('0'<=temp&&temp<='9'||'a'<=temp&&temp<='z'||temp=='_')&&i<num)	//���Ϊ���ֻ���ĸ���»��ߣ����¼
				{
					bar1(border,y1-3,border+16, y1+29, 0xffff);//��չ��λ��
					code[i]=temp;				//�ַ���������ַ���			
					
					*showtemp=temp;
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0); //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
					
					delay(150);                        
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'_',0);
					delay(50);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'*',0);
					
					i++;
					code[i]='\0';		//����ַ�����β
					border+=16;
					show_gb(border,y1);
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//�����ļ��������ִ�Сд����������ļ�����Ҫ���û������ļ��� 
				{							            //����ע��ʱ�Ͳ����ִ�Сд�� 
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					temp+=32;                   //��дתСд
					code[i]=temp;				//�ַ���������ַ���			
					
					*showtemp=temp;             //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);
					
					delay(300);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'_',0);
					delay(100);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'*',0);
					
					i++;
					code[i]='\0';		//����ַ�����β
					border+=16;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//����Ƿ�Ϊ�˸������������ǰһ���ַ�
				{
					border-=16;
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					i--;
					code[i]=0;
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!mouse_press(a1,b1,c1,d1)&&MouseGet(&mouse))		//���������������Ĳ��֣��˳�
		{
			break;
		}
		bar1(border,y1-3,border+16, y1+29, 0xffff);
		if(bioskey(1)==0||!MouseGet(&mouse))			//��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)				//��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
	}
	bar1(border,y1-3,border+16, y1+29, 0xffff);
}


/**********************
����˵���������û���Ϣ���� 
����˵�����û��ṹ�� 
����ֵ˵��:0������ɹ�   -1�� ����ʧ�� 
**********************/
int save_user(USER temp)
{
    if (repeat_user("C://cks/user/user.dat", temp.account) == 1) {
        FILE *fp = fopen("C://cks/user/user.dat", "a");
        if (fp == NULL) {
            prt_hz24(410, 380, "�޷����ļ���", 10, "HZK\\Hzk24h");
            return -1;
        }
        fprintf(fp, "%s %s\n", temp.account, temp.password);
        fclose(fp);
        return 0;
    } 
	else if(repeat_user("C://cks/user/user.dat", temp.account) == 0){
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
    if (fp == NULL) {
        return -1; // �ļ������ڣ��û�������
    }

    strcpy(expected, account);
    strcat(expected, " ");
    strcat(expected, password);
    strcat(expected, "\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strcmp(line, expected) == 0) {
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
    if (fp == NULL) {
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