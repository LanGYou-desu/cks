#include"allfunc.h"

OBS obs[6];
SHELFPOINT shelfpoint[3];
LIFT lift[3];

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
    puthz(18,9,"返回",32,32,0X0000);
    Readbmp64k(120,0,"C:\\cks\\image\\map.bmp");
}

void init_map()
{
    init_obs();
    init_shelfpoint();
    init_lift();
}

void init_obs()
{
    /*入口&出口*/
    obs[0].x1=387;
    obs[0].y1=596;
    obs[0].x2=640;
    obs[0].y2=679;
    /*一类货架*/
    obs[1].x1=303;
    obs[1].y1=344;
    obs[1].x2=723;
    obs[1].y2=427;
    /*二类货架*/
    obs[2].x1=135;
    obs[2].y1=176;
    obs[2].x2=218;
    obs[2].y2=597;
    /*三类货架*/
    obs[3].x1=805;
    obs[3].y1=176;
    obs[3].x2=890;
    obs[3].y2=597;
    /*充电站*/
    obs[4].x1=387;
    obs[4].y1=92;
    obs[4].x2=640;
    obs[4].y2=178;
    /*返回按键*/
    obs[5].x1=0;
    obs[5].y1=0;
    obs[5].x2=100;
    obs[5].y2=50;
}

void init_shelfpoint()
{
    /*一类货架*/
    shelfpoint[0].x=346;
    shelfpoint[0].y=386;
    /*二类货架*/
    shelfpoint[1].x=176;
    shelfpoint[1].y=220;
    /*三类货架*/
    shelfpoint[2].x=849;
    shelfpoint[2].y=220;
}

void init_lift()
{
    /*一类货架*/
    lift[0].x=513;
    lift[0].y=427;
    /*二类货架*/
    lift[1].x=218;
    lift[1].y=301;
    /*三类货架*/
    lift[2].x=805;
    lift[2].y=301;
}