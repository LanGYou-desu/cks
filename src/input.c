#include"allfunc.h"

void input(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1){//输入函数，x1,y1为输入框左上角坐标，name为输入字符串，num为字符串长度，a1,b1,c1,d1为输入框的四个角坐标{
    char showtemp[2]= {0,0};//显示字符
	int key;    			//按键值
	int i=0,k,temp;
	int border=x1+4;	    //border表示显示图片的左边界
	x1=x1+4;
	y1=y1+16;

	for(i=strlen(name)-1;i>=0;i--)
	{
		*showtemp=name[i];
		Put_Asc16_Size(x1+i*16,y1-2,2,2,*showtemp,0);  //显示之前输入的字符串，以便修改.
	}                       

	i=strlen(name);         

	while(bioskey(1))		//清空输入缓冲区
	{
		bioskey(0);
	}

	border+=16*i;            //光标位置
	
	while(1)     									   /*当按下回车键时表示输入完毕（回车键值为13）*/
    {
	    show_gb(border,y1);                            //光标闪烁 
		if(bioskey(1)==0||!MouseGet(&mouse))		   //延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				           //延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))       //检测是否有输入或点击
				{
					break;
				}
			}
		}
		if(bioskey(1))                                 //检测是否有输入,有则继续
		{
			temp=bioskey(0)&0x00ff;                    //获取输入的字符ASCII码
			if(temp!='\r'&&temp!='\n')	               //检测输入不为回车键，则继续，否则输入结束
			{
				if(('0'<=temp&&temp<='9'||('a'<=temp&&temp<='z')/*||temp=='_'*/)&&i<num)	//检测为数字或字母或下划线，则记录
				{
					bar1(border,y1-3,border+16, y1+29, 0xffff);   //清空光标位置
					name[i]=temp;				               //字符送入给定字符串			
					
					*showtemp=temp;                            //显示新的字符串达到画面与实际输入的同步
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);         
					i++;
					name[i]='\0';		//标记字符串结尾
					border+=16;          //光标位置后移
					show_gb(border,y1); //显示光标
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//由于文件名不区分大小写，而后面的文件部分要用用户名做文件名 
				{						             	//故在注册时就不区分大小写了 
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					temp+=32;                   //大写转小写
					name[i]=temp;				//字符送入给定字符串			
					
					*showtemp=temp;             //以下操作同上
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);
					i++;
					name[i]='\0';		
					border+=16;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//检测是否为退格键，是则消除前一个字符
				{
					border-=16;                      //光标位置前移
					bar1(border,y1-3,border+16, y1+29, 0xffff);//清空光标位置
					i--;                                    //字符串长度减一
					name[i]='\0';                           //字符串结尾
					bar1(border,y1-3,border+16, y1+29, 0xffff);//清空光标位置
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!mouse_press(a1,b1,c1,d1)&&MouseGet(&mouse))		//如果鼠标点击输入框外的部分，退出
		{
			break;
		}
		bar1(border,y1-3,border+16, y1+29, 0xffff);            //清空光标位置
		if(bioskey(1)==0||!MouseGet(&mouse))			    //延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				                //延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;                                  //检测是否有输入或点击，有则退出for循环，即退出延时
				}
			}
		}
	} 
	bar1(border,y1-3,border+16, y1+29, 0xffff);//清空光标位置
}