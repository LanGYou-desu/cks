#include"allfunc.h"

int mock_handin(int *flag,int *item)
{
    ROBO rob;
    int t;
    char key;
    char temp[4];
    SHHEAD *shhp;
    
    rob.x=308;
    rob.y=646;
    rob.flag=0;
    rob.energy=100;

    mouse_off(&mouse);
    draw_mock_hand();

    shhp=init_shelflist();
    shhp=create_shelflist(shhp,item);

    while(1)
    {
        key=0;
        t=(int)rob.energy;
        itoa(t,temp,10);
        strcat(temp,"%");
        
        if(kbhit())
        {
            key=getch();
        }
        else
        {
            if((rob.x>386&&rob.x<640)&&(rob.y>92&&rob.y<210))//充电站
            {
                if(rob.energy>=100)
                {
                    rob.energy=100;
                }
                else
                {
                    rob.energy+=0.5;
                }
                bar1(847,20,1000,70,0XFFFF);
                put_asc16_size(847,20,3,3,temp,0X0000);
                delay(50);
            }   
            if((rob.x>386&&rob.x<640)&&(rob.y>661&&rob.y<751)&&rob.flag==0)//入口
            {
                rob.flag=1;
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }
        if(rob.energy<=0)//能量耗尽
        {
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            put_asc16_size(300,300,4,4,"Energy is over",0X0000);
            put_asc16_size(188,400,4,4,"Press any key to exit",0X0000);
            delay(1500);
            getch();
            *flag=7;
            return 0;
        }
        else
        {
            if(key!=0)
            {
                bar1(847,20,1000,70,0XFFFF);
                put_asc16_size(847,20,3,3,temp,0X0000);
            }
            if(key==0X1B)//ESC
            {
                *flag=7;
                return 0;
            }
            else if(key=='w'&&judge_obs(rob.x,rob.y)!=1)
            {
                movef(&rob);
                rob.energy-=0.1;
            }
            else if(key=='s'&&judge_obs(rob.x,rob.y)!=2)
            {
                moveb(&rob);
                rob.energy-=0.1;
            }
            else if(key=='a'&&judge_obs(rob.x,rob.y)!=3)
            {
                movel(&rob);
                rob.energy-=0.1;
            }
            else if(key=='d'&&judge_obs(rob.x,rob.y)!=4)
            {
                mover(&rob);
                rob.energy-=0.1;
            }
        }
    }
}

int mock_handout(int *flag,int *item)
{
    ROBO rob;
    int t;
    char key;
    char temp[4];
    SHHEAD *shhp;
    
    rob.x=308;
    rob.y=646;
    rob.flag=0;
    rob.energy=100;

    mouse_off(&mouse);
    draw_mock_hand();

    shhp=init_shelflist();
    shhp=create_shelflist(shhp,item);

    init_item(item,shhp);

    while(1)
    {
        key=0;
        t=(int)rob.energy;
        itoa(t,temp,10);
        strcat(temp,"%");
        
        if(kbhit())
        {
            key=getch();
        }
        else
        {
            if((rob.x>386&&rob.x<640)&&(rob.y>92&&rob.y<210))//充电站
            {
                if(rob.energy>=100)
                {
                    rob.energy=100;
                }
                else
                {
                    rob.energy+=0.5;
                }
                bar1(847,20,1000,70,0XFFFF);
                put_asc16_size(847,20,3,3,temp,0X0000);
                delay(50);
            }   
            else if((rob.x>386&&rob.x<640)&&(rob.y>661&&rob.y<751)&&rob.flag==0)//入口
            {
                rob.flag=0;
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }
        if(rob.energy<=0)//能量耗尽
        {
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            put_asc16_size(300,300,4,4,"Energy is over",0X0000);
            put_asc16_size(188,400,4,4,"Press any key to exit",0X0000);
            delay(1500);
            getch();
            *flag=7;
            return 0;
        }
        else
        {
            if(key!=0)
            {
                bar1(847,20,1000,70,0XFFFF);
                put_asc16_size(847,20,3,3,temp,0X0000);
            }
            if(key==0X1B)//ESC
            {
                *flag=7;
                return 0;
            }
            else if(key=='w'&&judge_obs(rob.x,rob.y)!=1)
            {
                movef(&rob);
                rob.energy-=0.1;
            }
            else if(key=='s'&&judge_obs(rob.x,rob.y)!=2)
            {
                moveb(&rob);
                rob.energy-=0.1;
            }
            else if(key=='a'&&judge_obs(rob.x,rob.y)!=3)
            {
                movel(&rob);
                rob.energy-=0.1;
            }
            else if(key=='d'&&judge_obs(rob.x,rob.y)!=4)
            {
                mover(&rob);
                rob.energy-=0.1;
            }
        }
    }
}

void draw_mock_hand()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"C:\\cks\\image\\maptwo.bmp");
    
    bar1(0,0,100,50,0X67FC);
    put_asc16_size(26,10,2,2,"ESC",0X0000);
    
    draw_hand_robot(308,646);
    puthz(762,25,"电量：",32,32,0X0000);
    put_asc16_size(847,20,3,3,"100%",0X0000);
}

void draw_hand_robot(int x,int y)
{
    bar1(x-25,y-25,x+25,y+25,0X62CA);
}

// 碰撞检测函数（严格不接触）
int isCollision(int rx1, int ry1, int rx2, int ry2, OBS obs) 
{
    return (rx1 < obs.x2) && (rx2 > obs.x1) && (ry1 < obs.y2) && (ry2 > obs.y1);
}

int judge_obs(int x, int y) 
{
    int i;
    // 检查向上移动（y负方向）
    int rx1 = x - 25;
    int ry1 = y - (25 + FL);  // 使用宏 FL 计算坐标
    int rx2 = x + 25;
    int ry2 = y + (25 - FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 1;
    }

    // 检查向下移动（y正方向）
    ry1 = y - (25 - FL);
    ry2 = y + (25 + FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 2;
    }

    // 检查向左移动（x负方向）
    rx1 = x - (25 + FL);
    rx2 = x + (25 - FL);
    ry1 = y - 25;
    ry2 = y + 25;
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 3;
    }

    // 检查向右移动（x正方向）
    rx1 = x - (25 - FL);
    rx2 = x + (25 + FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 4;
    }

    return 0; // 所有方向均可移动
}
