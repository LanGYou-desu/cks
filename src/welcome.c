#include"allfunc.h"

int login_flag=0;

int welcome(int *flag)
{
    mouse_off(&mouse);
    draw_welcome();
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(374,335,653,430)==1)
        {
            *flag=1;//转入登录界面
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1)
        {
            *flag=2;//转入注册界面
            return 0;
        }
        else if(mouse_press(665,398,793,430)==1)
        {
            *flag=3;//游客模式
            login_flag=0;
            delay(150);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1)
        {
            logout();//退出
        }
    }
}


void draw_welcome()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"C:\\cks\\image\\welcome.bmp");

    draw_button(374,335,653,430);
    draw_button(374,465,653,560);
    draw_button(374,595,653,690);
    puthz(470,359,"登录",48,48,0X0000);
    puthz(470,489,"注册",48,48,0X0000);
    puthz(470,619,"退出",48,48,0X0000);

    puthz(665,398,"游客模式",32,32,0XC0C0);
    
    put_asc16_size(938,730,2,2,"debug",0X0000);
    put_asc16_size(5,730,2,2,"version:1.1.0",0X0000);
    Line_Thick(0,722,1024,722,2,0X0000);
}

void logout(){
    mouse_off(&mouse);
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"C:\\cks\\image\\goodbye.bmp");
    delay(1500);
    exit(0);
}