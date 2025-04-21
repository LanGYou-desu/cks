#include "allfunc.h"

int user_register(int *flag)
{
    USER temp = {0};        //临时用户信息
	char judge[20] = {0};   //用于判段密码是否一致

    mouse_off(&mouse);
	draw_register();
    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(325,177,705,225) == 1)
        {
            mouse_off(&mouse);
            bar1(325,177,705,225,0xFFFF);
			put_inputline(325,225,380);
            strcpy(temp.account,"\0");
            input(325,177,temp.account,18,325,177,705,225);//获取账号
			mouse_on(mouse);
        }
		else if(mouse_press(325,302,705,350) == 1)
		{
			mouse_off(&mouse);
			bar1(325,302,705,350,0xFFFF);
			put_inputline(325,350,380);
			strcpy(temp.password,"\0");
			Getcode(325,302,temp.password,18,325,302,705,350);//获取密码
			mouse_on(mouse);
		}
		else if(mouse_press(325,427,705,475) == 1)
		{
			mouse_off(&mouse);
			bar1(325,427,705,475,0xFFFF);
			put_inputline(325,475,380);
			strcpy(judge,"\0");
			Getcode(325,427,judge,18,325,427,705,475);//获取密码
			mouse_on(mouse);
		}
		else if(mouse_press(0,0,100,50) == 1)
		{
			*flag = 0;
			return 0;
		}
		if(mouse_press(374,595,653,690) == 1)
		{
			if(strcmp(temp.account,"\0") == 0 || strcmp(temp.password,"\0") == 0 || strcmp(judge,"\0") == 0)
			{
				mouse_off(&mouse);	
				prt_hz24(410,380,"请填写完整信息！",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 2;
				return 0;
			}
			else if(strcmp(temp.password,judge) != 0)
			{
				mouse_off(&mouse);
				prt_hz24(410,380,"两次密码不一致！",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 2;
				return 0;
			}
			else
			{
				if(save_user(temp) == 0)
				{
					mouse_off(&mouse);
					prt_hz24(440,380,"注册成功！",10,"HZK\\Hzk24h");
					delay(500);
					*flag = 0;
					return 0;
				}
				else{
					delay(500);
					*flag = 2;
					return 0;
				}
			}
		}
    }
}

void draw_register()
{
	bar1(0,0,1024,768,0XFFFF);
	bar1(0,0,100,50,0X67FC);
	draw_button(374,595,653,690);
    puthz(470,619,"注册",48,48,0X0000);
	puthz(18,9,"返回",32,32,0X0000);
    draw_commoninput(325,225,380,"请输入账号");
    draw_commoninput(325,350,380,"请输入密码");
    draw_commoninput(325,475,380,"请再次确认密码");
}

int login(int *flag)
{
	USER temp = {0};        //临时用户信息

	mouse_off(&mouse);
	draw_login();
	mouse_on(mouse);

	while(1)
	{
		mouse_show(&mouse);
		if(mouse_press(325,222,705,270) == 1)
		{
			mouse_off(&mouse);
			bar1(325,222,705,270,0xFFFF);
			put_inputline(325,270,380);
			strcpy(temp.account,"\0");
			input(325,222,temp.account,18,325,222,705,270);//获取账号
			mouse_on(mouse);
		}
		else if(mouse_press(325,377,705,425) == 1)
		{
			mouse_off(&mouse);
			bar1(325,377,705,425,0xFFFF);
			put_inputline(325,425,380);
			strcpy(temp.password,"\0");
			Getcode(325,377,temp.password,18,325,377,705,425);//获取密码
			mouse_on(mouse);
		}
		else if(mouse_press(0,0,100,50) == 1)
		{
			*flag = 0;
			return 0;
		}
		if(mouse_press(374,595,653,690) == 1)
		{
			if(strcmp(temp.account,"\0") == 0 || strcmp(temp.password,"\0") == 0)
			{
				mouse_off(&mouse);
				prt_hz24(410,325,"请填写完整信息！",10,"HZK\\Hzk24h");
				delay(500);
				*flag = 1;
				return 0;
			}
			else
			{
				if(Check_info("C://cks/user/user.dat",temp.account,temp.password) == 0)
				{
					mouse_off(&mouse);
					prt_hz24(440,325,"登录成功！",10,"HZK\\Hzk24h");
					login_flag = 1;
					delay(500);
					*flag = 3;
					return 0;
				}
				else
				{
					mouse_off(&mouse);
					prt_hz24(385,325,"用户不存在或密码错误！",10,"HZK\\Hzk24h");
					delay(500);
					*flag = 1;
					return 0;
				}
			}
		}
	}
}

void draw_login()
{
	bar1(0,0,1024,768,0XFFFF);
	bar1(0,0,100,50,0X67FC);
	draw_button(374,595,653,690);
	puthz(18,9,"返回",32,32,0X0000);
	puthz(470,619,"登录",48,48,0X0000);
	draw_commoninput(325,270,380,"请输入账号");
	draw_commoninput(325,425,380,"请输入密码");
}

