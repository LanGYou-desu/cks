#include"allfunc.h"

int energy_monitor(int *flag,ROHEAD *rohp)
{
    int star[8]={0};

    mouse_off(&mouse);
    draw_energy_monitor(rohp);
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;//返回
            return 0;
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//设置人机
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 5;//设置货物
            return 0;
        }
        else if(mouse_press(0,350,100,450) == 1)
        {
            *flag = 7;//开始模拟
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

        if(mouse.x>=282&&mouse.x<=332&&mouse.y>=685&&mouse.y<=735&&star[0]==0&&rohp->length>=1)//机器人1
        {
            star[0]=1;
            bar1(282,685,332,735,0XD69A);
            draw_showbox(138,530);
            show_energy(138,530,rohp,1);
        }
        else if(!(mouse.x>=282&&mouse.x<=332&&mouse.y>=685&&mouse.y<=735)&&star[0]==1&&rohp->length>=1)
        {
            star[0]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse.x>=218&&mouse.x<=268&&mouse.y>=685&&mouse.y<=735&&star[1]==0&&rohp->length>=2)//机器人2
        {
            star[1]=1;
            bar1(218,685,268,735,0XD69A);
            draw_showbox(138,530);
            show_energy(138,530,rohp,2);
        }
        else if(!(mouse.x>=218&&mouse.x<=268&&mouse.y>=685&&mouse.y<=735)&&star[1]==1&&rohp->length>=2)
        {
            star[1]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse.x>=154&&mouse.x<=204&&mouse.y>=685&&mouse.y<=735&&star[2]==0&&rohp->length>=3)//机器人3
        {
            star[2]=1;
            bar1(154,685,204,735,0XD69A);
            draw_showbox(138,530);
            show_energy(138,530,rohp,3);
        }
        else if(!(mouse.x>=154&&mouse.x<=204&&mouse.y>=685&&mouse.y<=735)&&star[2]==1&&rohp->length>=3)
        {
            star[2]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse.x>=135&&mouse.x<=219&&mouse.y>=188&&mouse.y<=607)//一类货架
        {
            if(star[3]==0)
            {
                star[3]=1;
                bar1(132,186,219,609,0XD69A);
                draw_showbox(195,325);
                show_item(195,325,1);
            }
        }
        else if(star[3]==1)
        {
            star[3]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse.x>=471&&mouse.x<=555&&mouse.y>=188&&mouse.y<=607)//二类货架
        {
            if(star[4]==0)
            {
                star[4]=1;
                bar1(468,186,555,609,0XD69A);
                draw_showbox(406,325);
                show_item(406,325,2);
            }
        }
        else if(star[4]==1)
        {
            star[4]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse.x>=807&&mouse.x<=891&&mouse.y>=188&&mouse.y<=607)//三类货架
        {
            if(star[5]==0)
            {
                star[5]=1;
                bar1(804,186,891,609,0XD69A);
                draw_showbox(623,325);
                show_item(623,325,3);
            }
        }
        else if(star[5]==1)
        {
            star[5]=0;
            draw_energy_monitor(rohp);
        }

        if(mouse_press(727,650,924,750)==1)
        {
            charge(rohp);
            prt_hz24(464,620,"充电完毕！",0X0000,"HZK\\Hzk24h");
            delay(500);
            draw_energy_monitor(rohp);
        }
    }
}

void draw_energy_monitor(ROHEAD *rohp)
{
    int count=1;
    RONODE *p=rohp->head;

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"image\\map.bmp");
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);

    draw_mainselector();
    bar1(0,250,100,350,0XD69A);
    puthz(18,264,"信息",32,32,0X0000);
    puthz(18,304,"一览",32,32,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(0,250,100,250,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);

    if(rohp->length!=0)
    {
        bar1(727,650,924,750,0X67FC);
        puthz(777,676,"充电",48,48,0X0000);
        Line_Thick(727,650,727,750,1,0X0000);
        Line_Thick(924,650,924,750,1,0X0000);
        Line_Thick(727,650,924,650,1,0X0000);
        Line_Thick(727,750,924,750,1,0X0000);
    }

    while(p!=NULL)
    {
        if(count==1)
        {
            draw_robot(307,710,0);
        }
        else if(count==2)
        {
            draw_robot(243,710,0);
        }
        else if(count==3)
        {
            draw_robot(179,710,0);
        }
        count++;
        p=p->next;
    }
}

void draw_none_robot()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");
    puthz(350,350,"无已设置机器人",48,48,0X0000);
}

void charge(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    while(p!=NULL)
    {
        p->robot.energy=100;
        p=p->next;
    }
}

void show_energy(int x, int y, ROHEAD *rohp, int type)
{
    int energy=0;
    char temp1[4];
    char temp2[2];
    RONODE *p=rohp->head;

    while(p!=NULL)
    {
        if(p->robot.id==type)
        {
            energy=(int)p->robot.energy;
            itoa(energy,temp1,10);
            strcat(temp1,"%");
            put_asc16_size(x+110,y+65,3,3,temp1,0X0000);
            break;
        }
        p=p->next;
    }

    itoa(type,temp2,10);
    put_asc16_size(x+110,y+21,3,3,temp2,0X0000);

    puthz(x+20,y+26,"编号：",32,32,0X0000);
    puthz(x+20,y+70,"电量：",32,32,0X0000);
}

void show_item(int x, int y, int type)
{
    int energy=0;
    char temp1[4];
    char temp2[2];

    itoa(statistics_in[type-1]-statistics_out[type-1],temp1,10);
    put_asc16_size(x+125,y+65,3,3,temp1,0X0000);
      
    itoa(type,temp2,10);
    put_asc16_size(x+125,y+21,3,3,temp2,0X0000);

    puthz(x+38,y+26,"编号：",32,32,0X0000);
    puthz(x+38,y+70,"货物：",32,32,0X0000);
}