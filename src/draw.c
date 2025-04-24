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
    puthz(370,422,"ȷ��",32,32,0X0000);
    puthz(585,422,"ȡ��",32,32,0X0000);
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
        puthz(379,280,"ȷ�Ϸ��ص�¼����",32,32,0X0000);
    }
    else if(i==1)
    {
        puthz(410,280,"ȷ���˳�����",32,32,0X0000);
    }
    else if(i==2)
    {
        puthz(410,270,"ȷ�����ɱ���",32,32,0X0000);
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

/**********************************************
* ������͵�16λ��ɫ��RGB565��ʽ��
* ԭ�����ָ���ɫͨ����Сֵ�������������
**********************************************/
unsigned int GeneratePastelColor(void) {
    /* ͨ���������ã�������ɫ�� */
    const int minRed = 0x18;   // ��ɫ������ȣ�ԭ��Χ0-31��
    const int minGreen = 0x30; // ��ɫ������ȣ�ԭ��Χ0-63��
    const int minBlue = 0x18;  // ��ɫ������ȣ�ԭ��Χ0-31��
    
    int red = minRed + (rand() % (31 - minRed/2));
    int green = minGreen + (rand() % (63 - minGreen/2));
    int blue = minBlue + (rand() % (31 - minBlue/2));
    
    return (red << 11) | (green << 5) | blue;
}

/**********************************************
* �߼�ͼ��Ԫ�ػ��ƺ���
* ������������ͼ������
**********************************************/
void DrawAestheticPattern(int elementCount) {
    int i, j, x, y, size, shapeType;
    unsigned int mainColor, borderColor;
    int armLength;
    const int maxX = 1024;
    const int maxY = 768;
    
    for(i = 0; i < elementCount; i++) {
        x = 50 + rand() % (maxX-100);  // ��������
        y = 50 + rand() % (maxY-100);
        size = 15 + rand() % 50;      // �ߴ緶Χ15-64
        mainColor = GeneratePastelColor();
        
        /* ����Э���ı߿�ɫ */
        borderColor = mainColor ^ 0x18E3; // ͨ���������Ա�ɫ
        
        shapeType = rand() % 6;  // ����ͼ������
        
        switch(shapeType) {
            case 0: // ˫��ͬ��Բ
                Circlefill(x, y, size, mainColor);
                Circle(x, y, size+2, borderColor);
                break;
                
            case 1: // Բ�Ǿ��Σ�ģ��ʵ�֣�
                bar1(x, y+5, x+size, y+size-5, mainColor); // ˮƽ����
                bar1(x+5, y, x+size-5, y+size, mainColor); // ��ֱ����
                Circlefill(x+5, y+5, 5, mainColor);       // �Ľ�Բ��
                Circlefill(x+size-5, y+5, 5, mainColor);
                Circlefill(x+5, y+size-5, 5, mainColor);
                Circlefill(x+size-5, y+size-5, 5, mainColor);
                break;
                
            case 2: // ����ͬ��Բ
                for(j=size; j>0; j-=3) {
                    Circle(x, y, j, mainColor + j*300);
                }
                break;
                
            case 3: { // ��������
                armLength = size/2;
                Line2(x-armLength, y, x+armLength, y, borderColor); // ˮƽ
                Line2(x, y-armLength, x, y+armLength, borderColor); // ��ֱ
                Line2(x-armLength, y-armLength, x+armLength, y+armLength, borderColor); // �Խ���
                Line2(x+armLength, y-armLength, x-armLength, y+armLength, borderColor);
                break;
            }
                
            case 4: // ���尴ťЧ��
                bar1(x, y, x+size, y+size, mainColor);      // ����
                bar2(x, y, x+size, y+size, borderColor);   // �߿�
                Line2(x+2, y+2, x+size-2, y+2, 0xFFFF);   // �߹���
                Line2(x+2, y+2, x+2, y+size-2, 0xFFFF);
                break;
                
            case 5: // ����Ч��
                Circlefill(x, y, size, mainColor);
                for(j=0; j<3; j++) { // �߹��
                    Putpixel64k(x+size/3-j, y-size/3+j, 0xFFFF);
                }
                break;
        }
    }
}