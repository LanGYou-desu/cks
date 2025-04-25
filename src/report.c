#include"allfunc.h"

int report_menu(int *flag)
{
    int star=1;
    
    mouse_off(&mouse);
    draw_report();
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
                puthz(753,434,"���ر���",32,32,0X0000);
                mouse_on(mouse);
            }
        }
        else if(star==1)
        {
            if(!(mouse.x>=717&&mouse.x<=914&&mouse.y>=400&&mouse.y<=500))
            {
                star=0;
                bar1(717,400,914,500,0X67FC);
                puthz(753,434,"���ر���",32,32,0X0000);
            }
        }

        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;
            return 0;
        }
        else if(mouse_press(717,400,914,500)==1)
        {
            download_report();
        }
    }
}

void draw_report()
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");
    
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"����",32,32,0X0000);
}

void update_report(int robonum,int *item,ROHEAD *head)
{
    
}

void download_report()
{
    FILE *fp;
    fp = fopen("report\\report.txt","w");
    setvbuf(fp, NULL, _IONBF, 0); // �޻���ģʽ
    if(fp == NULL)
    {
        printf("�ļ���ʧ��\n");
        return;
    }
    fprintf(fp,"====================\n");
    fprintf(fp,"�������ͳ�ƣ�\n");
    fprintf(fp,"���������     %d\n",statistics_in[0]+statistics_in[1]+statistics_in[2]);
    fprintf(fp,"���һ����  %d\n",statistics_in[0]);
    fprintf(fp,"��������  %d\n",statistics_in[1]);
    fprintf(fp,"���������  %d\n",statistics_in[2]);
    fprintf(fp,"====================\n");
    fprintf(fp,"��������ͳ�ƣ�\n");
    fprintf(fp,"����������     %d\n",statistics_out[0]+statistics_out[1]+statistics_out[2]);
    fprintf(fp,"����һ����  %d\n",statistics_out[0]);
    fprintf(fp,"���������  %d\n",statistics_out[1]);
    fprintf(fp,"����������  %d\n",statistics_out[2]);
    fprintf(fp,"====================\n");
    fprintf(fp,"������ۺ�ͳ�ƣ�\n");
    fprintf(fp,"һ�����仯����%d\n",statistics_in[0]-statistics_out[0]);
    fprintf(fp,"�������仯����%d\n",statistics_in[1]-statistics_out[1]);
    fprintf(fp,"�������仯����%d\n",statistics_in[2]-statistics_out[2]);
    fprintf(fp,"====================\n");
    fflush(fp); 
}