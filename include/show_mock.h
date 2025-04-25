#define SHOW_MOCK_H
#ifdef SHOW_MOCK_H

/*显示轨迹*/
void draw_trace(int robonum);

/*模拟重演出库*/
void watchMockin(int robonum,int speed,int *item);

/*模拟重演出库*/
void watchMockout(int robonum,int speed,int *item);

/*快速充电*/
void quick_charge(ROHEAD *rohp);

/*手动重演*/
void rehand(int flag,int *item);

#endif