/***获取用户名函数***/
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1)//x1,y1为输入框左上角坐标，name为存放输入字符串的数组，num为数组长度
{
	char showtemp[2]= {0,0};//显示字符
	int key;    			//按键值
	int i=0,k,temp;
	int border=x1+4;	    //border表示显示图片的左边界
	x1=x1+4;
	y1=y1+15;

	for(i=strlen(name)-1;i>=0;i--)
	{
		*showtemp=name[i];
		prt_asc16_ch(x1+i*8,y1-2,showtemp[0],0);  //显示之前输入的字符串，以便修改.
	}                       

	i=strlen(name);         

	while(bioskey(1))		//清空输入缓冲区
	{
		bioskey(0);
	}

	border+=8*i;            //光标位置
	
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
					bar1(border,y1,border+8, y1+32, 0xffff);   //清空光标位置
					name[i]=temp;				               //字符送入给定字符串			
					
					*showtemp=temp;                            //显示新的字符串达到画面与实际输入的同步
					prt_asc16(border,y1-2,showtemp,0);         
					i++;
					name[i]='\0';		//标记字符串结尾
					border+=8;          //光标位置后移
					show_gb(border,y1); //显示光标
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//由于文件名不区分大小写，而后面的文件部分要用用户名做文件名 
				{						             	//故在注册时就不区分大小写了 
					bar1(border,y1,border+8, y1+32, 0xffff);
					temp+=32;                   //大写转小写
					name[i]=temp;				//字符送入给定字符串			
					
					*showtemp=temp;             //以下操作同上
					prt_asc16(border,y1-2,showtemp,0);
					i++;
					name[i]='\0';		
					border+=8;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//检测是否为退格键，是则消除前一个字符
				{
					border-=8;                      //光标位置前移
					bar1(border,y1,border+8, y1+32, 0xffff);//清空光标位置
					i--;                                    //字符串长度减一
					name[i]='\0';                           //字符串结尾
					bar1(border,y1,border+8, y1+32, 0xffff);//清空光标位置
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
		bar1(border,y1,border+8, y1+32, 0xffff);            //清空光标位置
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
	bar1(border,y1,border+8, y1+32, 0xffff);//清空光标位置
}

/* 获取密码函数 */
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1)//x1,y1为输入框左上角坐标，name为存放输入字符串的数组，num为数组长度
{
	char showtemp[2]= {0,0};
	int key;    			//按键值
	int i=0,k,temp;
	int border=x1+4;	    //border表示显示图片的左边界
	x1=x1+4;
	y1=y1+16;
	for(i=strlen(code)-1;i>=0;i--)
	{
		*showtemp=code[i];
		Put_Asc16_Size(x1+i*16,y1-2,2,2,'*',0);//显示之前输入的字符串，以便修改.
	}
	i=strlen(code);

	while(bioskey(1))					//清空输入缓冲区
	{
		bioskey(0);
	}

	border+=16*i;  //光标位置

	while(1)     													//当按下回车键时表示输入完毕（回车键值为13）
   {
	   show_gb(border,y1);
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)	   			//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
		if(bioskey(1))   //检测是否有输入,有则继续
		{
			temp=bioskey(0)&0x00ff;
			if(temp!='\r'&&temp!='\n')	//检测输入不为回车键，则继续，否则输入结束
			{
				if(('0'<=temp&&temp<='9'||'a'<=temp&&temp<='z'||temp=='_')&&i<num)	//检测为数字或字母或下划线，则记录
				{
					bar1(border,y1-3,border+16, y1+29, 0xffff);//清空光标位置
					code[i]=temp;				//字符送入给定字符串			
					
					*showtemp=temp;
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0); //显示新的字符串达到画面与实际输入的同步
					
					delay(150);                        
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'_',0);
					delay(50);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'*',0);
					
					i++;
					code[i]='\0';		//标记字符串结尾
					border+=16;
					show_gb(border,y1);
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//由于文件名不区分大小写，而后面的文件部分要用用户名做文件名 
				{							            //故在注册时就不区分大小写了 
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					temp+=32;                   //大写转小写
					code[i]=temp;				//字符送入给定字符串			
					
					*showtemp=temp;             //显示新的字符串达到画面与实际输入的同步
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);
					
					delay(300);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'_',0);
					delay(100);
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					Put_Asc16_Size(border,y1-2,2,2,'*',0);
					
					i++;
					code[i]='\0';		//标记字符串结尾
					border+=16;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//检测是否为退格键，是则消除前一个字符
				{
					border-=16;
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					i--;
					code[i]=0;
					bar1(border,y1-3,border+16, y1+29, 0xffff);
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
		bar1(border,y1-3,border+16, y1+29, 0xffff);
		if(bioskey(1)==0||!MouseGet(&mouse))			//延时函数，使光标闪烁，在点击鼠标或有输入时退出
		{
			for(k=0;k<100;k++)				//延时的同时检测鼠标键盘
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;
				}
			}
		}
	}
	bar1(border,y1-3,border+16, y1+29, 0xffff);
}
