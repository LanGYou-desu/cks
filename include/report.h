#define REPORT_H
#ifdef REPORT_H

/*����˵�*/
int report_menu(int *flag);

/*���Ʊ���˵�*/
void draw_report();

/*��ʱ����ʱ�洢��������*/
void update_report(int robonum,int *item,ROHEAD *head);

/*���ر��浥*/
void download_report();

#endif