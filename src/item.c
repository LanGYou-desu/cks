#include"allfunc.h"

int item_menu(int *flag,int *item,SHHEAD **shhp)
{
    int i=0;
    char temp[3][3];
    mouse_off(&mouse);
    draw_item_menu();
    mouse_on(mouse);

    for(i=0;i<3;i++)
    {
        if(item[i]>10||item[i]<0)
        {
            item[i]=0;
        }
    }

    for(i=0;i<3;i++)
    {
        itoa(item[i],temp[i],10);
        put_asc16_size(314+200*i,406,2,2,temp[i],0X0000);
    }

    while(1){
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50)==1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
            *flag=3;
            return 0;
        }
        if(mouse_press(270,391,370,439)==1)
        {
            mouse_off(&mouse);
            bar1(270,391,370,439,0XFFFF);
            put_inputline(270,439,100);
            input(310,392,temp[0],4,270,391,370,439);
            item[0]=atoi(temp[0]);
            if(item[0]>10||item[0]<0)
            {
                item[0]=0;
                prt_hz24(388,459,"请输入零到十之间的数字",0X0000,"HZK\\Hzk24h");
                delay(1000);
                return 0;
            }
            else
            {
                prt_hz24(272,459,"输入成功",0X0000,"HZK\\Hzk24h");
                delay(1000);
                bar1(200,459,900,491,0XFFFF);
            }
            mouse_on(mouse);
        }
        if(mouse_press(470,391,570,439)==1)
        {
            mouse_off(&mouse);
            bar1(470,391,570,439,0XFFFF);
            put_inputline(470,439,100);
            input(510,392,temp[1],4,470,391,570,439);
            item[1]=atoi(temp[1]);
            if(item[1]>10||item[1]<0)
            {
                item[1]=0;
                prt_hz24(388,459,"请输入零到十之间的数字",0X0000,"HZK\\Hzk24h");
                delay(500);
                return 0;
            }
            else
            {
                prt_hz24(472,459,"输入成功",0X0000,"HZK\\Hzk24h");
                delay(500);
                bar1(200,459,900,491,0XFFFF);
            }
            mouse_on(mouse);
        }
        if(mouse_press(670,391,770,439)==1)
        {
            mouse_off(&mouse);
            bar1(670,391,770,439,0XFFFF);
            put_inputline(670,439,100);
            input(710,392,temp[2],4,670,391,770,439);
            item[2]=atoi(temp[2]);
            if(item[2]>10||item[2]<0)
            {
                item[2]=0;
                prt_hz24(388,459,"请输入零到十之间的数字",0X0000,"HZK\\Hzk24h");
                delay(500);
                return 0;
            }
            else
            {
                prt_hz24(672,459,"输入成功",0X0000,"HZK\\Hzk24h");
                delay(500);
                bar1(200,459,900,491,0XFFFF);
            }
            mouse_on(mouse);
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
            *flag = 4;//设置人机
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
            *flag = 6;//电量监测
            return 0;
        }
        else if(mouse_press(0,350,100,450) == 1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
            *flag = 7;//开始模拟
            return 0;
        }
        else if(mouse_press(0,450,100,550) == 1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
            *flag = 10;//仓库预览
            return 0;
        }
        else if(mouse_press(0,550,100,650) == 1)
        {
            free_shelf(*shhp);//货物数量更改，释放货物链表，重新初始化货物链表
            *shhp=init_shelflist();
            *shhp=create_shelflist(*shhp,item);
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

void draw_item_menu()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(413,490,"image\\box.bmp");

    DrawAestheticPattern(20);

    draw_mainselector();
    bar1(0,250,100,350,0XD69A);
    puthz(18,264,"设置",32,32,0X0000);
    puthz(18,304,"货物",32,32,0X0000);
    Line_Thick(0,250,100,250,2,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
    
    draw_commoninput(270,439,100,"");
    draw_commoninput(470,439,100,"");
    draw_commoninput(670,439,100,"");
    puthz(256,309,"一类货物",32,32,0X0000);
    puthz(456,309,"二类货物",32,32,0X0000);
    puthz(656,309,"三类货物",32,32,0X0000);
}