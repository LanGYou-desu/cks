#include"allfunc.h"

void input(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1){//���뺯����x1,y1Ϊ��������Ͻ����꣬nameΪ�����ַ�����numΪ�ַ������ȣ�a1,b1,c1,d1Ϊ�������ĸ�������{
    char showtemp[2]= {0,0};//��ʾ�ַ�
	int key;    			//����ֵ
	int i=0,k,temp;
	int border=x1+4;	    //border��ʾ��ʾͼƬ����߽�
	x1=x1+4;
	y1=y1+16;

	for(i=strlen(name)-1;i>=0;i--)
	{
		*showtemp=name[i];
		Put_Asc16_Size(x1+i*16,y1-2,2,2,*showtemp,0);  //��ʾ֮ǰ������ַ������Ա��޸�.
	}                       

	i=strlen(name);         

	while(bioskey(1))		//������뻺����
	{
		bioskey(0);
	}

	border+=16*i;            //���λ��
	
	while(1)     									   /*�����»س���ʱ��ʾ������ϣ��س���ֵΪ13��*/
    {
	    show_gb(border,y1);                            //�����˸ 
		if(bioskey(1)==0||!MouseGet(&mouse))		   //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)				           //��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))       //����Ƿ����������
				{
					break;
				}
			}
		}
		if(bioskey(1))                                 //����Ƿ�������,�������
		{
			temp=bioskey(0)&0x00ff;                    //��ȡ������ַ�ASCII��
			if(temp!='\r'&&temp!='\n')	               //������벻Ϊ�س�����������������������
			{
				if(('0'<=temp&&temp<='9'||('a'<=temp&&temp<='z')/*||temp=='_'*/)&&i<num)	//���Ϊ���ֻ���ĸ���»��ߣ����¼
				{
					bar1(border,y1-3,border+16, y1+29, 0xffff);   //��չ��λ��
					name[i]=temp;				               //�ַ���������ַ���			
					
					*showtemp=temp;                            //��ʾ�µ��ַ����ﵽ������ʵ�������ͬ��
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);         
					i++;
					name[i]='\0';		//����ַ�����β
					border+=16;          //���λ�ú���
					show_gb(border,y1); //��ʾ���
				}
				else if('A'<=temp&&temp<='Z'&&i<num)	//�����ļ��������ִ�Сд����������ļ�����Ҫ���û������ļ��� 
				{						             	//����ע��ʱ�Ͳ����ִ�Сд�� 
					bar1(border,y1-3,border+16, y1+29, 0xffff);
					temp+=32;                   //��дתСд
					name[i]=temp;				//�ַ���������ַ���			
					
					*showtemp=temp;             //���²���ͬ��
					Put_Asc16_Size(border,y1-2,2,2,*showtemp,0);
					i++;
					name[i]='\0';		
					border+=16;
					show_gb(border,y1);
				}
				else if(temp=='\b'&&i>0)			//����Ƿ�Ϊ�˸������������ǰһ���ַ�
				{
					border-=16;                      //���λ��ǰ��
					bar1(border,y1-3,border+16, y1+29, 0xffff);//��չ��λ��
					i--;                                    //�ַ������ȼ�һ
					name[i]='\0';                           //�ַ�����β
					bar1(border,y1-3,border+16, y1+29, 0xffff);//��չ��λ��
					show_gb(border,y1);
				}
			}
			else
			{
				break;
			}
		}
		if(!mouse_press(a1,b1,c1,d1)&&MouseGet(&mouse))		//���������������Ĳ��֣��˳�
		{
			break;
		}
		bar1(border,y1-3,border+16, y1+29, 0xffff);            //��չ��λ��
		if(bioskey(1)==0||!MouseGet(&mouse))			    //��ʱ������ʹ�����˸���ڵ������������ʱ�˳�
		{
			for(k=0;k<100;k++)				                //��ʱ��ͬʱ���������
			{
				delay(2);
				if(bioskey(1)||MouseGet(&mouse))
				{
					break;                                  //����Ƿ�����������������˳�forѭ�������˳���ʱ
				}
			}
		}
	} 
	bar1(border,y1-3,border+16, y1+29, 0xffff);//��չ��λ��
}