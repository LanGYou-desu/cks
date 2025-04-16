#define MOCK_H
#ifdef MOCK_H

/*模拟主菜单*/
int mock_menu(int *flag, int *robonum, int *item, ROHEAD *rohp, SHHEAD *shhp); 

/*绘制模拟主菜单*/
void draw_mock_menu(int *robonum, int *item);

/*绘制手动按钮*/
void draw_hand(int *item);

/*判断是否能模拟*/
int judge_mock(int robonum, int *item);

/*查找货架节点*/
SHNODE *find_shelf(int type,SHHEAD *hp);

/*更新货架*/
void update_shelf(int type,SHHEAD *hp);

/*为机器人设定目标点*/
void setRobotPoint(Robot *robot, int id, int pointid);

#endif