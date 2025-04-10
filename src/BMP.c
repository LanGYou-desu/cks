#include "bmp.h"
#include "mouse.h"		//只是调用其中的Getpixel64k()这个函数
#include "hz.h"
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
/**************************************
   SVGA的功能号ax说明
   0x4f00  读SVGA卡信息
   0x4f01  读显示模式信息
   0x4f02  设置显示模式
   0x4f03  读当前显示模式
   0x4f04  存储或恢复SVGA的视频状态
   0x4f05  控制内存页区域切换
   0x4f06  设置或读取逻辑扫描线宽度
   0x4f07  设置或读取视频内存与屏幕的初始对应位置
   0x4f08  设置或读取DAC各原色有效位数
   SVGA显示模式号bx：
		模式号		分辨率		颜色数		颜色位定义
		0x101		640*480		256				-
		0x103		800*600		256				-
		0x104		1024*768	16				-
		0x105		1024*768	256				-
		0x110		640*480		32K			1:5:5:5
		0x111		640*480		64K			5:6:5
		0x112		640*480		16.8M		8:8:8
		0x113		800*600		32K			1:5:5:5
		0x114		800*600		64K			5:6:5
		0x115		800*600		16.8M		8:8:8
		0x116		1024*768	32K			1:5:5:5
		0x117		1024*768	64K			5:6:5
		0x118		1024*768	16.8M		8:8:8
**************************************************/
void SetSVGA2561()
{
	union REGS regs;
	regs.x.ax=0x4f02;                //设置SVGA功能
	regs.x.bx=0x105;                  //设置SVGA显示模式
	int86(0x10,&regs,&regs);          //BIOS int 10h功能调用
	if (regs.x.ax != 0x004f)        //判断是否支持该功能
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", regs.x.ax);
		delay(5000);
		exit(1);
	}
}

void SetSVGA64k1()
{
	union REGS regs;
	regs.x.ax = 0x4f02;                //设置SVGA功能
	regs.x.bx = 0x117;                  //设置SVGA显示模式
	int86(0x10, &regs, &regs);           //BIOS int 10h功能调用
	if (regs.x.ax != 0x004f)              //判断是否支持该功能 
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n",regs.x.ax);
		delay(5000);
		exit(1);
	}
}

void Selectpage1(register char page)
{
	union REGS regs;
	static unsigned char old_page = 0;     //上一次的页面号,用于减少切换次数 
	static int flag = 0;                   //标志数，用于判断是否是第一次换页
	regs.x.ax = 0x4f05;                   //设置窗口页面控制功能号
	regs.x.bx = 0;
	if (flag == 0)                      //如果是第一次换页
	{
		old_page = page;
		regs.x.dx = page;
		int86(0x10, &regs, &regs);
		flag++;
	}
	else if (page != old_page)    //如果和上次页面号不同，则进行换页
	{
		old_page = page;
		regs.x.dx = page;
		int86(0x10, &regs, &regs);
	}
}

void Readbmp64k1(int x, int y, char * path)
{
	FILE * fpbmp;                      //指向图片文件的文件指针
	COLORS24 * buffer;                    //行像素缓存指针
	long int width, height, linebytes;   //图片的宽度、高度、一行像素所占字节数 
	int i, j;                        //循环变量
	unsigned int bit;                 //图片位深
	unsigned long int compression;     //压缩类型
	if ((fpbmp = fopen(path, "rb")) == NULL)   //打开文件
	{
		printf("can not open 24bmpfile");
		delay(5000);
		exit(1);
	}
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	if (bit != 24U)  
	{
		printf("not 24bit");
		delay(5000);
		exit(1);
	}
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	if (compression != 0UL)
	{
		printf("can not display a compressed bmp file");
		delay(5000);
		exit(1);
	}
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	/*宽度或高度超限则退出*/
	if (width > SCR_WIDTH||height>SCR_HEIGHT)
	{
		printf("24bmp too big");
		delay(5000);
		exit(1);
	}
	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;   //24位bmp一个像素三个字节
	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}
	/*开辟行像素数据动态储存空间*/
	if ((buffer = (COLORS24 *)malloc(linebytes)) == 0)
	{
		printf("not memery");
	}
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		/*一行像素的数据处理和画出*/
		for (j = 0; j < width; j++)
		{
			/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			Putpixel64k1(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
		}
	}
	free(buffer);	
	fclose(fpbmp);
}

