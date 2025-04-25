#define REPORT_H
#ifdef REPORT_H

/*报告菜单*/
int report_menu(int *flag);

/*绘制报告菜单*/
void draw_report();

/*按时间临时存储报告数据*/
void update_report(int robonum,int *item,ROHEAD *head);

/*下载报告单*/
void download_report();

#endif