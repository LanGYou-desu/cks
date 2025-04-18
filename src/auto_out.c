#include"allfunc.h"

int auto_out(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int key;
    int select_flag = 0;
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
        if(key==0X0D)//»Ø³µ¼ü
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
            turn_list_back(rohp, robot);
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
    Readbmp64k(120,0,"C:\\cks\\image\\maptwo.bmp");
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"·µ»Ø",32,32,0X0000);
    
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
        p->shelf.num=item[type];
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
        draw_item(p->shelf.x,p->shelf.y,-1,0,4);
        p->shelf.item[1][4]=0;
        p->shelf.num--;
        return;
    }
    else if(p->shelf.item[1][0]==0&&p->shelf.item[0][4]==1)
    {
        draw_item(p->shelf.x,p->shelf.y,-1,0,4);
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
                    draw_item(p->shelf.x,p->shelf.y,-1,i,j);
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