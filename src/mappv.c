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
        else if(mouse_press(0,350,100,450) == 1)
        {
            *flag = 7;//开始模拟
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
    
    return 0;
}

void draw_map_preview()
{
    bar1(0,0,1024,768,0XFFFF);
   
    Readbmp64k(120,0,"image\\map.bmp");

    draw_mainselector();
    bar1(0,450,100,550,0XD69A);
    bar1(924,0,1024,768,0XD69A);
    puthz(18,464,"仓库",32,32,0X0000);
    puthz(18,504,"预览",32,32,0X0000);
    Line_Thick(0,450,100,450,2,0X0000);
    Line_Thick(0,550,100,550,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
    Line_Thick(924,0,924,768,2,0X0000);
}