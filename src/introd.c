#include"allfunc.h"

int introduction(int *flag)
{
    int page=1;

    mouse_off(&mouse);
    draw_introduction();
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;
            return 0;
        }
        
        if(page==1)
        {
            if(mouse_press(924,718,1024,768)==1)
            {
                page=2;
                draw_second_introduction();
                continue;
            }
        }
        else if(page==2)
        {
            if(mouse_press(0,718,100,768)==1)
            {
                page=1;
                draw_introduction();
                continue;
            }
            else if(mouse_press(924,718,1024,768)==1)
            {
                page=3;
                draw_third_introduction();
                continue;
            }
        }
        else if(page==3)
        {
            if(mouse_press(0,718,100,768)==1)
            {
                page=2;
                draw_second_introduction();
                continue;
            }
        }
    }
}

void draw_introduction()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\intro1.bmp");

    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);

    bar1(924,718,1024,768,0X67FC);
    puthz(926,727,"下一页",32,32,0X0000);
}

void draw_second_introduction()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\intro2.bmp");

    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);

    bar1(0,718,100,768,0X67FC);
    puthz(2,727,"上一页",32,32,0X0000);

    bar1(924,718,1024,768,0X67FC);
    puthz(926,727,"下一页",32,32,0X0000);
}

void draw_third_introduction()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\intro3.bmp");

    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);

    bar1(0,718,100,768,0X67FC);
    puthz(2,727,"上一页",32,32,0X0000);
}