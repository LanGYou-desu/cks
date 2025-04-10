#define MOCK_HAND_H
#ifdef MOCK_HAND_H

/*手动控制入库界面*/
int mock_handin(int *flag,int *item);

/*手动控制出库界面*/
int mock_handout(int *flag,int *item);

/*绘制手动控制界面*/
void draw_mock_hand();

/*绘制机器人*/
void draw_hand_robot(int x,int y);

/*判断两个矩形是否相交的函数*/
int isCollision(int rx1, int ry1, int rx2, int ry2, OBS obs);

/*避开障碍物*/
int judge_obs(int x, int y);

#endif