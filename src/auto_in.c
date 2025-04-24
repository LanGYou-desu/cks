#include"allfunc.h"

int auto_in(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp)
{
    int i;
    int key;
    int enter_flag = 0;
    int select_flag = 0;
    int robonum = rohp->length;
    
    Robot *robot = NULL;

    for(i=0;i<3;i++)
    {
        statistics_in[i]=statistics_in[i]+item[i];
    }

    mouse_off(&mouse);
    draw_auto_in(rohp);
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        key=0;
        if(kbhit())
        {
            key=getch();
        }
        if(key==0X0D&&enter_flag==0)//�س���
        {
            enter_flag = 1;
            robot = createRoboList(rohp);
            turn_list(rohp, robot);
            path_in(robot, robonum, item, shhp);
            turn_list_back(rohp, robot);
            draw_auto_in(rohp);
            init_item(item,shhp);
        }

        if(mouse.x>=924&&mouse.y<=50&&select_flag==0)
        {
            select_flag=1;
            draw_selecter();
        }
        else if(!(mouse.x>=924&&mouse.y<=250)&&select_flag==1)
        {
            select_flag=0;
            bar1(923,0,1024,250,0XFFFF);
            draw_mock_select();
        }

        if(select_flag==1)
        {
            if(mouse_press(924,0,1024,50)==1)
            {
                draw_auto_in(rohp);
                reset_shelf(shhp, item);
                robot = createRoboList(rohp);
                turn_list(rohp, robot);
                path_in(robot, robonum, item, shhp);
                turn_list_back(rohp, robot);
                draw_auto_in(rohp);
                init_item(item,shhp);
            }
            else if(mouse_press(924,50,1024,100)==1)
            {
                draw_trace(rohp->length);
            }
            else if(mouse_press(924,100,1024,150)==1)
            {
                draw_auto_in(rohp);
                reset_shelf(shhp, item);
                watchMock(rohp->length,10);
                draw_auto_in(rohp);
                init_item(item,shhp);
            }
            else if(mouse_press(924,150,1024,200)==1)
            {
                draw_auto_in(rohp);
                reset_shelf(shhp, item);
                watchMock(rohp->length,1);
                draw_auto_in(rohp);
                init_item(item,shhp);
            }   
            else if(mouse_press(924,200,1024,250)==1)
            {
                quick_charge(rohp);
                prt_hz24(464,620,"�����ϣ�",0X0000,"HZK\\Hzk24h");
                delay(500);
                bar1(464,620,900,650,0XFFFF);
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

void path_in(Robot *robot, int robonum, int *item, SHHEAD *shhp) 
{
    /*============= �������� =============*/
    int i, j;      
    int key;                 
    int original_items[3];          // ԭʼ������������
    int remaining_assignments[3];   // ʣ������������
    int delivered_items[3] = {0};   // ���ʹ���������
    int available_types[3];         // ���û������ͻ���
    int num_available;              // ������������
    int completion_flag;            // ��ɱ�־
    int selected_type;              // ���ѡ�еĻ�������
    int random_target;              // ���Ŀ���ѡ��

    Robot *p = robot;               // ����������ָ��
 
    /*============= ��ʼ���׶� =============*/
    mouse_off(&mouse);              // ���������
    robotlist = robot;              // ��ȫ�ֻ������б�

    // ��ʼ������״̬������ԭʼ���ݱ��ݣ�
    for(i = 0; i < 3; i++) 
    {
        original_items[i] = item[i];
        remaining_assignments[i] = item[i];
    }

    /*============= ������ѭ�� =============*/
    while(1) 
    {
        key = 0;
        if(kbhit())
        {
            key=getch();
        }
        if(key == 0X1B) // ESC���˳�
        {
            break;
        }

        /*-- �׶�1������������ --*/
        completion_flag = 1;
        for(i = 0; i < 3; i++) 
        {
            if(delivered_items[i] < original_items[i]) 
            {
                completion_flag = 0;
                break;
            }
        }
        if(completion_flag) 
        {
            break;
        }

        /*-- �׶�2��������� --*/
        p = robot;
        while(p != NULL) 
        {
            /* ������Ч���������б� */
            num_available = 0;
            for(j = 0; j < 3; j++) 
            {
                if(remaining_assignments[j] > 0) 
                {
                    available_types[num_available++] = j;
                }
            }
            if(num_available == 0)
            {
                break;
            }

            /* ִ��������� */
            selected_type = available_types[rand() % num_available];
            remaining_assignments[selected_type]--;
            p->cargo_type = selected_type + 1;  // ����1-3

            /* ����Ŀ��� */
            switch(p->cargo_type) 
            {
                case 1: setTarget(p, point[5].x, point[5].y); 
                        break;

                case 2: random_target = 6 + (rand() % 2);
                        setTarget(p, point[random_target].x, point[random_target].y);
                        break;

                case 3: setTarget(p, point[8].x, point[8].y); 
                        break;
            }

            p = p->next;
        }

        /*-- �׶�3��ִ������ --*/
        robotlist = robot;
        mainLoop(robonum);  // ����ִ��ֱ�����

        /*-- �׶�4���ʹﴦ�� --*/
        p = robot;
        while(p != NULL) 
        {
            if(p->cargo_type != 0) 
            {
                // ִ��������
                item_in(shhp, p->cargo_type);
                update_shelf(p->cargo_type, shhp);
                
                // �����ʹ������
                delivered_items[p->cargo_type - 1]++;
                
                // ����״̬
                p->cargo_type = 0;
                setTarget(p, point[8 + p->id].x, point[8 + p->id].y); // ���س�����
            }
            p = p->next;
        }

        /*-- �׶�5��������ʼ�� --*/
        robotlist = robot;
        mainLoop(robonum);  // ������ʼ��
    }

    /*============= �������� =============*/
    mouse_on(mouse);  // �ָ������ʾ
}

void draw_auto_in(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    ROBO rob;

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(120,0,"image\\maptwo.bmp");
    bar1(380,680,650,760,0XFFFF);
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"����",32,32,0X0000);

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
    SHNODE *p = NULL;

    if(type==0)
    {
        return;
    }

    p=find_shelf(type,hp);

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