void Xorpixel64k(int x, int y, unsigned int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	unsigned char page;  //要切换的页面号
	unsigned long int page_dev;  //对应显存地址偏移量
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		printf("out of range");
	}
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page_dev = ((unsigned long int)y << 10) + x;    //用<<10代替乘以1024
	page = page_dev >> 15;	//64k个点一换页，除以64k的替代算法
	Selectpage1(page);
	/*向显存写入颜色，对应点异或画出*/
	video_buffer[page_dev]^= color;	
}

void Putpixel64k1(int x, int y, unsigned int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	unsigned char page;    //要切换的页面号
	unsigned long int page_dev;   //对应显存地址偏移量
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		 printf("out of range");		
		 delay(5000);
		 exit(1); //有些时候鼠标会超过，还没有解决，就先把这个注释了
	}
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page_dev = ((unsigned long int)y << 10) + x;
	page = page_dev >> 15;	/*32k个点一换页，除以32k的替代算法*/
	Selectpage1(page);
	/*向显存写入颜色，对应点画出*/
	video_buffer[page_dev] = color;
} 

void rectangle_svga1(int x0,int y0,int x1,int y1)
{
	int i,j;           //循环函数
	for(i=y0;i<=y1;i++)
		for(j=x0;j<=x1;j++)           //画像素点为2的矩形框
		{
			if((i>=y0&&i<=y0+1)||(i>=y1-1&&i<=y1))
			{
				Putpixel64k1(j,i,500);
			}
			else
			{
				Putpixel64k1(x0,i,500);
				Putpixel64k1(x0+1,i,500);
				Putpixel64k1(x1-1,i,500);
				Putpixel64k1(x1,i,500);
			}
		}
}


void CloseSVGA1()        
{
    union REGS regs;
    regs.h.ah=0;
    regs.h.al=0x03;
    int86(0x10,&regs,&regs);     
}

void Readpartbmp64k1(int x,int y,int x1,int y1,int x2,int y2,char *path)
{
	FILE * fpbmp;                      //指向图片文件的文件指针
	COLORS24 * buffer;                    //行像素缓存指针
	long int width, height, linebytes;   //图片的宽度、高度、一行像素所占字节数 
	int i, j;                        //循环变量
	unsigned int bit;                 //图片位深
	unsigned long int compression;     //压缩类型
	if ((fpbmp = fopen(path, "rb")) == NULL)   //打开文件
	{
		printf("can not open 24bmpfile");
		delay(5000);
		exit(1);
	}
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	if (bit != 24U)  
	{
		printf("not 24bit");
		delay(5000);
		exit(1);
	}
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	if (compression != 0UL)
	{
		printf("can not display a compressed bmp file");
		delay(5000);
		exit(1);
	}
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	/*宽度或高度超限则退出*/
	if (width > SCR_WIDTH||height>SCR_HEIGHT)
	{
		printf("24bmp too big");
		delay(5000);
		exit(1);
	}
	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;   //24位bmp一个像素三个字节
	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}
	/*开辟行像素数据动态储存空间*/
	if ((buffer = (COLORS24 *)malloc(linebytes)) == 0)
	{
		printf("not memery");
	}
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L+linebytes*(height-1-y1), 0);
	for (i =y1-y2; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		/*一行像素的数据处理和画出*/
		for (j = 0; j < x2-x1; j++)
		{
			if((x1+j)>=x1&&(x1+j)<=x2)
			{
				/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
				buffer[j].R >>= 3;
				buffer[j].G >>= 2;
				buffer[j].B >>= 3;
				Putpixel64k1(  j + x, i + y,
				((((unsigned int)buffer[j].R) << 11)
				| (((unsigned int)buffer[j].G) << 5)
				| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
			}
		}
	}
	free(buffer);	
	fclose(fpbmp);
}

/***设置背景颜色***/
void setbkcolor64k1(int color)
{
	int i,j;
	for(i=0;i<SCR_WIDTH;i++)
	{
		for(j=0;j<SCR_HEIGHT;j++)
		{
			Putpixel64k1(i,j,color);
		}
	}
}

/***24位显示模式下划线***/			
void Linel1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i;
	if(x1==x2)                   //竖直直线
	{
		if(y1<=y2)
		{
			for(i=y1;i<=y2;i++)
			Putpixel64k1(x1,i,color);
		}
		else
		{
			for(i=y2;i<=y1;i++)
			Putpixel64k1(x1,i,color);
		 }
	}
	
	else  if(y1==y2)                   //水平直线
	{
		if(x1<=x2)
		{
			for(i=x1;i<=x2;i++)
			Putpixel64k1(i,y1,color);
		}
		else
		{
			for(i=x2;i<=x1;i++)
			Putpixel64k1(i,y1,color);
		}
	}
}

