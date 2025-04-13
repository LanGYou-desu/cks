#include"allfunc.h"

int auto_out(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int key;
    Robot *robot = createRoboList(rohp);

    turn_list(rohp, robot);

    mouse_off(&mouse);
    draw_auto_out(rohp);
    mouse_on(mouse);

    init_item(item,shhp);

    while(1)
    {
        mouse_show(&mouse);
        if(kbhit())
        {
            key=getch();
        }
        if(key==0X0D)//�س���
        {
           
        }
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=7;
            freeRoboList(robot);
            return 0;
        }
    }
}

void draw_auto_out(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    ROBO rob;

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,6,"C:\\cks\\image\\maptwo.bmp");
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"����",32,32,0X0000);
    
    while(p!=NULL)
    {
        rob=p->robot;
        draw_robot(rob.x,rob.y,rob.flag);
        p=p->next;
    }
}

void init_item(int *item,SHHEAD *shhp)
{
    int i;
    int j;
    int type=0;
    int temp[3];
    SHNODE *p=shhp->head;

    for(i=0;i<3;i++)
    {
        temp[i]=item[i];
    }

    while(p!=NULL)
    {
        for(i=0;i<2;i++)
        {
            for(j=0;j<5;j++)
            {
                if(temp[type]==0)
                {
                    break;
                }
                p->shelf.item[i][j]=1;
                temp[type]--;
                draw_item(p->shelf.x,p->shelf.y,p->shelf.type,i,j);
            }
            if(temp[type]==0)
            {
                break;
            }
        }
        p=p->next;
        if(type==2)
        {
            break;
        }
        type++;
    }
}

void item_out(SHHEAD *hp,int type)
{
    int i,j;
    SHNODE *p=find_shelf(type,hp);

    if(p->shelf.num==0)
    {
        return;
    }
    else if(p->shelf.num==10)
    {
        p->shelf.item[1][4]=0;
        p->shelf.num--;
        return;
    }
    else if(p->shelf.item[1][0]==0&&p->shelf.item[0][4]==1)
    {
        p->shelf.item[0][4]=0;
        p->shelf.num--;
        return;
    }
    else
    {
        for(i=0;i<2;i++)
        {
            for(j=0;j<4;j++)
            {
                if(p->shelf.item[i][j]==1&&p->shelf.item[i][j+1]==0)
                {
                    p->shelf.item[i][j]=0;
                    p->shelf.num--;
                    return;
                }
            }
        }
    }
}

void path_out(Robot *robot)
{

}