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

void draw_robot(int x,int y,int flag)
{
	if(flag==0)
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
	}
	else
	{
		bar1(x-25,y-25,x+25,y+25,0X62CA);
		bar1(x-15,y-15,x+15,y+15,0XCBA4);
	}
}

void draw_item(int x,int y,int type,int floor,int flag)
{
	int rx,ry;

	if(type==2||type==3)
	{
		rx=x;
		ry=y+IL*flag;
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0X5A9C);
		}
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XCBA4);
		}
	}
	else if(type==1)
	{
		rx=x+IL*flag;
		ry=y;
		if(floor==0)
		{
			bar1(rx-30,ry-30,rx+30,ry+30,0X5A9C);
		}
		else if(floor==1)
		{
			bar1(rx-20,ry-20,rx+20,ry+20,0XCBA4);
		}
	}
}