/***24位显示模式下画矩形***/
void Barl1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int j;
	//getch();
	for(j=y1;j<=y2;j++)
	{
		Linel1(x1,j,x2,j,color);
	}
}

/***画45度斜线***/
void Linel1ean1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i,j;
	if((x1<x2)&&(y1>y2))
	{
		j=y1-1;
		for(i=x1-1;i<x2;i++)
		{
			Putpixel64k1(i,j,color);
			j=j-1;
		}
	}
	else if((x1<x2)&&(y1<y2))
	{
		j=y1-1;
		for(i=x1-1;i<x2;i++)
		{
			Putpixel64k1(i,j,color);
			j=j+1;
		}
	}
	else if((x1>x2)&&(y1>y2))
	{
		j=y2-1;
		for(i=x2-1;i<x1;i++)
		{
			Putpixel64k1(i,j,color);
			j=j+1;
		}
	}
	else if((x1>x2)&&(y1<y2))
	{
		j=y2-1;
		for(i=x2-1;i<x1;i++)
		{
			Putpixel64k1(i,j,color);
			j=j-1;
		}
	}
}

/***画斜线***/
void line64k1(int x1, int y1, int x2, int y2, unsigned int color)
{
    	int dx=0,dy=0;
	int x_inc=1,y_inc=1;
	int x=0,y=0;
    	int index=0,error=1;

    	x=x1;
   	 y=y1;
   	 dx=x2-x1;
    	dy=y2-y1;

		/*判断两点的左右信息*/
   	 if(dx<0)
    	{
        	dx=-dx;
        	x_inc=-1;
  	  }
	
   	 if(dy<0)
  	  {
        	dy=-dy;
        	y_inc=-1;
  	  }

		/*画线函数算法*/
    	if(dx>dy)
    	{
        	for(index=0;index<=dx;index++)
        	{
	      	 	 Putpixel64k1(x,y,color);
         	 	 error+=dy;
         	 	  x+=x_inc;
          		  Putpixel64k1(x,y,color);
			
            		if(error>dx)
           		 {
               			 error-=dx;
                		y+=y_inc;
              			 Putpixel64k1(x,y,color);
          		  }
			
       		 }
   	 }
    else
    {
        for(index=0;index<=dy;index++)
        {
            Putpixel64k1(x,y,color);
            error+=dx;
            y+=y_inc;
            Putpixel64k1(x,y,color);
			
            if(error>dy)
            {
                error-=dy;
                x+=x_inc;
                Putpixel64k1(x,y,color);
            }
        }
     }

}

/***读取颜色真值表对应的颜色***/
unsigned int ReadColor1(unsigned int x ,unsigned int y ,unsigned int z )
{
	
	x>>=3;		//x,y,z分别对应R,G,B
	y>>=2;
	z>>=3;
	return (((unsigned int)x<<11)|((unsigned int)y<<5)|(unsigned int)z); 		//返回值为该颜色对应的2字节的值
}

/***储存图像***/
void Saveimagetofile1(int x1, int y1, int x2, int y2, const char * path)
{
	int wid, len, i = 0, size = 0;		//用来储存每一行字节的个数
	FILE * save;
	unsigned int color, *buffer;
	unsigned int far * const head = (unsigned int far *)0xa0000000L;
	save = fopen(path, "wb+");
	if (save == NULL)
	{
		//write_hz24("无法找到保存图像内存的文件", 200, 200, 0);
		delay(3000);
		exit(1);
	}

	len = y2 - y1;
	wid = x2 - x1;
	size = (wid + 1) * 2;
	if ((buffer = (unsigned int*)malloc(size)) == 0)
	{
		//write_hz24("没有足够空间分配内存储存像素", 200, 200, 0);
		delay(3000);
		exit(1);
	}
	for (i = 0; i <= len; i++)
	{
		Selectpage1((i + y1) / 32);
		_fmemcpy(buffer, head + (y1 + i) * 1024 + x1, size);
		fwrite(buffer, size, 1, save);
	}
	free(buffer);
	fclose(save);
}




