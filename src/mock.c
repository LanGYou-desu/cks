#include"allfunc.h"

int auto_flag=1;

int mock_menu(int *flag,int *robonum,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    auto_flag=1;
    
    mouse_off(&mouse);
    draw_mock_menu(robonum,item);
    mouse_on(mouse);

    reset_shelf(shhp,item);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;//����
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(1,item)==1&&auto_flag==0)
        {
            *flag=12;//���
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(1,item)==1&&auto_flag==0)
        {
            *flag=13;//����
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(1,item)==0&&auto_flag==0)
        {
            prt_hz24(469,290,"��������",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(1,item)==0&&auto_flag==0)
        {
            prt_hz24(469,290,"��������",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(*robonum,item)==1&&auto_flag==1)
        {
            *flag=9;//���
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(*robonum,item)==1&&auto_flag==1&&judge_itemnum(item)==1)
        {
            *flag=8;//����
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(*robonum,item)==0&&auto_flag==1)
        {
            prt_hz24(469,290,"��������",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(*robonum,item)==0&&auto_flag==1)
        {
            prt_hz24(469,290,"��������",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(*robonum,item)==1&&auto_flag==1&&judge_itemnum(item)==0)
        {
            prt_hz24(469,290,"���ﲻ�㣡",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,335,653,430)==1&&auto_flag==1)
        {
            draw_hand(item);
            auto_flag=0;//�ֶ�
            continue;
        }
        else if(mouse_press(374,335,653,430)==1&&auto_flag==0)
        {
            draw_mock_menu(robonum,item);
            auto_flag=1;//�Զ�
            continue;
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//�����˻�
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 5;//���û���
            return 0;
        }
        else if(mouse_press(0,250,100,350) == 1)
        {
            *flag = 6;//�������
            return 0;
        }
        else if(mouse_press(0,450,100,550) == 1)
        {
            *flag = 10;//�ֿ�Ԥ��
            return 0;
        }
        else if(mouse_press(0,550,100,650) == 1)
        {
            *flag = 11;//�������
            return 0;
        }
        else if(mouse_press(0,650,100,750) == 1)
        {
            mouse_off(&mouse);
            draw_return_comfirm(1);
            mouse_on(mouse);
            while(1){
                mouse_show(&mouse);
                if(mouse_press(331,415,470,460) == 1)
                {
                    logout();
                    exit(0);
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
    }
}

void draw_mock_menu(int *robonum,int *item)
{
    char temp[3];
    
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");

    draw_button(374,335,653,430);
    draw_button(374,465,653,560);
    draw_button(374,595,653,690);
    puthz(470,359,"�Զ�",48,48,0X0000);
    puthz(470,489,"���",48,48,0X0000);
    puthz(470,619,"����",48,48,0X0000);

    puthz(280,100,"��ǰ����������Ϊ��",48,48,0X0000);
    puthz(280,160,"��ǰ���������ֱ�Ϊ��",48,48,0X0000);

    itoa(*robonum,temp,10);
    put_asc16_size(710,103,3,3,temp,0X0000);

    itoa(item[0],temp,10);
    put_asc16_size(361,215,3,3,temp,0X0000);

    itoa(item[1],temp,10);
    put_asc16_size(505,215,3,3,temp,0X0000);

    itoa(item[2],temp,10);
    put_asc16_size(649,215,3,3,temp,0X0000);

    draw_mainselector();
    bar1(0,350,100,450,0XD69A);
    puthz(18,364,"��ʼ",32,32,0X0000);
    puthz(18,404,"ģ��",32,32,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(0,450,100,450,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
}

void draw_hand(int *item)
{
    char temp[3];

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");

    draw_button(374,335,653,430);
    draw_button(374,465,653,560);
    draw_button(374,595,653,690);
    puthz(470,359,"�ֶ�",48,48,0X0000);
    puthz(470,489,"���",48,48,0X0000);
    puthz(470,619,"����",48,48,0X0000);

    puthz(283,100,"��ǰΪ�ֶ�����ģʽ",48,48,0X0000);
    puthz(280,160,"��ǰ���������ֱ�Ϊ��",48,48,0X0000);

    itoa(item[0],temp,10);
    put_asc16_size(361,215,3,3,temp,0X0000);

    itoa(item[1],temp,10);
    put_asc16_size(505,215,3,3,temp,0X0000);

    itoa(item[2],temp,10);
    put_asc16_size(649,215,3,3,temp,0X0000);

    draw_mainselector();
    bar1(0,350,100,450,0XD69A);
    puthz(18,364,"��ʼ",32,32,0X0000);
    puthz(18,404,"ģ��",32,32,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(0,450,100,450,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
}

void draw_mock_select()
{
    bar1(924,0,1024,50,0X67FC);
    puthz(942,9,"����",32,32,0X0000);
}

void draw_selecter()
{
    bar1(924,0,1024,50,0X67FC);
    Line_Thick(923,50,1024,50,1,0X0000);
    bar1(924,50,1024,100,0X67FC);
    Line_Thick(923,100,1024,100,1,0X0000);
    bar1(924,100,1024,150,0X67FC);
    Line_Thick(923,150,1024,150,1,0X0000);
    bar1(924,150,1024,200,0X67FC);
    Line_Thick(923,200,1024,200,1,0X0000);
    bar1(924,200,1024,250,0X67FC);

    puthz(926,13,"����ģ��",24,24,0X0000);
    puthz(926,63,"��ʾ�켣",24,24,0X0000);
    puthz(926,113,"���ٲ���",24,24,0X0000);
    puthz(926,163,"���ٲ���",24,24,0X0000);
    puthz(926,213,"���ٳ��",24,24,0X0000);
}

int judge_mock(int robonum,int *item)
{
   if(robonum==0||(item[0]==0&&item[1]==0&&item[2]==0))
   {
       return 0;
   }
   else
   {
       return 1;
   }
}

int judge_itemnum(int *item)
{
    int i;
    for(i=0;i<3;i++)
    {
        if(statistics_in[i]-statistics_out[i]-item[i]<0)
        {
            return 0;
        }
    }
    return 1;
}

int random_num()
{
    srand((unsigned)time(NULL));    
    return rand()%3;
}

SHNODE *find_shelf(int type,SHHEAD *hp)
{
    SHNODE *p=hp->head;
    while(p!=NULL)
    {
        if(p->shelf.type==type)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

void update_shelf(int type,SHHEAD *hp)
{
    int i,j;
    int temp;
    SHNODE *p=NULL;

    if(type==0)
    {
        return;
    }

    p=find_shelf(type,hp);
    temp=p->shelf.num;

	for(i=0;i<2;i++)
    {
        for(j=0;j<5;j++)
        {
            if(temp==0)
            {
                break;
            }
            temp--;
            draw_item(p->shelf.x,p->shelf.y,type,i,j);
        }
    }
}

void setRobotPoint(Robot *robot, int id, int pointid)
{
    Robot *head = findRobot(robot, id);
    setTarget(head, point[pointid].x, point[pointid].y);
    robotlist=robot;
}

