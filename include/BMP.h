#ifndef	SVGA_H
#define	SVGA_H

#define	SCR_WIDTH	1024	 //屏幕宽度像素 
#define	SCR_HEIGHT	768		 //屏幕高度像素 
#define PI 3.141595265 //pi


/***8位bmp调色板区***/
typedef struct RGB_BMP_typ
{
	unsigned char b;	//蓝色分量，BLUE缩写
	unsigned char g;	//绿色分量，GREEN缩写
	unsigned char r;	//红色分量， RED缩写
	unsigned char reserved;		//保留字
}RGB_BMP;


/*24位bmp图颜色结构*/
typedef struct
{
	unsigned char B;	/*蓝色分量，BLUE缩写*/
	unsigned char G;	/*绿色分量，GREEN缩写*/
	unsigned char R;	/*红色分量，RED缩写*/
} COLORS24;



/***设置SVGA显示模式为0x105,为1024*768*256***/
void SetSVGA2561(void);
/***设置SVGA显示模式为0x117,为1024*768*64k***/
void SetSVGA64k1(void);
/***换页函数***/
void Selectpage1(register char page);


/***显示24位非压缩bmp图***/
void Readbmp64k1(int x, int y, char * path);
/***读取部分64k的bmp图片***/
void Readpartbmp64k1(int x,int y,int x1,int y1,int x2,int y2,char *path);

/***0x117模式下画点函数***/
void Putpixel64k1(int x, int y, unsigned int color);

/***画矩形函数***/
void rectangle_svga1(int x0,int y0,int x1,int y1);

/***关闭图形显示模式***/
void CloseSVGA1(void);
/***设置背景颜色***/
void setbkcolor64k1(int color);

/***24位显示模式下划线***/
void Linel1(int x1, int y1, int x2, int y2, unsigned int color);
/***画矩形块函数(24位）***/
void Barl1(int x1, int y1, int x2, int y2, unsigned int color);
/***画45度斜线***/
void Linel1ean1(int x1, int y1, int x2, int y2, unsigned int color);
/***画斜线***/
void line64k1(int x1, int y1, int x2, int y2, unsigned int color);
/***读取颜色真值表对应的颜色***/
unsigned int ReadColor1(unsigned int x ,unsigned int y ,unsigned int z);
/***储存图像***/
void Saveimagetofile1(int x1,int y1,int x2,int y2,const char * path);
/***加载图像***/
void Loadimagefromfile1(int x1,int y1,int x2,int y2,const char * path);
/***读取大照片中1024*768大小的图片***/
void Readbmplarge1 (int x, int y, char * path);
/***快速读图***/
int bmp_fast1(int y1,int y2,char * path);
/***绘制按钮的通用函数***/
void bmp_draw_button1(int x1, int y1, int x2, int y2, unsigned int color);
/***绘制搜索的横线***/
void bmp_draw_line1(int x1, int y1, int x2, unsigned int color);
/*画圆  圆心位置，半径，颜色，是否实心(是1否0)  成功返回1，失败返回0*/
int drawcircle1(int x, int y, int r, unsigned int color, int flag);
/*画椭圆  圆心位置，x方向半径，y方向半径，颜色，是否实心(是1否0)  成功返回1，失败返回0*/
int drawellipse1(int x, int y, int a, int b, unsigned int color, int flag);
/*画弧*/
void arc2561(int xc, int yc, int r, float stangle, float enangle, unsigned char color);
void draw_play_light1(int xc, int yc); //绘制播放按钮
//void draw_play_dark(int xc, int yc); //绘制播放按钮
void draw_suspend_light1(int xc, int yc); //绘制暂停按钮
void draw_last_light1(int xc, int yc); //绘制上一个按钮
void draw_next_light1(int xc, int yc); //绘制下一个按钮
void draw_back_svga1(int xc, int yc); //绘制返回按钮
void draw_end_svga1(int xc, int yc); //绘制退出按钮
void draw_start_light1(int y); //绘制完成按钮（亮）
void draw_start_dark1(int y); //绘制完成按钮（暗）
int X(int i); //计算拐点的坐标，仅用于收藏按钮
int Y(int i); //计算拐点的坐标，仅用于收藏按钮
void button_collect_light1(int x, int y); //绘制收藏按钮（亮）
void button_collect_dark1(int x, int y); //绘制收藏按钮（暗）
void draw_clock1(int x, int y); //画时钟
void draw_fire1(int x, int y); //画火
void drawxin1(int x, int y, int color);//画爱心 
void draw_tri1(int x1, int y1, int x2, int y2, int x3, int y3, int color);//画三角形 

#endif