/***加载图像***/
void Loadimagefromfile1(int x1, int y1, int x2, int y2, const char * path)
{
	int wid, len, i = 0, size = 0;
	FILE * fpbmp;
	unsigned int color, *buffer;
	unsigned int far * const head = (unsigned int far *)0xa0000000L;
	fpbmp = fopen(path, "rb");
	if (fpbmp == NULL)
	{
		//write_hz24("无法找到加载图像内存的文件", 200, 200, 0);
		delay(3000);
		exit(1);
	}
	len = y2 - y1;
	wid = x2 - x1;
	size = (wid + 1) * 2;
	if ((buffer = (unsigned int*)malloc(size)) == 0)
	{
		//write_hz24("没有足够空间分配内存储存像素", 200, 200, 0);
		delay(3000);
		exit(1);
	}
	for (i = 0; i <= len; i++)
	{
		Selectpage1((i + y1 ) / 32);
		fread(buffer, size, 1, fpbmp);
		_fmemcpy(head + (y1 + i) * 1024 + x1, buffer, size);
	}
	free(buffer);
	fclose(fpbmp);
}

/***快速读取大照片中1024*768大小的图片***/
void Readbmplarge1 (int x, int y, char * path)
{
	FILE * fpbmp;                      //指向图片文件的文件指针
	unsigned int  * buffer;                    //行像素缓存指针
	int page;		//储存显存的页数
	long int width, height, height_1, linebytes;   //图片的宽度、高度、一行像素所占字节数 
	int i, j;                        //循环变量
	unsigned int bit;                 //图片位深
	unsigned long int compression;     //压缩类型
	unsigned int far *const head=(unsigned int far *)0xa0000000L;		//显存首地址
	long int bfoffbits;		
	if ((fpbmp = fopen(path, "rb")) == NULL)   //打开文件
	{
		printf("can not open 24bmpfile");
		delay(5000);
		exit(1);
	}
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	/*设置宽度、高度*/
	//width_1=1024;
	height_1=768;
	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = 2 * width;   //16位bmp一个像素2个字节
	/*开辟行像素数据动态储存空间*/
	if ((buffer = (unsigned int  *)malloc(1024*2)) == 0)
	{
		printf("not memery");
	}
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp,0x0a,SEEK_SET);
	fread(&bfoffbits,sizeof(long),1,fpbmp);
	fseek(fpbmp,bfoffbits,SEEK_SET);
	/*fseek(fpbmp, 54L, 0);*/
	for (i = height_1-1; i > -1; i--)
	{
		page=i/32;
		Selectpage1(page);
		fseek(fpbmp,bfoffbits+(height-1-y-i)*linebytes+2*x,0);
		fread(buffer, 1024, 2, fpbmp);	/*读取一行像素数据*/
		_fmemcpy(head+i*1024,buffer,1024*2);	
	}
	free(buffer);	
	fclose(fpbmp);
}

/***快速贴图***/
/*
int bmp_fast1( char * path)
{
	long int bfoffbits;
	unsigned int far *const head=(unsigned int far *)0xa0000000L;
	unsigned int* buffer;
	int i,j,k;
	unsigned int width,height;
	FILE * fpbmp;
	fpbmp=fopen(path, "rb");
	if(fpbmp==NULL)
	{
		return 1;
	}
	if ((buffer = (unsigned int*)malloc(1024*2)) == 0)
	{
		return 1;
	}
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	fseek(fpbmp,0x0a,SEEK_SET);
	fread(&bfoffbits,sizeof(long),1,fpbmp);
	fseek(fpbmp,bfoffbits,SEEK_SET);
	for (i =24; i>0; i--)
	{
		Selectpage1(i-1);
		for (j = 32; j>0; j--)
		{
			fread(buffer,1024,2, fpbmp);	
			_fmemcpy(head+((i-1)*32+j-1)*1024,buffer,1024*2);                  //1024*2表示一行像素内存,buffer储存 
		}
	}
	free(buffer);
	fclose(fpbmp);
	return 0;
}
*/

