#include"allfunc.h"

int mock_handin(int *flag,int *item)
{
    int i;
    int t;
    int random;
    char key;
    char temp[4];
    int titem[3];
    SHHEAD *shhp;
    ROBO rob;
    
    rob.x=308;
    rob.y=710;
    rob.flag=0;
    rob.energy=100;

    for(i=0;i<3;i++)
    {
        titem[i]=item[i];
    }

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
            if((rob.x>386&&rob.x<640)&&(rob.y>92&&rob.y<210))//���վ
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
            if((rob.x>386&&rob.x<640)&&(rob.y>661&&rob.y<751)&&rob.flag==0)//���
            {
                while(1)
                {
                    random=random_num();
                    if(titem[0]==0&&titem[1]==0&&titem[2]==0)
                    {
                        rob.flag=0;
                        break;
                    }

                    if(titem[random]==0)
                    {
                        continue;
                    }
                    else if(titem[random]>0)
                    {
                        rob.flag=random+1;
                        break;
                    }
                    
                }
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }

        if(rob.energy<=0)//�����ľ�
        {
            delay(1000);
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            put_asc16_size(300,300,4,4,"Energy is over",0X0000);
            put_asc16_size(188,400,4,4,"Wait a moment to exit",0X0000);
            delay(1500);
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

        if(rob.flag!=0)
        {
            if((rob.y>=355&&rob.y<=439)&&(rob.x>=219&&rob.x<=249)&&rob.flag==1)
            {
                rob.flag=0;
                titem[0]--;
                item_in(shhp,1);
                update_shelf(1,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=441&&rob.x<=471)&&rob.flag==2)
            {
                rob.flag=0;
                titem[1]--;
                item_in(shhp,2);
                update_shelf(2,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=555&&rob.x<=585)&&rob.flag==2)
            {
                rob.flag=0;
                titem[1]--;
                item_in(shhp,2);
                update_shelf(2,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=777&&rob.x<=807)&&rob.flag==3)
            {
                rob.flag=0;
                titem[2]--;
                item_in(shhp,3);
                update_shelf(3,shhp); 
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }

        if(titem[0]==0&&titem[1]==0&&titem[2]==0)
        {
            draw_robot(rob.x,rob.y,0);
            delay(1000);
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            puthz(416,360,"ģ�����",48,48,0X0000);
            delay(1500);
            *flag=7;
            return 0;
        }
    }
}

int mock_handout(int *flag,int *item)
{
    int t;
    char key;
    char temp[4];
    int titem[3]={0};
    ROBO rob;
    SHHEAD *shhp;
    
    rob.x=308;
    rob.y=710;
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
            if((rob.x>386&&rob.x<640)&&(rob.y>92&&rob.y<210))//���վ
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
            else if((rob.x>386&&rob.x<640)&&(rob.y>661&&rob.y<751)&&rob.flag!=0)//���
            {
                if(rob.flag==1)
                {
                    titem[0]++;
                }
                else if(rob.flag==2)
                {
                    titem[1]++;
                }
                else if(rob.flag==3)
                { 
                    titem[2]++;
                }
                rob.flag=0;
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }

        if(rob.energy<=0)//�����ľ�
        {
            delay(1000);
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            put_asc16_size(300,300,4,4,"Energy is over",0X0000);
            put_asc16_size(188,400,4,4,"Wait a moment to exit",0X0000);
            delay(1500);
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

        if(rob.flag==0)
        {
            if((rob.y>=355&&rob.y<=439)&&(rob.x>=219&&rob.x<=249))
            {
                rob.flag=1;
                item_out(shhp,1);
                update_shelf(1,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=441&&rob.x<=471))
            {
                rob.flag=2;
                item_out(shhp,2);
                update_shelf(2,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=555&&rob.x<=585))
            {
                rob.flag=2;
                item_out(shhp,2);
                update_shelf(2,shhp);
                draw_robot(rob.x,rob.y,rob.flag);
            }
            else if((rob.y>=355&&rob.y<=439)&&(rob.x>=777&&rob.x<=807))
            {
                rob.flag=3;
                item_out(shhp,3);
                update_shelf(3,shhp); 
                draw_robot(rob.x,rob.y,rob.flag);
            }
        }

        if(titem[0]==item[0]&&titem[1]==item[1]&&titem[2]==item[2])
        {
            draw_robot(rob.x,rob.y,0);
            delay(1000);
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
            puthz(416,360,"ģ�����",48,48,0X0000);
            delay(1500);
            *flag=7;
            return 0;
        }
    }
}

void draw_mock_hand()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"C:\\cks\\image\\maptwo.bmp");
    
    bar1(0,0,100,50,0X67FC);
    put_asc16_size(26,10,2,2,"ESC",0X0000);
    
    draw_hand_robot(308,710);
    puthz(762,25,"������",32,32,0X0000);
    put_asc16_size(847,20,3,3,"100%",0X0000);
}

void draw_hand_robot(int x,int y)
{
    bar1(x-25,y-25,x+25,y+25,0X62CA);
}

// ��ײ��⺯�����ϸ񲻽Ӵ���
int isCollision(int rx1, int ry1, int rx2, int ry2, OBS obs) 
{
    return (rx1 < obs.x2) && (rx2 > obs.x1) && (ry1 < obs.y2) && (ry2 > obs.y1);
}

int judge_obs(int x, int y) 
{
    int i;
    // ��������ƶ���y������
    int rx1 = x - 25;
    int ry1 = y - (25 + FL);  // ʹ�ú� FL ��������
    int rx2 = x + 25;
    int ry2 = y + (25 - FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 1;
    }

    // ��������ƶ���y������
    ry1 = y - (25 - FL);
    ry2 = y + (25 + FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 2;
    }

    // ��������ƶ���x������
    rx1 = x - (25 + FL);
    rx2 = x + (25 - FL);
    ry1 = y - 25;
    ry2 = y + 25;
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 3;
    }

    // ��������ƶ���x������
    rx1 = x - (25 - FL);
    rx2 = x + (25 + FL);
    for (i = 0; i < 6; i++) 
    {
        if (isCollision(rx1, ry1, rx2, ry2, obs[i])) return 4;
    }

    return 0; // ���з�������ƶ�
}
