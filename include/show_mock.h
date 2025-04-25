#define SHOW_MOCK_H
#ifdef SHOW_MOCK_H

/*显示轨迹*/
void draw_trace(int robonum);

/*模拟重演*/
void watchMock(int robonum,int speed);

/*快速充电*/
void quick_charge(ROHEAD *rohp);

/*手动重演*/
void rehand(int flag,int *item);

#endif