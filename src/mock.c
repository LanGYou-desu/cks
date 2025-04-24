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
            *flag=3;//返回
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(1,item)==1&&auto_flag==0)
        {
            *flag=12;//入库
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(1,item)==1&&auto_flag==0)
        {
            *flag=13;//出库
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(1,item)==0&&auto_flag==0)
        {
            prt_hz24(469,290,"数量有误！",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(1,item)==0&&auto_flag==0)
        {
            prt_hz24(469,290,"数量有误！",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(*robonum,item)==1&&auto_flag==1)
        {
            *flag=9;//入库
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(*robonum,item)==1&&auto_flag==1)
        {
            *flag=8;//出库
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1&&judge_mock(*robonum,item)==0&&auto_flag==1)
        {
            prt_hz24(469,290,"数量有误！",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1&&judge_mock(*robonum,item)==0&&auto_flag==1)
        {
            prt_hz24(469,290,"数量有误！",10,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(374,335,653,430)==1&&auto_flag==1)
        {
            draw_hand(item);
            auto_flag=0;//手动
            continue;
        }
        else if(mouse_press(374,335,653,430)==1&&auto_flag==0)
        {
            draw_mock_menu(robonum,item);
            auto_flag=1;//自动
            continue;
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//设置人机
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 6;//电量监测
            return 0;
        }
        else if(mouse_press(0,250,100,350) == 1)
        {
            *flag = 5;//设置货物
            return 0;
        }
        else if(mouse_press(0,450,100,550) == 1)
        {
            *flag = 10;//仓库预览
            return 0;
        }
        else if(mouse_press(0,550,100,650) == 1)
        {
            *flag = 11;//程序介绍
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
                    *flag = 3;//取消
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
    puthz(470,359,"自动",48,48,0X0000);
    puthz(470,489,"入库",48,48,0X0000);
    puthz(470,619,"出库",48,48,0X0000);

    puthz(280,100,"当前机器人数量为：",48,48,0X0000);
    puthz(280,160,"当前货物数量分别为：",48,48,0X0000);

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
    puthz(18,364,"开始",32,32,0X0000);
    puthz(18,404,"模拟",32,32,0X0000);
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
    puthz(470,359,"手动",48,48,0X0000);
    puthz(470,489,"入库",48,48,0X0000);
    puthz(470,619,"出库",48,48,0X0000);

    puthz(283,100,"当前为手动控制模式",48,48,0X0000);
    puthz(280,160,"当前货物数量分别为：",48,48,0X0000);

    itoa(item[0],temp,10);
    put_asc16_size(361,215,3,3,temp,0X0000);

    itoa(item[1],temp,10);
    put_asc16_size(505,215,3,3,temp,0X0000);

    itoa(item[2],temp,10);
    put_asc16_size(649,215,3,3,temp,0X0000);

    draw_mainselector();
    bar1(0,350,100,450,0XD69A);
    puthz(18,364,"开始",32,32,0X0000);
    puthz(18,404,"模拟",32,32,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(0,450,100,450,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
}

void draw_mock_select()
{
    bar1(924,0,1024,50,0X67FC);
    puthz(942,9,"功能",32,32,0X0000);
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

    puthz(926,13,"重新模拟",24,24,0X0000);
    puthz(926,63,"显示轨迹",24,24,0X0000);
    puthz(926,113,"慢速播放",24,24,0X0000);
    puthz(926,163,"快速播放",24,24,0X0000);
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

void draw_trace(int robonum)
{
    int color=1;
    int i=0,j=0;
    int x=0,y=0;    //坐标
    int px=0,py=0;  //上一个坐标
    FILE *fp;

    char tracefile[3][30]={
        "path\\robot1.log",
        "path\\robot2.log",
        "path\\robot3.log"
    };

    for(i=0;i<robonum;i++)
    {
        fp=fopen(tracefile[i],"r");
        if(fp==NULL)
        {
            printf("文件打开失败！\n");
            return;
        }
        if(color==1)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0XE126);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        else if(color==2)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0X0235);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        else if(color==3)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0X13A6);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        color++;
        fclose(fp);
    }
}

void watchMock(int robonum,int speed)
{
    int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
    int px1=0,py1=0,px2=0,py2=0,px3=0,py3=0;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;

    char mockfile[3][30]={
        "path\\robot1.log",
        "path\\robot2.log",
        "path\\robot3.log"
    };

    fp1=fopen(mockfile[0],"r");
    fp2=fopen(mockfile[1],"r");
    fp3=fopen(mockfile[2],"r");

    if(robonum==1)
    {
        while(fscanf(fp1,"%d,%d",&x1,&y1)!=EOF)
        {
            if(px1==0&&py1==0)
            {
                px1=x1;
                py1=y1;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                draw_robot(px1,py1,0);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                draw_robot(x1,y1,0);
                px1=x1;
                py1=y1;
            }
            delay(speed);
        }
    }
    else if(robonum==2)
    {
        while(fscanf(fp1,"%d,%d",&x1,&y1)!=EOF&&fscanf(fp2,"%d,%d",&x2,&y2)!=EOF)
        {
            if(px1==0&&py1==0&&px2==0&&py2==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                draw_robot(px1,py1,0);
                draw_robot(px2,py2,0);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                draw_robot(x1,y1,0);
                draw_robot(x2,y2,0);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }
    else if(robonum==3)
    {
        while(fscanf(fp1,"%d,%d",&x1,&y1)!=EOF&&fscanf(fp2,"%d,%d",&x2,&y2)!=EOF&&fscanf(fp3,"%d,%d",&x3,&y3)!=EOF)
        {
            if(px1==0&&py1==0&&px2==0&&py2==0&&px3==0&&py3==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                px3=x3;
                py3=y3;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                bar1(point[11].x-25,point[11].y-25,point[11].x+25,point[11].y+25,0XFFFF);
                draw_robot(px1,py1,0);
                draw_robot(px2,py2,0);
                draw_robot(px3,py3,0);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                bar1(px3-25,py3-25,px3+25,py3+25,0XFFFF);
                draw_robot(x1,y1,0);
                draw_robot(x2,y2,0);
                draw_robot(x3,y3,0);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}