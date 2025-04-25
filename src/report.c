#include"allfunc.h"

int report_menu(int *flag)
{
    int star=1;
    int choose=timestep;
    
    mouse_off(&mouse);
    draw_anime();
    draw_report_menu(choose);
    mouse_on(mouse);
    
    while(1)
    {
        mouse_show(&mouse);
        if(star==0)
        {
            if(mouse.x>=827&&mouse.x<=1024&&mouse.y>=0&&mouse.y<=100)
            {
                mouse_off(&mouse);
                star=1;
                bar1(827,0,1024,100,0XD69A);
                puthz(863,34,"下载报告",32,32,0X0000);
                mouse_on(mouse);
            }
        }
        else if(star==1)
        {
            if(!(mouse.x>=827&&mouse.x<=1024&&mouse.y>=0&&mouse.y<=100))
            {
                star=0;
                bar1(827,0,1024,100,0X67FC);
                puthz(863,34,"下载报告",32,32,0X0000);
            }
        }

        if(mouse_press(0,0,100,50)==1)
        {
            *flag=3;
            return 0;
        }
        else if(mouse_press(827,0,1024,100)==1)
        {
            download_report();
            draw_report_menu(choose);
            continue;
        }
        else if(mouse_press(0,176,41,217)==1)
        {
            if(choose==1)
            {
                choose=3;
            }
            else
            {
                choose--;
            }
            draw_report_menu(choose);
        }
        else if(mouse_press(983,176,1024,217)==1)
        {
            if(choose==3)
            {
                choose=1;
            }
            else
            {
                choose++;
            }
            draw_report_menu(choose);
        }
    }
}

void draw_report_menu(int choose)
{
    bar1(0,0,1024,768,0xF8FFBD);
    
    bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);
    Line_Thick(0,50,100,50,1,0X0000);
    Line_Thick(100,0,100,50,1,0X0000);

    bar1(827,0,1024,100,0X67FC);
    puthz(863,34,"下载报告",32,32,0X0000);
    Line_Thick(827,0,1024,0,1,0X0000);
    Line_Thick(827,100,1024,100,1,0X0000);
    Line_Thick(827,0,827,100,1,0X0000);
    Line_Thick(1024,0,1024,100,1,0X0000);

    bar1(0,176,41,217,0X67FC);
    bar1(983,176,1024,217,0X67FC);
    put_asc16_size(7,174,3,3,"<",0X0000);
    put_asc16_size(993,174,3,3,">",0X0000);
    Line_Thick(0,176,0,217,2,0X0000);
    Line_Thick(41,176,41,217,2,0X0000);
    Line_Thick(983,176,983,217,2,0X0000);
    Line_Thick(1024,176,1024,217,2,0X0000);
    Line_Thick(0,176,41,176,2,0X0000);
    Line_Thick(983,176,1024,176,2,0X0000);
    Line_Thick(0,217,41,217,2,0X0000);
    Line_Thick(983,217,1024,217,2,0X0000);

    draw_report();

    fill_blank(choose);
}

