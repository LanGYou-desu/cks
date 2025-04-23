#define AUTO_IN_H
#ifdef AUTO_IN_H

/*自动出库*/
int auto_out(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp);

/*绘制自动出库界面*/
void draw_auto_out(ROHEAD *rohp);

/*初始化货架*/
void init_item(int *item,SHHEAD *shhp);

/*出库物品*/
void item_out(SHHEAD *hp,int type);

/*出库模拟*/
void path_out(Robot *robot, int robonum, int *item, SHHEAD *shhp);

#endif