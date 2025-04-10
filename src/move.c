#include"allfunc.h"

void movef(ROBO *p)
{
    bar1(p->x-25,p->y-25,p->x+25,p->y+25,0XFFFF);
    draw_robot(p->x,p->y-FL,p->flag);
    p->y-=FL;
    delay(SD);
}

void moveb(ROBO *p)
{
    bar1(p->x-25,p->y-25,p->x+25,p->y+25,0XFFFF);
    draw_robot(p->x,p->y+FL,p->flag);
    p->y+=FL;
    delay(SD);
}

void movel(ROBO *p)
{
    bar1(p->x-25,p->y-25,p->x+25,p->y+25,0XFFFF);
    draw_robot(p->x-FL,p->y,p->flag);
    p->x-=FL;
    delay(SD);
}

void mover(ROBO *p)
{
    bar1(p->x-25,p->y-25,p->x+25,p->y+25,0XFFFF);
    draw_robot(p->x+FL,p->y,p->flag);
    p->x+=FL;
    delay(SD);
}