int bmp_fast1(int y1,int y2,char* path)
{
	long int bfoffbits;
	unsigned int far* head = (unsigned int far*)0xa0000000L;
	unsigned int* buffer;
	int i, j, k;
	int top, end;
	unsigned int width, height;
	FILE* fpbmp;
	unsigned int bit;
	fpbmp = fopen(path, "rb");
	if (fpbmp == NULL)
	{
		return 1;
	}
	if ((buffer = (unsigned int*)malloc(1024 * 2)) == 0)
	{
		return 1;
	}
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	fseek(fpbmp, 0x0a, SEEK_SET);
	fread(&bfoffbits, sizeof(long), 1, fpbmp);
	fread(&bit, 2, 1, fpbmp);
	fseek(fpbmp, bfoffbits, SEEK_SET);
	top = y1 / 32 + (y1 % 32)/16;
	end = y2 / 32 + (y2 % 32) / 16;
	for (i = 24; i > 0; i--)
	{
		Selectpage1(i - 1);
		for (j = 32; j > 0; j--)
		{
			fread(buffer, 1024, 2, fpbmp);
			if (i < end && i>top)
			{
				_fmemcpy(head + ((i - 1) * 32 + j - 1) * 1024, buffer, 1024 * 2);                  //1024*2表示一行像素内存,buffer储存 
			}
		}
	}
	free(buffer);
	fclose(fpbmp);
	return 0;
}

/***绘制按钮的通用函数***/  
void bmp_draw_button1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i, j,width,length;
	width = x2 - x1;
	length = y2 - y1;
	for (i = 0; i <= width; i++)
	{
		for (j = 0; j < length; j++)
		{
			Putpixel64k1(x1+i,y1+j,color);
		}
	}
}

/***绘制搜索的横线***/
void bmp_draw_line1(int x1, int y1, int x2, unsigned int color)
{
	int i, j;
	for (i = x1; i <= x2; i++)
	{
		Putpixel64k1(i, y1, color);
		Putpixel64k1(i, y1+1, color);
		Putpixel64k1(i, y1+2, color);
	}
}

/*画椭圆函数*/
int drawellipse1(int x, int y, int a, int b, unsigned int color, int flag)
{
	int i = 0, j = 0;
	float af = a, bf = b;
	if ((x - a < 0) || (x + a > 800) || (y - b < 0) || (y + b > 600))
		return 0;
	else
	{
		if (flag == 1)
		{
			for (i = 0; i <= a; i++)
			{
				j = (int)(sqrt(bf * bf - bf * bf / af / af * i * i));
				for (; j >= 0; j--)
				{
					Putpixel64k1(x + i, y + j, color);
					Putpixel64k1(x + i, y - j, color);
					Putpixel64k1(x - i, y + j, color);
					Putpixel64k1(x - i, y - j, color);
				}
			}
		}
		else
		{
			for (i = 0; i <= a; i++)
			{
				j = (int)(sqrt(bf * bf - bf * bf / af / af * i * i));
				Putpixel64k1(x + i, y + j, color);
				Putpixel64k1(x + i, y - j, color);
				Putpixel64k1(x - i, y + j, color);
				Putpixel64k1(x - i, y - j, color);
			}
			for (j = 0; j <= b; j++)
			{
				i = (int)(sqrt(af * af - af * af / bf / bf * j * j));
				Putpixel64k1(x + i, y + j, color);
				Putpixel64k1(x + i, y - j, color);
				Putpixel64k1(x - i, y + j, color);
				Putpixel64k1(x - i, y - j, color);
			}
		}
		return 1;
	}
}

