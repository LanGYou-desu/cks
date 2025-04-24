#include"allfunc.h"

int energy_monitor(int *flag,ROHEAD *rohp)
{
    if(rohp->length==0)
    {
       draw_none_robot();
       *flag=4;
       delay(1500);
       return 0;
    }

    mouse_off(&mouse);
    draw_energy_monitor(flag,rohp);
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;
            return 0;
        }
        if(mouse_press(374,595,653,690)==1)
        {
            mouse_off(&mouse);
            charge(rohp);
            prt_hz24(470,565,"充电完毕！",0X0000,"HZK\\Hzk24h");
            delay(500);
            return 0;
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//设置人机
            return 0;
        }
        else if(mouse_press(0,250,100,350) == 1)
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
    }
}

void draw_energy_monitor(int *flag,ROHEAD *rohp)
{
    bar1(0,0,1024,768,0XFFFF);
    bar1(0,0,100,50,0X67FC);
    draw_button(374,595,653,690);
    puthz(18,9,"返回",32,32,0X0000);
    puthz(470,619,"充电",48,48,0X0000);

    if(rohp->length==1)
    {
        Readbmp64k(396,100,"image\\robot.bmp");
        show_energy(rohp);
    }
    else if(rohp->length==2)
    {
        Readbmp64k(186,100,"image\\drobot.bmp");
        show_energy(rohp);
    }
    else if(rohp->length==3)
    {
        Readbmp64k(106,100,"image\\robot.bmp");
        Readbmp64k(420,100,"image\\robot.bmp");
        Readbmp64k(734,100,"image\\robot.bmp");
        show_energy(rohp);
    }
    else
    {
        draw_none_robot();
       *flag=3;
       delay(1500);
       return 0;
    }

    draw_mainselector();
    bar1(0,150,100,250,0XD69A);
    puthz(18,164,"电量",32,32,0X0000);
    puthz(18,204,"监测",32,32,0X0000);
    Line_Thick(0,150,100,150,2,0X0000);
    Line_Thick(0,250,100,250,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
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

void show_energy(ROHEAD *rohp)
{
    int x=0;
    int y=0;
    int energy=0;
    char temp[4];
    RONODE *p=rohp->head;

    if(rohp->length==1)
    {
        x=470;
        while(p!=NULL)
        {
            y=x;
            energy=(int)p->robot.energy;
            itoa(energy,temp,10);
            strcat(temp,"%");
            put_asc16_size(y,445,3,3,temp,0X0000);
            p=p->next;  
        }
    }
    else if(rohp->length==2)
    {
        x=260;
        while(p!=NULL)
        {
            y=x;
            energy=(int)p->robot.energy;
            itoa(energy,temp,10);
            strcat(temp,"%");
            put_asc16_size(y,445,3,3,temp,0X0000);
            x=x+420;
            p=p->next;
        }
    }
    else if(rohp->length==3)
    {
        x=180;
        while(p!=NULL)
        {
            y=x;
            energy=(int)p->robot.energy;
            itoa(energy,temp,10);
            strcat(temp,"%");
            put_asc16_size(y,445,3,3,temp,0X0000);
            x=x+314;
            p=p->next;
        }
    }
}