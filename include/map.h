#define MAP_H
#ifdef MAP_H

#define ECLA 30//有效碰撞长度(efeective collision length)，用于升降机的碰撞检测
#define ECLB 32//有效碰撞宽度(efeective collision length)，用于出入口以及充电站的碰撞检测
#define IL 83//货架相邻格子的距离

/*障碍物*/
typedef struct{
    int x1;
    int y1;
    int x2;
    int y2;
}OBS;

/*货架定位点*/
typedef struct{
    int x;
    int y;
}SHELFPOINT;

/*升降机*/
typedef struct{
    int x;
    int y;
}LIFT;

/*地图预览*/
int map_preview(int *flag);

/*绘制地图预览界面*/
void draw_map_preview();

/*初始化地图*/
void init_map();

/*初始化障碍物*/
void init_obs();

/*初始化货架位置*/
void init_shelfpoint();

/*初始化升降机位置*/
void init_lift();

#endif