/*画圆函数*/
int drawcircle1(int x, int y, int r, unsigned int color, int flag)//shi xin 1,xu xin 0
{
	int i = 0, j = 0;
	if ((x - r < 0) || (x + r > 1024) || (y - r < 0) || (y + r > 768))
		return 0;
	else
	{
		if (flag == 1)
		{
			for (i = 0; i <= r; i++)
			{
				j = (int)(sqrt(r * r - i * i));
				for (; j >= 0; j--)
				{
					Putpixel64k1(x + i, y + j, color);
					Putpixel64k1(x + i, y - j, color);
					Putpixel64k1(x - i, y + j, color);
					Putpixel64k1(x - i, y - j, color);
				}
			}
		}
		else
		{
			for (i = 0; i <= r; i++)
			{
				j = (int)(sqrt(r * r - i * i));
				Putpixel64k1(x + i, y + j, color);
				Putpixel64k1(x + i, y - j, color);
				Putpixel64k1(x - i, y + j, color);
				Putpixel64k1(x - i, y - j, color);
			}
			for (j = 0; j <= r; j++)
			{
				i = (int)(sqrt(r * r - j * j));
				Putpixel64k1(x + i, y + j, color);
				Putpixel64k1(x + i, y - j, color);
				Putpixel64k1(x - i, y + j, color);
				Putpixel64k1(x - i, y - j, color);
			}
		}
		return 1;
	}
}

/*画弧*/
void arc2561(int xc, int yc, int r, float stangle, float enangle, unsigned char color)
{
	float x, y, i;
	i = stangle;
	while (i <= enangle)
	{
		x = r * cos(i);
		y = r * sin(i);

		Putpixel64k1(xc + x, yc + y, color);
		//Putpixel256(xc + x + 1, yc + y + 1, color);
		//Putpixel256(xc + x + 1, yc + y - 1, color);
		//Putpixel256(xc + x - 1, yc + y + 1, color);
		//Putpixel256(xc + x - 1, yc + y - 1, color);
		i += 0.01;
	}
}

void draw_play_light1(int xc, int yc) //绘制播放按钮
{
	int i;
	drawcircle1(xc, yc, 30, -1, 1);
	for (i = 0; i < 20; i++)
	{
		Linel1(xc - 10, yc - i, xc - 10 + (20 - i) * 3 / 2, yc - i, -200);
		Linel1(xc - 10, yc + i, xc - 10 + (20 - i) * 3 / 2, yc + i, -200);
	}
}
/*
void draw_play_dark(int xc, int yc) //绘制播放按钮
{
	int i;
	drawcircle1(xc, yc, 30, -1, 1);
	for (i = 0; i < 20; i++)
	{
		Linel1(xc - 10, yc - i, xc - 10 + (20 - i) * 3 / 2, yc - i, -200);
		Linel1(xc - 10, yc + i, xc - 10 + (20 - i) * 3 / 2, yc + i, -200);
	}
}
*/
void draw_suspend_light1(int xc, int yc) //绘制暂停按钮
{
	int i;
	drawcircle1(xc, yc, 30, -1, 1);
	for (i = 8; i < 14; i++)
	{
		Linel1(xc - i, yc - 20, xc - i, yc +20, -200);
		Linel1(xc + i, yc - 20, xc + i, yc + 20, -200);
	}
}

void draw_next_light1(int xc, int yc) //绘制下一个按钮
{
	int i;
	drawcircle1(xc, yc, 30, -1, 1);
	for (i = 0; i < 20; i++)
	{
		Linel1(xc - 16 + (20 - i) * 3 / 2, yc - i, xc - 10 + (20 - i) * 3 / 2, yc - i, -200);
		Linel1(xc - 16 + (20 - i) * 3 / 2, yc + i, xc - 10 + (20 - i) * 3 / 2, yc + i, -200);
	}
}

void draw_last_light1(int xc, int yc) //绘制上一个按钮
{
	int i;
	drawcircle1(xc, yc, 30, -1, 1);
	for (i = 0; i < 20; i++)
	{
		Linel1(xc + 10 - (20 - i) * 3 / 2, yc - i, xc + 16 - (20 - i) * 3 / 2, yc - i, -200);
		Linel1(xc + 10 - (20 - i) * 3 / 2, yc + i, xc + 16 - (20 - i) * 3 / 2, yc + i, -200);
	}
}

void draw_back_svga1(int xc, int yc) //绘制返回按钮
{
	int i;
	for (i = 0; i < 20; i++)
	{
		Linel1(xc + 10 - (20 - i) * 3 / 2, yc - i, xc + 10, yc - i, -1);
		Linel1(xc + 10 - (20 - i) * 3 / 2, yc + i, xc + 10, yc + i, -1);
	}
}

void draw_end_svga1(int xc, int yc) //绘制退出按钮
{
	int i;
	for (i = 0; i < 5; i++)
	{
		line64k1(xc - 20, yc - 20, xc + 20, yc + 20, -1);
		line64k1(xc - 20, yc + 20, xc + 20, yc - 20, -1);
	}
}


