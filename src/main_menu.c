#include"allfunc.h"

int statistics_in[3] = {0,0,0}; //ͳ���������
int statistics_out[3] = {0,0,0};//ͳ�Ƴ�������
int timestep = 0;               //ʱ�䲽

int main_menu(int *flag,int *robonum,int *item)
{
    int star=1;

    mouse_off(&mouse);
    draw_main_menu();
    mouse_on(mouse);
    
    while(1)
    {
        mouse_show(&mouse);
        if(star==0)
        {
            if(mouse.x>=717&&mouse.x<=914&&mouse.y>=400&&mouse.y<=500)
            {
                mouse_off(&mouse);
                star=1;
                bar1(717,400,914,500,0XD69A);
                puthz(753,434,"���ɱ���",32,32,0X0000);
                mouse_on(mouse);
            }
        }
        else if(star==1)
        {
            if(!(mouse.x>=717&&mouse.x<=914&&mouse.y>=400&&mouse.y<=500))
            {
                star=0;
                bar1(717,400,914,500,0X67FC);
                puthz(753,434,"���ɱ���",32,32,0X0000);
            }
        }

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
                    statistics_in[0] = 0;
                    statistics_in[1] = 0;
                    statistics_in[2] = 0;
                    statistics_out[0] = 0;
                    statistics_out[1] = 0;
                    statistics_out[2] = 0;
                    *robonum = 0;
                    *item = 0;
                    *(item+1) = 0;
                    *(item+2) = 0;
                    remove("report\\report1.txt");
                    remove("report\\report2.txt");
                    remove("report\\report3.txt");
                    return 0;
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//�����˻�
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 5;//���û���
            return 0;
        }
        else if(mouse_press(0,250,100,350) == 1)
        {
            *flag = 6;//�������
            return 0;
        }
        else if(mouse_press(0,350,100,450) == 1)
        {
            *flag = 7;//��ʼģ��
            return 0;
        }
        else if(mouse_press(0,450,100,550) == 1)
        {
            *flag = 10;//�ֿ�Ԥ��
            return 0;
        }
        else if(mouse_press(0,550,100,650) == 1)
        {
            *flag = 11;//�������
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
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
        else if(mouse_press(717,400,914,500)==1&&login_flag==1)
        {
            mouse_off(&mouse);
            draw_return_comfirm(2);
            mouse_on(mouse);
            while(1)
            {
                mouse_show(&mouse);
                if(mouse_press(331,415,470,460) == 1)
                {
                    *flag=14;//���ɱ���
                    return 0;
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//ȡ��
                    return 0;
                }
            }
        }
        else if(mouse_press(717,400,914,500)==1&&login_flag==0)
        {
            bar1(0,0,1024,768,0XFFFF);
            Readbmp64k(0,0,"image\\bg.bmp");
            puthz(410,360,"���¼��ʹ��",32,32,0X0000);
            delay(1500);
            return 0;
        }
    }
}

void draw_main_menu()
{
    char str1[3];
    char str2[3];

    itoa(statistics_in[0]+statistics_in[1]+statistics_in[2],str1,10);
    itoa(statistics_out[0]+statistics_out[1]+statistics_out[2],str2,10);

    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");
    Readbmp64k(150,50,"image\\nijika.bmp");
    
    draw_mainselector();
    
    bar1(717,400,914,500,0X67FC);
    puthz(753,434,"���ɱ���",32,32,0X0000);
    Line_Thick(717,400,717,500,1,0X0000);
    Line_Thick(914,400,914,500,1,0X0000);
    Line_Thick(717,400,914,400,1,0X0000);
    Line_Thick(717,500,914,500,1,0X0000);

    puthz(680,230,"���������",48,48,0X0000);
    puthz(680,300,"����������",48,48,0X0000);
    put_asc16_size(910,226,4,4,str1,0X0000);
    put_asc16_size(910,296,4,4,str2,0X0000);
}
