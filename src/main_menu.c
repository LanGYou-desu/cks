#include"allfunc.h"

int statistics_in[3] = {0,0,0};//统计入库数据
int statistics_out[3] = {0,0,0};//统计出库数据

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
                puthz(753,434,"生成报告",32,32,0X0000);
                mouse_on(mouse);
            }
        }
        else if(star==1)
        {
            if(!(mouse.x>=717&&mouse.x<=914&&mouse.y>=400&&mouse.y<=500))
            {
                star=0;
                bar1(717,400,914,500,0X67FC);
                puthz(753,434,"生成报告",32,32,0X0000);
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
                    *flag = 0;//返回
                    *robonum = 0;
                    *item = 0;
                    *(item+1) = 0;
                    *(item+2) = 0;
                    return 0;
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//取消
                    return 0;
                }
            }
        }
        else if(mouse_press(0,50,100,150) == 1)
        {
            *flag = 4;//设置人机
            return 0;
        }
        else if(mouse_press(0,150,100,250) == 1)
        {
            *flag = 6;//电量监测
            return 0;
        }
        else if(mouse_press(0,250,100,350) == 1)
        {
            *flag = 5;//设置货物
            return 0;
        }
        else if(mouse_press(0,350,100,450) == 1)
        {
            *flag = 7;//开始模拟
            return 0;
        }
        else if(mouse_press(0,450,100,550) == 1)
        {
            *flag = 10;//仓库预览
            return 0;
        }
        else if(mouse_press(0,550,100,650) == 1)
        {
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
        else if(mouse_press(717,400,914,500))
        {
            mouse_off(&mouse);
            draw_return_comfirm(2);
            mouse_on(mouse);
            while(1){
                mouse_show(&mouse);
                if(mouse_press(331,415,470,460) == 1)
                {
                    report();
                    return 0;
                }
                else if(mouse_press(546,415,685,460) == 1)
                {
                    *flag = 3;//取消
                    return 0;
                }
            }
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
    Readbmp64k(0,0,"C:\\cks\\image\\bg.bmp");
    Readbmp64k(150,50,"C:\\cks\\image\\nijika.bmp");
    bar1(0,750,100,768,0X67FC);
    
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);
    
    bar1(0,50,100,150,0X67FC);
    puthz(18,64,"设置",32,32,0X0000);
    puthz(18,104,"人机",32,32,0X0000);
    
    bar1(0,150,100,250,0X67FC);
    puthz(18,164,"电量",32,32,0X0000);
    puthz(18,204,"监测",32,32,0X0000);
   
    bar1(0,250,100,350,0X67FC);
    puthz(18,264,"设置",32,32,0X0000);
    puthz(18,304,"货物",32,32,0X0000);
    
    bar1(0,350,100,450,0X67FC);
    puthz(18,364,"开始",32,32,0X0000);
    puthz(18,404,"模拟",32,32,0X0000);

    bar1(0,450,100,550,0X67FC);
    puthz(18,464,"仓库",32,32,0X0000);
    puthz(18,504,"预览",32,32,0X0000);

    bar1(0,550,100,650,0X67FC);
    puthz(18,564,"程序",32,32,0X0000);
    puthz(18,604,"介绍",32,32,0X0000);

    bar1(0,650,100,750,0X67FC);
    puthz(18,664,"退出",32,32,0X0000);
    puthz(18,704,"程序",32,32,0X0000);

    bar1(717,400,914,500,0X67FC);
    puthz(753,434,"生成报告",32,32,0X0000);

    puthz(680,230,"入库总数：",48,48,0X0000);
    puthz(680,300,"出库总数：",48,48,0X0000);
    put_asc16_size(910,226,4,4,str1,0X0000);
    put_asc16_size(910,296,4,4,str2,0X0000);

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
    puthz(370,422,"确定",32,32,0X0000);
    puthz(585,422,"取消",32,32,0X0000);

    if(i==0)
    {
        puthz(379,270,"确认返回登录界面",32,32,0X0000);
    }
    else if(i==1)
    {
        puthz(410,270,"确认退出程序",32,32,0X0000);
    }
    else if(i==2)
    {
        puthz(410,270,"确认生成报告",32,32,0X0000);
    }
}

void report()
{
    FILE *fp;
    fp = fopen("C:\\cks\\report\\report.txt","w");
    setvbuf(fp, NULL, _IONBF, 0); // 无缓冲模式
    if(fp == NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    fprintf(fp,"====================\n");
    fprintf(fp,"入库数据统计：\n");
    fprintf(fp,"入库总数：     %d\n",statistics_in[0]+statistics_in[1]+statistics_in[2]);
    fprintf(fp,"入库一类货物：  %d\n",statistics_in[0]);
    fprintf(fp,"入库二类货物：  %d\n",statistics_in[1]);
    fprintf(fp,"入库三类货物：  %d\n",statistics_in[2]);
    fprintf(fp,"====================\n");
    fprintf(fp,"出库数据统计：\n");
    fprintf(fp,"出库总数：     %d\n",statistics_out[0]+statistics_out[1]+statistics_out[2]);
    fprintf(fp,"出库一类货物：  %d\n",statistics_out[0]);
    fprintf(fp,"出库二类货物：  %d\n",statistics_out[1]);
    fprintf(fp,"出库三类货物：  %d\n",statistics_out[2]);
    fprintf(fp,"====================\n");
    fprintf(fp,"出入库综合统计：\n");
    fprintf(fp,"一类货物变化量：%d\n",statistics_in[0]-statistics_out[0]);
    fprintf(fp,"二类货物变化量：%d\n",statistics_in[1]-statistics_out[1]);
    fprintf(fp,"三类货物变化量：%d\n",statistics_in[2]-statistics_out[2]);
    fprintf(fp,"====================\n");
    fflush(fp); 
}