#include"allfunc.h"

int robo_menu(int *flag,int *robonum,ROHEAD **rohp)
{   
    char temp[3];
    int init=*robonum;
    int robochange=*robonum;

    mouse_off(&mouse);
    draw_robo_menu();
    mouse_on(mouse);

    if(*robonum>3||*robonum<1)
    {
        *robonum=0;
    }

    itoa(*robonum,temp,10);
    put_asc16_size(514,406,2,2,temp,0X0000);
    
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            if(robochange!=*robonum&&*robonum>0)
            {
                free_robolist(*rohp);//����������������ĳɹ����ͷŻ������������³�ʼ������������
                *rohp=init_robolist(*robonum);
                *rohp=create_robolist(*rohp);
            }
            *flag=3;
            return 0;
        }
        if(mouse_press(470,391,553,439)==1)
        {
            mouse_off(&mouse);
            bar1(470,391,553,439,0XFFFF);
            put_inputline(470,439,100);
            input(510,392,temp,2,470,391,553,439);
            *robonum=atoi(temp);
            if(*robonum>3||*robonum<1)
            {
                *robonum=0;
                free_robolist(*rohp);//������벻�Ϸ����ͷŻ������������³�ʼ������������
                *rohp=init_robolist(*robonum);
                prt_hz24(390,459,"������һ����֮�������",0X0000,"HZK\\Hzk24h");
                delay(500);
                return 0;
            }
            else if(*robonum<=3&&*robonum>=1&&init!=*robonum)
            {
               prt_hz24(472,459,"���ĳɹ�",0X0000,"HZK\\Hzk24h");
               init=*robonum;
               delay(500);
               bar1(343,459,700,491,0XFFFF);
            }
            else if(*robonum<=3&&*robonum>=1&&init==*robonum)
            {
               prt_hz24(472,459,"���ֲ���",0X0000,"HZK\\Hzk24h");
               delay(500);
               bar1(343,459,700,491,0XFFFF);
            }
            mouse_on(mouse);
        }
    }

    return 0;
}

void draw_robo_menu()
{
    bar1(0,0,1024,768,0XFFFF);
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"����",32,32,0X0000);
    draw_commoninput(470,439,100,"");
    puthz(390,309,"�����������������",32,32,0X0000);
    Readbmp64k(110,200,"image\\robot.bmp");
}

char* itoa(int value, char* string, int radix)
{
	char tmp[33];
	char* tp = tmp;
	int i;
	unsigned v;
	int sign;
	char* sp;
	if (radix > 36 || radix <= 1)
	{
		return 0;
	}
	sign = (radix == 10 && value < 0);
	if (sign)
		v = -value;
	else
		v = (unsigned)value;
 
	while (v || tp == tmp)
	{
		i = v % radix;
		v = v / radix;
		if (i < 10)
			*tp++ = i + '0';
		else
			*tp++ = i + 'a' - 10;
	}
	if (string == 0)
		string = (char*)malloc((tp - tmp) + sign + 1);
	sp = string;
	if (sign)
		*sp++ = '-';
	while (tp > tmp)
		*sp++ = *--tp;
	*sp = 0;
	return string;
}