void draw_anime()
{
    char progress_text1[5][30]=
    {
        "正在加载时间...",
        "正在加载仓库数据...",
        "正在加载货物数据...",
        "正在加载机器人数据...",
        "正在综合数据..."
    }; // 进度条文本

    char progress_text2[5][30]=
    {
        "时间加载完成！",
        "仓库数据加载完成！",
        "货物数据加载完成！",
        "机器人数据加载完成！",
        "数据综合完成！"
    };

    int progress_x = 50; // 进度条起始X坐标
    int progress_y_start = 150; // 第一个进度条起始Y坐标
    int progress_width = 924; // 进度条总宽度
    int progress_height = 30; // 进度条高度
    int progress_spacing = 80; // 每个进度条之间的间隔
    int segment_width = progress_width / 5; // 每段宽度
    int i, j;
    int progress_y;

    // 绘制界面
    bar1(0, 0, 1024, 768, 0xF8FFBD); // 背景
    puthz(230,0,"加载完成前请等待大约十秒钟",48,50,0x000000);
    Line_Thick(0,51,1024,51,1,0xAAAA);
    Line_Thick(200,0,200,51,1,0xAAAA);
    Line_Thick(920,0,920,51,1,0xAAAA);

    // 绘制5个进度条背景
    for (i = 0; i < 5; i++) 
    {
        progress_y = progress_y_start + i * (progress_height + progress_spacing);
        bar1(progress_x, progress_y, progress_x + progress_width, progress_y + progress_height, 0xCCCCCC); // 灰色背景
        
        if(i>0)
        {
            prt_hz16_asc16_size(progress_x, progress_y-50,3,3,"等待中...",0x000000, "hzk\\hzk16");
        }
    }

    // 加载5个内容
    for (i = 0; i < 5; i++) 
    {
        bar1(50, 100+i*110, 350, 149+i*110,0xF8FFBD);
        prt_hz16_asc16_size(50, 100+i*110,3,3,progress_text1[i],0x000000,"hzk\\hzk16");
        
        
        for (j = 0; j < 5; j++) 
        { // 每个内容分5段加载
            delay(500); // 模拟加载时间

            // 更新对应进度条
            progress_y = progress_y_start + i * (progress_height + progress_spacing);
            bar1(progress_x, progress_y, progress_x + segment_width * (j + 1), progress_y + progress_height, 0x00FF00); // 绿色进度条
        }

        bar1(50, 100+i*110, 600, 149+i*110,0xF8FFBD);
        prt_hz16_asc16_size(50, 100+i*110,3,3,progress_text2[i],0x000000, "hzk\\hzk16");


        // 确保进度条被完全填满
        progress_y = progress_y_start + i * (progress_height + progress_spacing);
        bar1(progress_x, progress_y, progress_x + progress_width, progress_y + progress_height, 0x00FF00); // 完全填满绿色
    }
}

void draw_report()
{
    Line_Thick(176,119,176,714,2,0X0000);
    Line_Thick(176,119,846,119,2,0X0000);
    Line_Thick(847,714,846,119,2,0X0000);
    Line_Thick(847,714,176,714,2,0X0000);

    Line_Thick(176,217,846,217,2,0X0000);
    Line_Thick(430,217,430,714,2,0X0000);
    Line_Thick(488,217,488,714,2,0X0000);

    Line_Thick(303,217,303,714,2,0X0000);
    Line_Thick(607,217,607,714,2,0X0000);
    Line_Thick(727,217,727,714,2,0X0000);

    Line_Thick(176,383,847,383,2,0X0000);
    Line_Thick(176,548,847,548,2,0X0000);

    Line_Thick(488,383,847,383,2,0X0000);
    Line_Thick(488,548,847,548,2,0X0000);
}

