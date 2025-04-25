#include"allfunc.h"

void draw_commoninput(int x,int y,int len,char *s)
{
	Line_Thick(x, y, x + len, y, 1, 0xBD32 );
	prt_hz16_size(x + 16, y - 46, 2, 2, s, 0xBD32, "HZK\\HZK16s");
}

void put_inputline(int x,int y,int len)
{
	Line_Thick(x, y, x + len, y, 1, 0xBD32 );
}

void draw_button(int x1,int y1,int x2,int y2)
{
	bar1(x1+50,y1,x2-50,y2,0X67FC);
	Circlefill(x1+45,(y1+y2)/2,(y2-y1)/2,0X67FC);
	Circlefill(x2-45,(y1+y2)/2,(y2-y1)/2,0X67FC);
}

void draw_return_comfirm(int i)
{
    bar1(0,0,1024,768,0XFFFF);
    Readbmp64k(0,0,"image\\bg.bmp");

    bar1(331,415,470,460,0X67FC);
    bar1(546,415,685,460,0X67FC);
    puthz(370,422,"确定",32,32,0X0000);
    puthz(585,422,"取消",32,32,0X0000);
    Line_Thick(331,415,331,460,1,0X0000);
    Line_Thick(470,415,470,460,1,0X0000);
    Line_Thick(331,415,470,415,1,0X0000);
    Line_Thick(331,460,470,460,1,0X0000);
    Line_Thick(546,415,546,460,1,0X0000);
    Line_Thick(685,415,685,460,1,0X0000);
    Line_Thick(546,415,685,415,1,0X0000);
    Line_Thick(546,460,685,460,1,0X0000);

    if(i==0)
    {
        puthz(379,280,"确认返回登录界面",32,32,0X0000);
    }
    else if(i==1)
    {
        puthz(410,280,"确认退出程序",32,32,0X0000);
    }
    else if(i==2)
    {
        puthz(410,270,"确认生成报告",32,32,0X0000);
    }
}

void show_gb(int x,int y)
{
	Line1(x,y-3,x,y+29,0);
}

void draw_robot(int x,int y,int flag)
{
	if(flag==0)
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
	}
	else if(flag==1)
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
		bar1(x-15,y-15,x+15,y+15,0XFFE9);
	}
	else if(flag==2)
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
		bar1(x-15,y-15,x+15,y+15,0X67E0);
	}
	else if(flag==3)
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
		bar1(x-15,y-15,x+15,y+15,0XFE19);
	}
}

void draw_item(int x,int y,int type,int floor,int flag)
{
	int rx,ry;

	rx=x;
	ry=y+IL*flag;
	if(type==1)
	{
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0XFFE9);
		}	
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XFC06);
		}
	}
	else if(type==2)
	{
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0X67E0);
		}	
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XFC06);
		}
	}
	else if(type==3)
	{
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0XFE19);
		}	
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XFC06);
		}
	}
	else if(type==-1)
	{
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0XFFFF);
		}	
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XFFFF);
		}
	}
}

void draw_mainselector()
{
	bar1(0,0,100,50,0X67FC);
    puthz(18,9,"返回",32,32,0X0000);

	bar1(0,50,100,150,0X67FC);
    puthz(18,64,"设置",32,32,0X0000);
    puthz(18,104,"人机",32,32,0X0000);
    
    bar1(0,150,100,250,0X67FC);
    puthz(18,164,"设置",32,32,0X0000);
    puthz(18,204,"货物",32,32,0X0000);
   
    bar1(0,250,100,350,0X67FC);
    puthz(18,264,"信息",32,32,0X0000);
    puthz(18,304,"一览",32,32,0X0000);
    
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

	bar1(0,750,100,768,0X67FC);

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

void draw_showbox(int x,int y)
{
    bar1(x,y,x+213,y+128,0X0000);
    bar1(x+3,y+3,x+210,y+125,0X67FC);
}

