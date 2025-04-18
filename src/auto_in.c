#include"allfunc.h"

int auto_in(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int key;
    int select_flag = 0;
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
        if(key==0X0D)//回车键
        {

        }

        if(mouse.x>=924&&mouse.y<=50&&select_flag==0)
        {
            select_flag=1;
            draw_selecter();
        }
        else if(!(mouse.x>=924&&mouse.y<=100)&&select_flag==1)
        {
            select_flag=0;
            bar1(923,0,1024,100,0XFFFF);
            draw_mock_select();
        }

        if(select_flag==1)
        {
            if(mouse_press(924,0,1024,50)==1)
            {
                //remock();
            }
            else if(mouse_press(924,50,1024,100)==1)
            {
                //watchMock();
            }
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
    randomize();
    mouse_off(&mouse);

    setRobotPoint(robot,1,5);
    setRobotPoint(robot,2,6);
    setRobotPoint(robot,3,3);

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

    draw_mock_select();
    
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
                if(p->shelf.item[i][j]==0&&p->shelf.item[i][j-1]==1)
                {
                    p->shelf.item[i][j]=1;
                    p->shelf.num++;
                    return;
                }
            }
        }
    }
}
