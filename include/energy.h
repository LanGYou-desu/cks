#define ENERGY_H
#ifdef ENERGY_H

/*�������*/
int energy_monitor(int *flag,ROHEAD *rohp);

/*����������ؽ���*/
void draw_energy_monitor(int *flag,ROHEAD *rohp);

/*���ƴ������*/
void draw_none_robot();

/*���*/
void charge(ROHEAD *rohp);

/*��ʾ����*/
void show_energy(ROHEAD *rohp);

#endif