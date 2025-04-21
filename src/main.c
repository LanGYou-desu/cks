#include <allfunc.h>

int main()
{
    int flag=0;//页面标志
    int robonum=0;//机器人数量
    int item[3]={0,0,0};//货物数量
    ROHEAD *rohp;//机器人链表头指针
    SHHEAD *shhp;//货架链表头指针

    rohp->length=0;//初始化机器人链表长度
    shhp->length=0;//初始化货架链表长度

    SetSVGA64k();//设置图形模式
    mouse_init();//初始化鼠标
    init_map();//初始化地图
    
    while(1){
        
        switch(flag){
            
            case 0:welcome(&flag);//欢迎界面
                    break;
            
            case 1:login(&flag);//登录界面
                    break;
            
            case 2:user_register(&flag);//注册界面
                    break;
            
            case 3:main_menu(&flag,&robonum,item);//主菜单界面
                    break;
            
            case 4:robo_menu(&flag,&robonum,&rohp);//机器人菜单界面
                    break;

            case 5:item_menu(&flag,item,&shhp);//货物菜单界面
                    break;

            case 6:energy_monitor(&flag,rohp);//货架菜单界面
                    break;

            case 7:mock_menu(&flag,&robonum,item,rohp,shhp);//模拟菜单界面
                    break;   

            case 8:auto_out(&flag,item,rohp,shhp);//自动出库界面
                    break;

            case 9:auto_in(&flag,item,rohp,shhp);//自动入库界面
                    break;

            case 10:map_preview(&flag);//地图预览界面
                    break;

            case 11:introduction(&flag);//程序介绍界面
                    break;
 
            case 12:mock_handin(&flag,item);//手动模拟入库界面
                    break;
                
            case 13:mock_handout(&flag,item);//手动模拟出库界面
                    break;

            default:flag=3;//防卡死
                    break;
        }

        delay(50);
    }
    
    return 0;
}