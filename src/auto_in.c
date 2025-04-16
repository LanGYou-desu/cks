#include"allfunc.h"

int auto_in(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int key;
    int robonum = rohp->length;
    
    Robot *robot = createRoboList(rohp);
    turn_list(rohp, robot);

    mouse_off(&mouse);
    draw_auto_in(rohp);
    mouse_on(mouse);

    path_in(robot, robonum);

    while(1)
    {
        mouse_show(&mouse);
        if(kbhit())
        {
            key=getch();
        }
        if(key==0X0D)//
        {

        }
        if(mouse_press(0,0,100,50)==1)
        {
            *flag=7;
            freeRoboList(robot);
            freeRoboList(robotlist);
            return 0;
        }
    }
}

void path_in(Robot *robot, int robonum)
{
    Robot *head = NULL;

    randomize();
    mouse_off(&mouse);

    head=findRobot(robot,1);
    setTarget(head,200,40);
    head=findRobot(robot,2);
    setTarget(head,500,40);
    head=findRobot(robot,3);
    setTarget(head,800,40);

    robotlist=robot;

       /* 运行仿真 */
    mainLoop(robonum);
    
    mouse_on(mouse);
}


void draw_auto_in(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    ROBO rob;

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"C:\\cks\\image\\maptwo.bmp");
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);
    
    while(p!=NULL)
    {
        rob=p->robot;
        draw_robot(rob.x,rob.y,rob.flag);
        p=p->next;
    }
}

void item_in(SHHEAD *hp,int type)
{
    int i,j;
    SHNODE *p=find_shelf(type,hp);

    if(p->shelf.num==10)
    {
        return;
    }
    else if(p->shelf.num==0)
    {
        p->shelf.item[0][0]=1;
        p->shelf.num++;
        return;
    }
    else if(p->shelf.item[1][0]==0&&p->shelf.item[0][4]==1)
    {
        p->shelf.item[1][0]=1;
        p->shelf.num++;
        return;
    }
    else
    {
        for(i=0;i<2;i++)
        {
            for(j=1;j<5;j++)
            {
                if(p->shelf.item[i][j]==1&&p->shelf.item[i][j-1]==0)
                {
                    p->shelf.item[i][j]=1;
                    p->shelf.num++;
                    return;
                }
            }
        }
    }
}
