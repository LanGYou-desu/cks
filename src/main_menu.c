#include"allfunc.h"

int main_menu(int *flag,int *robonum,int *item)
{
    mouse_off(&mouse);
    draw_main_menu();
    mouse_on(mouse);
    
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(0,0,100,50) == 1)
        {
            mouse_off(&mouse);
            draw_return_comfirm(0);
            mouse_on(mouse);
            while(1)
            {
                mouse_show(&mouse);
                if(mouse_press(331,415,470,460) == 1)
                {
                    *flag = 0;//����
                    *robonum = 0;
                    *item = 0;
                    *(item+1) = 0;
                    *(item+2) = 0;
                    return 0;
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
        if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//�����˻�
            return 0;
        }
        if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 6;//�������
            return 0;
        }
        if(mouse_press(0,250,100,350) == 1)
        {
            *flag = 5;//���û���
            return 0;
        }
        if(mouse_press(0,350,100,450) == 1)
        {
            *flag = 7;//��ʼģ��
            return 0;
        }
        if(mouse_press(0,450,100,550) == 1)
        {
            *flag = 10;//�ֿ�Ԥ��
            return 0;
        }
        if(mouse_press(0,550,100,650) == 1)
        {
            *flag = 11;//�������
            return 0;
        }
        if(mouse_press(0,650,100,750) == 1)
        {
            mouse_off(&mouse);
            draw_return_comfirm(1);
            mouse_on(mouse);
            while(1){
                mouse_show(&mouse);
                if(mouse_press(331,415,470,460) == 1)
                {
                    //logout();
                    exit(0);
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
    }
}

void draw_main_menu()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
    Readbmp64k(300,50,"C:\\cks\\image\\nijika.bmp");
    bar1(0,750,100,768,0X67FC);
    
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"����",32,32,0X0000);
    
    bar1(0,50,100,150,0X67FC);
    puthz(18,64,"����",32,32,0X0000);
    puthz(18,104,"�˻�",32,32,0X0000);
    
    bar1(0,150,100,250,0X67FC);
    puthz(18,164,"����",32,32,0X0000);
    puthz(18,204,"���",32,32,0X0000);
   
    bar1(0,250,100,350,0X67FC);
    puthz(18,264,"����",32,32,0X0000);
    puthz(18,304,"����",32,32,0X0000);
    
    bar1(0,350,100,450,0X67FC);
    puthz(18,364,"��ʼ",32,32,0X0000);
    puthz(18,404,"ģ��",32,32,0X0000);

    bar1(0,450,100,550,0X67FC);
    puthz(18,464,"�ֿ�",32,32,0X0000);
    puthz(18,504,"Ԥ��",32,32,0X0000);

    bar1(0,550,100,650,0X67FC);
    puthz(18,564,"����",32,32,0X0000);
    puthz(18,604,"����",32,32,0X0000);

    bar1(0,650,100,750,0X67FC);
    puthz(18,664,"�˳�",32,32,0X0000);
    puthz(18,704,"����",32,32,0X0000);

    Line_Thick(0,50,100,50,2,0X0000);
    Line_Thick(0,150,100,150,2,0X0000);
    Line_Thick(0,250,100,250,2,0X0000);
    Line_Thick(0,350,100,350,2,0X0000);
    Line_Thick(0,450,100,450,2,0X0000);
    Line_Thick(0,550,100,550,2,0X0000);
    Line_Thick(0,650,100,650,2,0X0000);
    Line_Thick(0,750,100,750,2,0X0000);
    Line_Thick(100,0,100,768,2,0X0000);
}

void draw_return_comfirm(int i)
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");

    bar1(331,415,470,460,0X67FC);
    bar1(546,415,685,460,0X67FC);
    puthz(370,422,"ȷ��",32,32,0X0000);
    puthz(585,422,"ȡ��",32,32,0X0000);

    if(i==0)
    {
        puthz(379,270,"ȷ�Ϸ��ص�¼����",32,32,0X0000);
    }
    else if(i==1)
    {
        puthz(410,270,"ȷ���˳�����",32,32,0X0000);
    }
}