void draw_start_light1(int y) //绘制完成按钮（亮）
{
	drawcircle1(462,y + 25,  25, -100, 1);
	drawcircle1(562,y + 25,  25, -100, 1);
	Barl1(462, y, 562, y+50, -100);
	//write_hz48("开始", 464, y+2, 0);
}

void draw_start_dark1(int y) //绘制完成按钮（暗）
{
	drawcircle1( 462,y + 25, 25, 10000, 1);
	drawcircle1( 562,y + 25,  25, 10000, 1);
	Barl1(462, y, 562, y + 50, 10000);
	//write_hz48("开始", 464, y+2, 0);
}

int X(int i) //计算拐点的坐标，仅用于收藏按钮
{
	double e = 2 * PI / 10; //定义角度
	if (i % 2 == 0) //偶数
		return 11 * cos((i - 1) * e + PI / 2);
	else //奇数
		return 18 * cos((i - 1) * e + PI / 2);
}

int Y(int i) //计算拐点的坐标，仅用于收藏按钮
{
	double e = 2 * PI / 10; //定义角度
	if (i % 2 == 0) //偶数
		return (-11) * sin((i - 1) * e + PI / 2);
	else //奇数
		return (-18) * sin((i - 1) * e + PI / 2);
}

void button_collect_light1(int x, int y) //绘制收藏按钮（亮）
{
	int num; //第几个点
	int i,j; //坐标，原点为（x,y）
	/*第一段*/
	for (j = Y(1); j < Y(2); j++)
	{
		Linel1(x + X(1) + (j - Y(1)) * (X(2) - X(1)) / (Y(2) - Y(1)), j+y, x + X(1) + (j- Y(1)) * (X(10) - X(1)) / (Y(10) - Y(1)), j+y, -1);
	}
	for(j = Y(2); j < Y(3); j++)
		Linel1(x + X(2) + (j - Y(2)) * (X(2) - X(3)) / (Y(2) - Y(3)), j+y, x + X(10) + (j - Y(10)) * (X(10) - X(9)) / (Y(10) - Y(9)),j+y,-1);
	for (j = Y(3); j < Y(4); j++)
		Linel1(x + X(3) + (j - Y(3)) * (X(3) - X(4)) / (Y(3) - Y(4)), j+y, x + X(9) + (j - Y(9)) * (X(9) - X(8)) / (Y(9) - Y(8)),j+y,-1);
	for (j = Y(4); j < Y(6); j++)
		Linel1(x + X(4) + (j - Y(4)) * (X(4) - X(5)) / (Y(4) - Y(5)), j+y, x + X(8) + (j - Y(8)) * (X(8) - X(7)) / (Y(8) - Y(7)),j+y,-1);
	for (j = Y(6); j < Y(5); j++)
	{
		Linel1(x + X(4) + (j - Y(4)) * (X(4) - X(5)) / (Y(4) - Y(5)), j+y, x + X(5) + (j - Y(5)) * (X(5) - X(6)) / (Y(5) - Y(6)), j+y,-1);
		Linel1(x + X(6) + (j - Y(6)) * (X(6) - X(7)) / (Y(6) - Y(7)), j+y, x + X(7) + (j - Y(7)) * (X(7) - X(8)) / (Y(7) - Y(8)), j+y,-1);
	}
}

