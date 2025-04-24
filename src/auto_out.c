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
        if(key==0X0D&&enter_flag==0)//�س���
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
                draw_trace(rohp->length);
            }
            else if(mouse_press(924,100,1024,150)==1)
            {
                draw_auto_in(rohp);
                reset_shelf(shhp, item);
                init_item(item,shhp);
                watchMock(rohp->length,10);
                draw_auto_in(rohp);
            }
            else if(mouse_press(924,150,1024,200)==1)
            {
                draw_auto_in(rohp);
                reset_shelf(shhp, item);
                init_item(item,shhp);
                watchMock(rohp->length,1);
                draw_auto_in(rohp);
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
            turn_list_back(rohp, robot);
            freeRoboList(robot);
            return 0;
        }
    }
}

void path_out(Robot *robot, int robonum, int *item, SHHEAD *shhp) 
{
    /*============= �������� =============*/
    int i, j, k;      \
    int key;                 
    int original_stock[3];          // ��ʼ��汸�� [����1-3]
    int remaining_stock[3];         // ����ʣ����
    int delivered_items[3] = {0};   // �ѳ���������
    int available_types[3];         // �ɳ����������
    int temp_item[3];               // ��ʱ�������ͻ���
    int num_available;              // �ɳ�����������
    int completion_flag;            // ��ɱ�־
    int selected_type;              // ���ѡ��Ļ�������
    int random_exit;                // �������ѡ��
    Robot *p = NULL;                // ����������ָ��

    /*============= ��ʼ���׶� =============*/
    mouse_off(&mouse);              // ���������
    robotlist = robot;              // ��ȫ�ֻ������б�

    // ��ʼ�����״̬��item[0]-item[2]��Ӧ����1-3�Ŀ�棩
    for(i = 0; i < 3; i++) 
    {
        original_stock[i] = item[i];
        remaining_stock[i] = item[i];
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

        /*-- �׶�2��������� --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            /* ���ɿɳ�����������б� */
            num_available = 0;
            for(j = 0; j < 3; j++) 
            {
                if(remaining_stock[j] > 0) 
                {
                    available_types[num_available++] = j;
                }
            }
            if(num_available == 0) break;

            /* ִ��������� */
            selected_type = available_types[rand() % num_available];
            remaining_stock[selected_type]--;    // ���ٿ��
            temp_item[k] = selected_type + 1;   // ��¼��������(1-3)

            /* ����ȡ��·���������� -> ���������� */
            switch(temp_item[k]) 
            {
                case 1: // һ�Ż���������
                        setTarget(p, point[5].x, point[5].y);
                        break;
                case 2: // ���Ż������ѡ��������
                        random_exit = 6 + (rand() % 2);
                        setTarget(p, point[random_exit].x, point[random_exit].y);
                        break;
                case 3: // ���Ż���������
                        setTarget(p, point[8].x, point[8].y);
                        break;
            }
            k++;
            p->cargo_type = 0;
            p = p->next;
        }

        /*-- �׶�3��ǰ������ȡ�� --*/
        robotlist = robot;
        mainLoop(robonum);  // ִ��ȡ��·��

        /*-- �׶�4�����ó���·�� --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            if(temp_item[k] != 0) 
            {
                p->cargo_type = temp_item[k];  // ���û�������

                // ִ�г������
                item_out(shhp, p->cargo_type);
                update_shelf(p->cargo_type, shhp);
        
                setTarget(p, point[8 + p->id].x, point[8 + p->id].y);
            }
            k++;
            p = p->next;
        }

        /*-- �׶�5������������ --*/
        robotlist = robot;
        mainLoop(robonum);

        /*-- �׶�6�����⴦�� --*/
        k = 0;
        p = robot;
        while(p != NULL) 
        {
            if(temp_item[k] != 0) 
            {
                // ���³��������
                delivered_items[p->cargo_type - 1]++;
                
                // ����״̬�����س�����
                p->cargo_type = 0;
                temp_item[k] = 0;  // �����ʱ��������
            }
            k++;
            p = p->next;
        }
    }

    /*============= �������� =============*/
    mouse_on(mouse);  // �ָ������ʾ
}

void draw_auto_out(ROHEAD *rohp)
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
