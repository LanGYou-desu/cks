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
            *flag=1;//ת���¼����
            return 0;
        }
        else if(mouse_press(374,465,653,560)==1)
        {
            *flag=2;//ת��ע�����
            return 0;
        }
        else if(mouse_press(665,398,793,430)==1)
        {
            *flag=3;//�ο�ģʽ
            login_flag=0;
            delay(150);
            return 0;
        }
        else if(mouse_press(374,595,653,690)==1)
        {
            logout();//�˳�
        }
    }
}


void draw_welcome()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\welcome.bmp");

    draw_button(374,335,653,430);
    draw_button(374,465,653,560);
    draw_button(374,595,653,690);
    puthz(470,359,"��¼",48,48,0X0000);
    puthz(470,489,"ע��",48,48,0X0000);
    puthz(470,619,"�˳�",48,48,0X0000);

    puthz(665,398,"�ο�ģʽ",32,32,0XC0C0);
    
    put_asc16_size(938,730,2,2,"debug",0X0000);
    put_asc16_size(5,730,2,2,"version:1.1.0",0X0000);
    Line_Thick(0,722,1024,722,2,0X0000);
}

void logout(){
    mouse_off(&mouse);
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\goodbye.bmp");
    free(robotlist);
    free(obs);
    free(point);
    free(shelfpoint);
    free(lift);
    delay(1500);  
    exit(0);
}