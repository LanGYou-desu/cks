#include"allfunc.h"

int auto_out(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int i;
    int key;
    int enter_flag = 0;
    int select_flag = 0;
    Robot *robot = NULL;

    for(i=0;i<3;i++)
    {
        statistics_out[i]=statistics_out[i]+item[i];
    }

    mouse_off(&mouse);
    draw_auto_out(rohp);
    mouse_on(mouse);

    init_item(item,shhp);

    while(1)
    {
        mouse_show(&mouse);
        key=0;
        if(kbhit())
        {
            key=getch();
        }
        if(key==0X0D&&enter_flag==0)//回车键
        {

            enter_flag = 1;
            robot = createRoboList(rohp);
            turn_list(rohp, robot);
            path_out(robot, rohp->length, item, shhp);
            turn_list_back(rohp, robot);
            draw_auto_in(rohp);
        }

        if(mouse.x>=924&&mouse.y<=50&&select_flag==0)
        {
            select_flag=1;
            draw_selecter();
        }
        else if(!(mouse.x>=924&&mouse.y<=150)&&select_flag==1)
        {
            select_flag=0;
            bar1(923,0,1024,150,0XFFFF);
            draw_mock_select();
        }

        if(select_flag==1)
        {
            if(mouse_press(924,0,1024,50)==1)
            {
                draw_auto_out(rohp);
                reset_shelf(shhp, item);
                init_item(item,shhp);
                robot = createRoboList(rohp);
                turn_list(rohp, robot);
                path_out(robot, rohp->length, item, shhp);
                turn_list_back(rohp, robot);
                draw_auto_in(rohp);
            }
            else if(mouse_press(924,50,1024,100)==1)
            {
                //watchMock();
            }
            else if(mouse_press(924,100,1024,150)==1)
            {
                draw_trace(rohp->length);
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

void path_out(Robot *robot, int robonum, int *item, SHHEAD *shhp) 
{
    /*============= 变量声明 =============*/
    int i, j, k;                       
    int original_stock[3];          // 初始库存备份 [类型1-3]
    int remaining_stock[3];         // 货架剩余库存
    int delivered_items[3] = {0};   // 已出库货物计数
    int available_types[3];         // 可出库货物类型
    int temp_item[3];               // 临时货物类型缓存
    int num_available;              // 可出库类型数量
    int completion_flag;            // 完成标志
    int selected_type;              // 随机选择的货物类型
    int random_exit;                // 随机出口选择
    Robot *p = NULL;                // 机器人链表指针

    /*============= 初始化阶段 =============*/
    mouse_off(&mouse);              // 隐藏鼠标光标
    robotlist = robot;              // 绑定全局机器人列表

    // 初始化库存状态（item[0]-item[2]对应类型1-3的库存）
    for(i = 0; i < 3; i++) 
    {
        original_stock[i] = item[i];
        remaining_stock[i] = item[i];
    }

    /*============= 主工作循环 =============*/
    while(1) 
    {
        /*-- 阶段1：检查完成条件 --*/
        completion_flag = 1;
        for(i = 0; i < 3; i++) 
        {
            if(delivered_items[i] < original_stock[i]) 
            {
                completion_flag = 0;
                break;
            }
        }
        if(completion_flag) 
        {
            break;
        }

        /*-- 阶段2：任务分配 --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            /* 生成可出库货物类型列表 */
            num_available = 0;
            for(j = 0; j < 3; j++) 
            {
                if(remaining_stock[j] > 0) 
                {
                    available_types[num_available++] = j;
                }
            }
            if(num_available == 0) break;

            /* 执行随机分配 */
            selected_type = available_types[rand() % num_available];
            remaining_stock[selected_type]--;    // 减少库存
            temp_item[k] = selected_type + 1;   // 记录货物类型(1-3)

            /* 设置取货路径：出生点 -> 货架升降机 */
            switch(temp_item[k]) 
            {
                case 1: // 一号货架升降机
                        setTarget(p, point[5].x, point[5].y);
                        break;
                case 2: // 二号货架随机选择升降机
                        random_exit = 6 + (rand() % 2);
                        setTarget(p, point[random_exit].x, point[random_exit].y);
                        break;
                case 3: // 三号货架升降机
                        setTarget(p, point[8].x, point[8].y);
                        break;
            }
            k++;
            p->cargo_type = 0;
            p = p->next;
        }

        /*-- 阶段3：前往货架取货 --*/
        robotlist = robot;
        mainLoop(robonum);  // 执行取货路径

        /*-- 阶段4：设置出口路径 --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            if(temp_item[k] != 0) 
            {
                p->cargo_type = temp_item[k];  // 设置货物类型

                // 执行出库操作
                item_out(shhp, p->cargo_type);
                update_shelf(p->cargo_type, shhp);
        
                setTarget(p, point[8 + p->id].x, point[8 + p->id].y);
            }
            k++;
            p = p->next;
        }

        /*-- 阶段5：运送至出口 --*/
        robotlist = robot;
        mainLoop(robonum);

        /*-- 阶段6：出库处理 --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            if(temp_item[k] != 0) 
            {
                // 更新出库计数器
                delivered_items[p->cargo_type - 1]++;
                
                // 重置状态并返回出生点
                p->cargo_type = 0;
                temp_item[k] = 0;  // 清空临时货物类型
                setTarget(p, point[8 + p->id].x, point[8 + p->id].y);
            }
            p = p->next;
        }

        /*-- 阶段7：返回出生点 --*/
        robotlist = robot;
        mainLoop(robonum);
    }

    /*============= 结束处理 =============*/
    mouse_on(mouse);  // 恢复鼠标显示
}

void draw_auto_out(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    ROBO rob;

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"image\\maptwo.bmp");
    bar1(380,680,650,760,0XFFFF);
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
    SHNODE *p=NULL;

    if(type==0)
    {
        return;
    }

    p=find_shelf(type,hp);
    
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
