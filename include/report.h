#define REPORT_H
#ifdef REPORT_H

/*����˵�*/
int report_menu(int *flag);

/*���Ʊ���˵�*/
void draw_report_menu(int choose);

/*������*/
void draw_anime();

/*��������*/
void draw_report();

/*�����*/
void fill_blank(int choose);

/*��ʱ����ʱ�洢��������*/
void update_report(int robonum,int *item,Robot *robot,int type,int is_auto);

/*���ر��浥*/
void download_report();

#endif