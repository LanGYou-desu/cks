#define REPORT_H
#ifdef REPORT_H

/*报告菜单*/
int report_menu(int *flag);

/*绘制报告菜单*/
void draw_report_menu(int choose);

/*进度条*/
void draw_anime();

/*画出报告*/
void draw_report();

/*填充表格*/
void fill_blank(int choose);

/*按时间临时存储报告数据*/
void update_report(int robonum,int *item,Robot *robot,int type,int is_auto);

/*下载报告单*/
void download_report();

#endif