#define ENERGY_H
#ifdef ENERGY_H

/*�������*/
int energy_monitor(int *flag,ROHEAD *rohp);

/*����������ؽ���*/
void draw_energy_monitor(ROHEAD *rohp);

/*���ƴ������*/
void draw_none_robot();

/*���*/
void charge(ROHEAD *rohp);

/*��ʾ����*/
void show_energy(int x, int y, ROHEAD *rohp, int type);

/*��ʾ����*/
void show_item(int x, int y, int type);

#endif