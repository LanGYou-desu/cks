#include"allfunc.h"

int map_preview(int *flag)
{
    mouse_off(&mouse);
    draw_map_preview();
    mouse_on(mouse);
    
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50) == 1)
        {
            *flag = 3;
            return 0;
        }
    }
    
    return 0;
}

void draw_map_preview()
{
    bar1(0,0,1024,768,0XFFFF);
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"·µ»Ø",32,32,0X0000);
    Readbmp64k(120,0,"image\\map.bmp");
}