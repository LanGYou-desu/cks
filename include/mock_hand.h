#define MOCK_HAND_H
#ifdef MOCK_HAND_H

/*�ֶ�����������*/
int mock_handin(int *flag,int *item);

/*�ֶ����Ƴ������*/
int mock_handout(int *flag,int *item);

/*�����ֶ����ƽ���*/
void draw_mock_hand();

/*���ƻ�����*/
void draw_hand_robot(int x,int y);

/*�ж����������Ƿ��ཻ�ĺ���*/
int isCollision(int rx1, int ry1, int rx2, int ry2, OBS obs);

/*�ܿ��ϰ���*/
int judge_obs(int x, int y);

#endif