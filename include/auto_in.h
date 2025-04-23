#define AUTO_IN_H
#ifdef AUTO_IN_H

/*自动入库*/
int auto_in(int *flag,int *item,ROHEAD *rohp,SHHEAD *shhp);

/*绘制自动入库界面*/
void draw_auto_in(ROHEAD *rohp);

/*入库物品*/
void item_in(SHHEAD *hp,int type);

/*入库模拟*/
void path_in(Robot *robot, int robonum, int *item, SHHEAD *shhp);

#endif