#include"allfunc.h"

OBS obs[6];
SHELFPOINT shelfpoint[3];
LIFT lift[4];
POINT point[12];

void init_map()
{
    init_obs();
    init_shelfpoint();
    init_lift();
    init_mappoint();
}

void init_obs()
{
    /*����*/
    obs[0].x1=0;
    obs[0].y1=0;
    obs[0].x2=0;
    obs[0].y2=0;
    /*һ�����*/
    obs[1].x1=135;
    obs[1].y1=188;
    obs[1].x2=219;
    obs[1].y2=607;
    /*�������*/
    obs[2].x1=471;
    obs[2].y1=188;
    obs[2].x2=555;
    obs[2].y2=607;
    /*�������*/
    obs[3].x1=807;
    obs[3].y1=188;
    obs[3].x2=891;
    obs[3].y2=607;
    /*���վ*/
    obs[4].x1=384;
    obs[4].y1=44;
    obs[4].x2=640;
    obs[4].y2=104;
    /*���ذ���*/
    obs[5].x1=0;
    obs[5].y1=0;
    obs[5].x2=100;
    obs[5].y2=50;
    /*�����*/
    obs[6].x1=386;
    obs[6].y1=690;
    obs[6].x2=640;
    obs[6].y2=751;
}

void init_shelfpoint()
{
    /*һ�����*/
    shelfpoint[0].x=177;
    shelfpoint[0].y=231;
    /*�������*/
    shelfpoint[1].x=512;
    shelfpoint[1].y=231;
    /*�������*/
    shelfpoint[2].x=848;
    shelfpoint[2].y=231;
}

void init_lift()
{
    /*һ�����*/
    lift[0].x=219;
    lift[0].y=398;
    /*�������*/
    lift[1].x=555;
    lift[1].y=398;
    lift[2].x=471;
    lift[2].y=398;
    /*�������*/
    lift[3].x=807;
    lift[3].y=398;
}

void init_mappoint()
{
    //�����˳���λǰ
    point[0].x=331;
    point[0].y=641;

    //�������
    point[1].x=427;
    point[1].y=665;

    //�������
    point[2].x=600;
    point[2].y=665;

    //���վ��
    point[3].x=427;
    point[3].y=132;

    //���վ��
    point[4].x=600;
    point[4].y=132;

    //һ�Ż���������
    point[5].x=245;
    point[5].y=398;

    //���Ż���������1
    point[6].x=443;
    point[6].y=398;

    //���Ż���������2
    point[7].x=581;
    point[7].y=398;

    //���Ż���������
    point[8].x=780;
    point[8].y=398;

    //һ�Ż����˳���λ
    point[9].x=576;
    point[9].y=710;

    //���Ż����˳���λ
    point[10].x=512;
    point[10].y=710;
    
    //���Ż����˳���λ
    point[11].x=448;
    point[11].y=710;
}