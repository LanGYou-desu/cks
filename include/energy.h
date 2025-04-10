#define ENERGY_H
#ifdef ENERGY_H

/*能量监控*/
int energy_monitor(int *flag,ROHEAD *rohp);

/*绘制能量监控界面*/
void draw_energy_monitor(int *flag,ROHEAD *rohp);

/*绘制错误界面*/
void draw_none_robot();

/*充电*/
void charge(ROHEAD *rohp);

/*显示能量*/
void show_energy(ROHEAD *rohp);

#endif