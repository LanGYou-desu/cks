#define MAP_H
#ifdef MAP_H

#define ECLA 30//��Ч��ײ����(efeective collision length)����������������ײ���
#define ECLB 32//��Ч��ײ���(efeective collision length)�����ڳ�����Լ����վ����ײ���
#define IL 83//�������ڸ��ӵľ���

/*�ϰ���*/
typedef struct{
    int x1;
    int y1;
    int x2;
    int y2;
}OBS;

/*���ܶ�λ��*/
typedef struct{
    int x;
    int y;
}SHELFPOINT;

/*������*/
typedef struct{
    int x;
    int y;
}LIFT;

/*·���ڵ�*/
typedef struct{
    int x;
    int y;
}POINT;

/*��ͼԤ��*/
int map_preview(int *flag);

/*���Ƶ�ͼԤ������*/
void draw_map_preview();

/*��ʼ����ͼ*/
void init_map();

/*��ʼ���ϰ���*/
void init_obs();

/*��ʼ������λ��*/
void init_shelfpoint();

/*��ʼ��������λ��*/
void init_lift();

/*��ʼ���ڵ�*/
void init_mappoint();

#endif