void button_collect_dark1(int x, int y) //绘制收藏按钮（暗）
{
	int num; //第几个点
	int i, j; //坐标，原点为（x,y）
	/*第一段*/
	for (j = Y(1); j < Y(2); j++)
	{
		Linel1(x + X(1) + (j - Y(1)) * (X(2) - X(1)) / (Y(2) - Y(1)), j + y, x + X(1) + (j - Y(1)) * (X(10) - X(1)) / (Y(10) - Y(1)), j + y, -500);
	}
	for (j = Y(2); j < Y(3); j++)
		Linel1(x + X(2) + (j - Y(2)) * (X(2) - X(3)) / (Y(2) - Y(3)), j + y, x + X(10) + (j - Y(10)) * (X(10) - X(9)) / (Y(10) - Y(9)), j + y, -500);
	for (j = Y(3); j < Y(4); j++)
		Linel1(x + X(3) + (j - Y(3)) * (X(3) - X(4)) / (Y(3) - Y(4)), j + y, x + X(9) + (j - Y(9)) * (X(9) - X(8)) / (Y(9) - Y(8)), j + y, -500);
	for (j = Y(4); j < Y(6); j++)
		Linel1(x + X(4) + (j - Y(4)) * (X(4) - X(5)) / (Y(4) - Y(5)), j + y, x + X(8) + (j - Y(8)) * (X(8) - X(7)) / (Y(8) - Y(7)), j + y, -500);
	for (j = Y(6); j < Y(5); j++)
	{
		Linel1(x + X(4) + (j - Y(4)) * (X(4) - X(5)) / (Y(4) - Y(5)), j + y, x + X(5) + (j - Y(5)) * (X(5) - X(6)) / (Y(5) - Y(6)), j + y, -500);
		Linel1(x + X(6) + (j - Y(6)) * (X(6) - X(7)) / (Y(6) - Y(7)), j + y, x + X(7) + (j - Y(7)) * (X(7) - X(8)) / (Y(7) - Y(8)), j + y, -500);
	}
}

void draw_clock1(int x,int y) //画时钟
{
	x += 10;
	drawcircle1(x,y,13,-1,1);
	drawcircle1(x, y, 13, 0, 0);
	Linel1(x, y,x, y-9, 100);
	Linel1(x+1, y, x+1, y - 9, 100);
	Linel1(x, y, x+11, y, 100);
	drawcircle1(x, y, 4, 100, 1);
}

void draw_fire1(int x, int y) //画火
{
	int fire[20][15] =
	{
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,1,0,0,0,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,0,1,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,0,1,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	int i,j;
	for (i = 0; i < 20; i++)
	{
		for(j = 0; j < 15; j++)
		{
			if (fire[i][j] == 0)
				continue;
			Putpixel64k1(x + j, y + i, -800);   
		}
	}
}

void drawxin1(int x, int y, int color)    //
{
	int x0 = x, y0 = y;
	double q, p;
	double r;
	r = sqrt(125);

	drawcircle1(x + 11, y, r, color, 1);
	drawcircle1(x + 31, y, r, color, 1);

	line64k1(x, y, x + 21, y + 25, color);
	line64k1(x + 42, y, x + 21, y + 25, color);

	for (p = y; p <= y + 25; p++)
	{
		for (q = x; q <= x + 42; q++)
		{
			if (p <= y0 + 25 * (q - x0) / 21 && p <= y0 - 25 * (q - x0 - 42) / 21)
				Putpixel64k1(q, p, color);
		}
	}



}

void draw_tri1(int x1, int y1, int x2, int y2, int x3, int y3, int color)//画三角形  
{
	int i, j, a, b;

	if (x1 > x2)
	{
		a = x2; b = y2;
		x2 = x1; y2 = y1;
		x1 = a; y1 = b;
	}
	if (x1 > x3)
	{
		a = x3; b = y3;
		x3 = x1; y3 = y1;
		x1 = a; y1 = b;
	}
	if (x2 > x3)
	{
		a = x3; b = y3;
		x3 = x2; y3 = y2;
		x2 = a; y2 = b;
	}

	line64k1(x1, y1, x2, y2, color);
	line64k1(x2, y2, x3, y3, color);
	line64k1(x3, y3, x1, y1, color);

	if (x1 == x2)
	{
		if (y1 > y2)
		{
			a = y2; y2 = y1; y1 = a;
		}
		for (j = y1; j < y2; j++)
		{
			for (i = x1; i < x3; i++)
			{
				if (i <= x1 + (j - y1) * (x3 - x1) / (y3 - y1) && i <= x2 + (j - y2) * (x3 - x2) / (y3 - y2))
					Putpixel64k1(i, j, color);
			}
		}
	}


	if (x2 == x3)
	{

		if (y2 > y3)
		{
			a = y3; y3 = y2; y2 = a;
		}
		for (j = y2; j < y3; j++)
		{
			for (i = x2; i > x1; i--)
			{
				if (i >= x2 + (j - y2) * (x2 - x1) / (y2 - y1) && i >= x3 + (j - y3) * (x3 - x1) / (y3 - y1))
					Putpixel64k1(i, j, color);
			}
		}
	}

}