void fill_blank(int choose)
{
    FILE *fp;
    int i=0;
    int item[3]={0};
    int robonum=0;
    int type=0;
    int is_auto=0;
    int energy[3]={0};
    char temp[4];
    char result[4];
    char plus[2]="+";
    char minus[2]="-";
    char reportfile[3][20]={
        "report\\report1.txt",
        "report\\report2.txt",
        "report\\report3.txt",
    };
    
    fp = fopen(reportfile[choose-1],"r");
    if(fp == NULL)
    {
        return;
    }

    fscanf(fp,"%d",&is_auto);
    fscanf(fp,"%d",&type);
    fscanf(fp,"%d",&robonum);
    fscanf(fp,"%d,%d,%d",&item[0],&item[1],&item[2]);
    if(is_auto==1)
    {
        for(i=0;i<robonum;i++)
        {
            fscanf(fp,"%d",&energy[i]);
        }
    }
    fclose(fp);

    puthz(215,276,"一",48,48,0X0000);
    puthz(215,441,"二",48,48,0X0000);
    puthz(215,606,"三",48,48,0X0000);

    puthz(515,268,"一类",32,32,0X0000);
    puthz(515,300,"货架",32,32,0X0000);
    puthz(634,268,"二类",32,32,0X0000);
    puthz(634,300,"货架",32,32,0X0000);
    puthz(753,268,"三类",32,32,0X0000);
    puthz(753,300,"货架",32,32,0X0000);

    itoa(statistics_in[0]-statistics_out[0],temp,10);
    put_asc16_size(525,615,2,2,temp,0X0000);

    itoa(statistics_in[1]-statistics_out[1],temp,10);
    put_asc16_size(644,615,2,2,temp,0X0000);

    itoa(statistics_in[2]-statistics_in[2],temp,10);
    put_asc16_size(763,615,2,2,temp,0X0000);

    if(is_auto==0)
    {
        puthz(255,144,"手动",48,48,0X0000);
        puthz(342,276,"—",48,48,0X0000);
        puthz(342,441,"—",48,48,0X0000);
        puthz(342,606,"—",48,48,0X0000);
    }
    else if(is_auto==1)
    {
        puthz(255,144,"自动",48,48,0X0000);
        if(robonum==1)
        {
            itoa(energy[0],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,281,2,2,temp,0X0000);

            puthz(342,441,"—",48,48,0X0000);
            puthz(342,606,"—",48,48,0X0000);
        }
        else if(robonum==2)
        {
            itoa(energy[0],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,281,2,2,temp,0X0000);

            itoa(energy[1],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,446,2,2,temp,0X0000);

            puthz(342,606,"—",48,48,0X0000);
        }
        else if(robonum==3)
        {
            itoa(energy[0],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,281,2,2,temp,0X0000);

            itoa(energy[1],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,446,2,2,temp,0X0000);

            itoa(energy[2],temp,10);
            strcat(temp,"%");
            put_asc16_size(342,611,2,2,temp,0X0000);
        }
    }

    if(type==1)
    {
        puthz(619,144,"出库",48,48,0X0000);

        itoa(item[0],temp,10);
        strcpy(result,minus);
        strcat(result,temp);
        put_asc16_size(520,449,2,2,result,0X0000);

        itoa(item[1],temp,10);
        strcpy(result,minus);
        strcat(result,temp);
        put_asc16_size(639,449,2,2,result,0X0000);

        itoa(item[2],temp,10);
        strcpy(result,minus);
        strcat(result,temp);
        put_asc16_size(758,449,2,2,result,0X0000);
    }
    else if(type==0)
    {
        puthz(619,144,"入库",48,48,0X0000);

        itoa(item[0],temp,10);
        strcpy(result,plus);
        strcat(result,temp);
        put_asc16_size(520,449,2,2,result,0X0000);

        itoa(item[1],temp,10);
        strcpy(result,plus);
        strcat(result,temp);
        put_asc16_size(639,449,2,2,result,0X0000);

        itoa(item[2],temp,10);
        strcpy(result,plus);
        strcat(result,temp);
        put_asc16_size(758,449,2,2,result,0X0000);
    }
}

void update_report(int robonum,int *item,Robot *robot,int type,int is_auto)//type=1出库，type=0入库
{
    int i=0;
    FILE *fp;
    char reportfile[3][20]={
        "report\\report1.txt",
        "report\\report2.txt",
        "report\\report3.txt",
    };

    if(timestep%3==1)
    {
        fp = fopen(reportfile[0],"w");
    }
    else if(timestep%3==2)
    {
        fp = fopen(reportfile[1],"w");
    }
    else if(timestep%3==0)
    {
        fp = fopen(reportfile[2],"w");
    }

    setvbuf(fp, NULL, _IONBF, 0); // 无缓冲模式
    fprintf(fp,"%d\n",is_auto);
    fprintf(fp,"%d\n",type);
    fprintf(fp,"%d\n",robonum);
    fprintf(fp,"%d,%d,%d\n",item[0],item[1],item[2]);
    if(is_auto==1)
    {
        for(i=0;i<robonum;i++)
        {
            fprintf(fp,"%d\n",(int)robot->battery);
            robot=robot->next;
        }
    }
    fflush(fp);

    fclose(fp);
    free(fp);
}

void download_report()
{
    FILE *fp;
    fp = fopen("report\\report.txt","w");
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
