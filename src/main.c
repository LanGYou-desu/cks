#include <allfunc.h>

int main()
{
    int flag=0;//ҳ���־
    int robonum=0;//����������
    int item[3]={0,0,0};//��������
    ROHEAD *rohp;//����������ͷָ��
    SHHEAD *shhp;//��������ͷָ��

    rohp->length=0;//��ʼ��������������
    shhp->length=0;//��ʼ������������

    SetSVGA64k();//����ͼ��ģʽ
    mouse_init();//��ʼ�����
    init_map();//��ʼ����ͼ
    
    while(1){
        
        switch(flag){
            
            case 0:welcome(&flag);//��ӭ����
                    break;
            
            case 1:login(&flag);//��¼����
                    break;
            
            case 2:user_register(&flag);//ע�����
                    break;
            
            case 3:main_menu(&flag,&robonum,item);//���˵�����
                    break;
            
            case 4:robo_menu(&flag,&robonum,&rohp);//�����˲˵�����
                    break;

            case 5:item_menu(&flag,item,&shhp);//����˵�����
                    break;

            case 6:energy_monitor(&flag,rohp);//���ܲ˵�����
                    break;

            case 7:mock_menu(&flag,&robonum,item,rohp,shhp);//ģ��˵�����
                    break;   

            case 8:auto_out(&flag,item,rohp,shhp);//�Զ��������
                    break;

            case 9:auto_in(&flag,item,rohp,shhp);//�Զ�������
                    break;

            case 10:map_preview(&flag);//��ͼԤ������
                    break;

            case 12:mock_handin(&flag,item);//�ֶ�ģ��������
                    break;
                
            case 13:mock_handout(&flag,item);//�ֶ�ģ��������
                    break;

            default:flag=3;//������
                    break;
        }

        delay(50);
    }
    
    return 0;
}