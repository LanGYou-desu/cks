#include"allfunc.h"

void draw_trace(int robonum)
{
    int color=1;
    int i=0,j=0;
    int x=0,y=0;    //坐标
    int px=0,py=0;  //上一个坐标
    FILE *fp;

    char tracefile[3][30]={
        "path\\robot1.log",
        "path\\robot2.log",
        "path\\robot3.log"
    };

    for(i=0;i<robonum;i++)
    {
        fp=fopen(tracefile[i],"r");
        if(fp==NULL)
        {
            printf("文件打开失败！\n");
            return;
        }
        if(color==1)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0XE126);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        else if(color==2)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0X0235);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        else if(color==3)
        {
            while(fscanf(fp,"%d,%d",&x,&y)!=EOF)
            {
                if(j==0)
                {
                    px=x;
                    py=y;
                    j++;
                }
                else
                {
                    Line_Thick(px,py,x,y,2,0X13A6);
                    px=x;
                    py=y;
                }
                delay(1);
            }
        }
        color++;
        fclose(fp);
    }
}

void watchMockin(int robonum,int speed,int *item)
{
    int i=0,j=0;
    int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
    int px1=0,py1=0,px2=0,py2=0,px3=0,py3=0;
    int  type1=0,ptype1=0,type2=0,ptype2=0,type3=0,ptype3=0;
    int titem[3];
    SHNODE *shhp=NULL;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;

    char mockfile[3][30]={
        "path\\robot1.log",
        "path\\robot2.log",
        "path\\robot3.log"
    };

    shhp=init_shelflist();
    shhp=create_shelflist(shhp,item);   

    for(i=0;i<3;i++)
    {
        titem[i]=item[i];
    }

    fp1=fopen(mockfile[0],"r");
    fp2=fopen(mockfile[1],"r");
    fp3=fopen(mockfile[2],"r");

    if(robonum==1)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF)
        {
            if(type1==0&&ptype1!=0)
            {
                item_in(shhp,ptype1);
                update_shelf(ptype1,shhp);
            }
            ptype1=type1;

            if(px1==0&&py1==0)
            {
                px1=x1;
                py1=y1;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                draw_robot(x1,y1,type1);
                px1=x1;
                py1=y1;
            }
            delay(speed);
        }
    }
    else if(robonum==2)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF&&fscanf(fp2,"%d,%d,%d",&x2,&y2,&type2)!=EOF)
        {
            if(type1==0&&ptype1!=0)
            {
                item_in(shhp,ptype1);
                update_shelf(ptype1,shhp);
            }
            if(type2==0&&ptype2!=0)
            {
                item_in(shhp,ptype2);
                update_shelf(ptype2,shhp);
            }
            ptype1=type1;
            ptype2=type2;

            if(px1==0&&py1==0&&px2==0&&py2==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
                draw_robot(px2,py2,type2);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                draw_robot(x1,y1,type1);
                draw_robot(x2,y2,type2);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }
    else if(robonum==3)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF&&fscanf(fp2,"%d,%d,%d",&x2,&y2,&type2)!=EOF&&fscanf(fp3,"%d,%d,%d",&x3,&y3,&type3)!=EOF)
        {
            if(type1==0&&ptype1!=0)
            {
                item_in(shhp,ptype1);
                update_shelf(ptype1,shhp);
            }
            if(type2==0&&ptype2!=0)
            {
                item_in(shhp,ptype2);
                update_shelf(ptype2,shhp);
            }
            if(type3==0&&ptype3!=0)
            {
                item_in(shhp,ptype3);
                update_shelf(ptype3,shhp);
            }
            ptype1=type1;   
            ptype2=type2;
            ptype3=type3;

            if(px1==0&&py1==0&&px2==0&&py2==0&&px3==0&&py3==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                px3=x3;
                py3=y3;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                bar1(point[11].x-25,point[11].y-25,point[11].x+25,point[11].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
                draw_robot(px2,py2,type2);
                draw_robot(px3,py3,type3);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                bar1(px3-25,py3-25,px3+25,py3+25,0XFFFF);
                draw_robot(x1,y1,type1);
                draw_robot(x2,y2,type2);
                draw_robot(x3,y3,type3);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

void watchMockout(int robonum,int speed,int *item)
{
    int i=0,j=0;
    int x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
    int px1=0,py1=0,px2=0,py2=0,px3=0,py3=0;
    int  type1=0,ptype1=0,type2=0,ptype2=0,type3=0,ptype3=0;
    int titem[3];
    SHNODE *shhp=NULL;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;

    char mockfile[3][30]={
        "path\\robot1.log",
        "path\\robot2.log",
        "path\\robot3.log"
    };

    shhp=init_shelflist();
    shhp=create_shelflist(shhp,item);   

    init_item(item,shhp);

    for(i=0;i<3;i++)
    {
        titem[i]=item[i];
    }

    fp1=fopen(mockfile[0],"r");
    fp2=fopen(mockfile[1],"r");
    fp3=fopen(mockfile[2],"r");

    if(robonum==1)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF)
        {
            if(type1!=0&&ptype1==0)
            {
                item_out(shhp,type1);
                update_shelf(type1,shhp);
            }
            ptype1=type1;

            if(px1==0&&py1==0)
            {
                px1=x1;
                py1=y1;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                draw_robot(x1,y1,type1);
                px1=x1;
                py1=y1;
            }
            delay(speed);
        }
    }
    else if(robonum==2)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF&&fscanf(fp2,"%d,%d,%d",&x2,&y2,&type2)!=EOF)
        {
            if(type1!=0&&ptype1==0)
            {
                item_out(shhp,type1);
                update_shelf(type1,shhp);
            }
            if(type2!=0&&ptype2==0)
            {
                item_out(shhp,type2);
                update_shelf(type2,shhp);
            }
            ptype1=type1;
            ptype2=type2;

            if(px1==0&&py1==0&&px2==0&&py2==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
                draw_robot(px2,py2,type2);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                draw_robot(x1,y1,type1);
                draw_robot(x2,y2,type2);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }
    else if(robonum==3)
    {
        while(fscanf(fp1,"%d,%d,%d",&x1,&y1,&type1)!=EOF&&fscanf(fp2,"%d,%d,%d",&x2,&y2,&type2)!=EOF&&fscanf(fp3,"%d,%d,%d",&x3,&y3,&type3)!=EOF)
        {
            if(type1!=0&&ptype1==0)
            {
                item_out(shhp,type1);
                update_shelf(type1,shhp);
            }
            if(type2!=0&&ptype2==0)
            {
                item_out(shhp,type2);
                update_shelf(type2,shhp);
            }
            if(type3!=0&&ptype3==0)
            {
                item_out(shhp,type3);
                update_shelf(type3,shhp);
            }
            ptype1=type1;
            ptype2=type2;
            ptype3=type3;

            if(px1==0&&py1==0&&px2==0&&py2==0&&px3==0&&py3==0)
            {
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
                px3=x3;
                py3=y3;
                bar1(point[9].x-25,point[9].y-25,point[9].x+25,point[9].y+25,0XFFFF);
                bar1(point[10].x-25,point[10].y-25,point[10].x+25,point[10].y+25,0XFFFF);
                bar1(point[11].x-25,point[11].y-25,point[11].x+25,point[11].y+25,0XFFFF);
                draw_robot(px1,py1,type1);
                draw_robot(px2,py2,type2);
                draw_robot(px3,py3,type3);
            }
            else
            {
                bar1(px1-25,py1-25,px1+25,py1+25,0XFFFF);
                bar1(px2-25,py2-25,px2+25,py2+25,0XFFFF);
                bar1(px3-25,py3-25,px3+25,py3+25,0XFFFF);
                draw_robot(x1,y1,type1);
                draw_robot(x2,y2,type2);
                draw_robot(x3,y3,type3);
                px1=x1;
                py1=y1;
                px2=x2;
                py2=y2;
            }
            delay(speed);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

void quick_charge(ROHEAD *rohp)
{
    RONODE *p=rohp->head;
    while(p!=NULL)
    {
        p->robot.energy=100;
        p=p->next;
    }
} 

void rehand(int flag,int *item)
{
    int i;
    int x=0,y=0;
    int px=0,py=0;
    int type=0,ptype=0;
    int count=0;
    int titem[3];

    SHNODE *shhp=NULL;
    FILE *fp;

    for(i=0;i<3;i++)
    {
        titem[i]=item[i];
    }

    shhp=init_shelflist();
    shhp=create_shelflist(shhp,titem);

    if(flag==1)
    {
        fp=fopen("path\\pathin.txt","r");
        if(fp==NULL)
        {
            printf("文件打开失败！\n");
            return;
        }
        while(fscanf(fp,"%d %d %d",&x,&y,&type)!=EOF)
        {
            if(type==0&&ptype!=0)
            {
                item_in(shhp,ptype);
                update_shelf(ptype,shhp);
            }
            ptype=type;

            if(count==0)
            {
                px=x;
                py=y;
                bar1(308-25,710-25,308+25,710+25,0XFFFF);
                draw_robot(px,py,type);
                count++;
            }
            else
            {
                bar1(px-25,py-25,px+25,py+25,0XFFFF);
                draw_robot(x,y,type);
                px=x;
                py=y;
            }
            delay(25);
        }
    }
    else if(flag==2)
    {
        init_item(item,shhp);

        fp=fopen("path\\pathout.txt","r");
        if(fp==NULL)
        {
            printf("文件打开失败！\n");
            return;
        }
        while(fscanf(fp,"%d %d %d",&x,&y,&type)!=EOF)
        {
            if(type!=0&&ptype==0)
            {
                item_out(shhp,type);
                update_shelf(type,shhp);
            }
            ptype=type;

            if(count==0)
            {
                px=x;
                py=y;
                bar1(308-25,710-25,308+25,710+25,0XFFFF);
                draw_robot(px,py,type);
                count++;
            }
            else
            {
                bar1(px-25,py-25,px+25,py+25,0XFFFF);
                draw_robot(x,y,type);
                px=x;
                py=y;
            }
            delay(25);
        }
    }
    draw_robot(x,y,0);
    bar1(x-25,y-25,x+25,y+25,0XFFFF);
}