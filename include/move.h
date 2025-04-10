#define MOVE_H
#ifdef MOVE_H

#define SD 1 //速度延迟
#define FL 8 //步长

/*机器人运动*/
void movef(ROBO *p);
void moveb(ROBO *p);
void movel(ROBO *p);
void mover(ROBO *p);

#endif