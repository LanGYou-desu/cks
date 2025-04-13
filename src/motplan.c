#include"allfunc.h"

Robot* robot_list = NULL;   // ����������ͷ

float fmaxf(float a, float b) {
    return (a > b) ? a : b;
}

float fminf(float a, float b) {
    return (a < b) ? a : b;
}

/*******************************************************
 * �������ƣ�calc_distance
 * ���ܣ����������ŷ�Ͼ��루���㾫�ȣ�
 *******************************************************/
float calc_distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*******************************************************
 * �������ƣ�check_collision
 * ���ܣ�����ƶ������ײ
 * ������dx,dy - �ƻ��ƶ���
 * ���أ�1-��ײ 0-��ȫ
 *******************************************************/
int check_collision(Robot* bot, int dx, int dy) {
    int i;

    int bot_left;
    int bot_right;
    int bot_top;
    int bot_bottom;

    int obs_left;
    int obs_right;
    int obs_top;
    int obs_bottom;

    // ������λ��
    int new_x = bot->x + dx;
    int new_y = bot->y + dy;

    Robot* p = robot_list;
    float dist;

    /* ��ͼ�߽��� */
    if(new_x < ROBOT_SIZE/2 || new_x > SCREEN_WIDTH - ROBOT_SIZE/2 ||
       new_y < ROBOT_SIZE/2 || new_y > SCREEN_HEIGHT - ROBOT_SIZE/2) {
        return 1;
    }

    /* �ϰ�����ײ��⣨AABB�㷨�� */
    for(i=0; i<6; i++) {
        // ����������±߽�
        bot_left = new_x - ROBOT_SIZE/2;
        bot_right = new_x + ROBOT_SIZE/2;
        bot_top = new_y - ROBOT_SIZE/2;
        bot_bottom = new_y + ROBOT_SIZE/2;

        // �ϰ���߽�
        obs_left = obs[i].x1;
        obs_right = obs[i].x2;
        obs_top = obs[i].y1;
        obs_bottom = obs[i].y2;

        // ����ص�
        if(bot_left < obs_right && 
           bot_right > obs_left &&
           bot_top < obs_bottom &&
           bot_bottom > obs_top) {
            return 1;
        }
    }

    /* ������������ײ��� */
    p = robot_list;
    while(p) {
        if(p != bot) {
            // �������ĵ���
            dist = calc_distance(new_x, new_y, p->x, p->y);
            if(dist < ROBOT_SIZE) {
                return 1;
            }
        }
        p = p->next;
    }

    return 0;
}

/*******************************************************
 * �������ƣ�path_adjust
 * ���ܣ�·�����������Ϻ����㷨��
 * ������dx,dy - �����������ƶ���
 *******************************************************/
void path_adjust(Robot* bot, int* dx, int* dy) {
    int i;
    float repel_x = 0, repel_y = 0;
    int base_step = STEP_BASE;
    float dir_x = 0, dir_y = 0;
    float dist, force;
    int obs_cx, obs_cy;
    float vec_x, vec_y;
    float final_dir_x, final_dir_y;
    float length;

    // ����Ŀ�귽��
    if(bot->tx != bot->x || bot->ty != bot->y) {
        dist = calc_distance(bot->x, bot->y, bot->tx, bot->ty);
        dir_x = (bot->tx - bot->x) / dist;
        dir_y = (bot->ty - bot->y) / dist;
    }

    // �ϰ����ų���
    for(i=0; i<6; i++) {
        // �ϰ�������
        obs_cx = (obs[i].x1 + obs[i].x2)/2;
        obs_cy = (obs[i].y1 + obs[i].y2)/2;
        
        // ���ϰ��������
        vec_x = bot->x - obs_cx;
        vec_y = bot->y - obs_cy;
        dist = calc_distance(bot->x, bot->y, obs_cx, obs_cy);
        
        // ��100�����ڲ����ų���
        if(dist < 100.0f) {
            force = (100.0f - dist) / 100.0f;
            repel_x += vec_x * force * 0.5f;
            repel_y += vec_y * force * 0.5f;
        }
    }

    // �ϳɷ�������
    final_dir_x = dir_x * base_step + repel_x;
    final_dir_y = dir_y * base_step + repel_y;
    
    // ��һ������
    length = sqrt(final_dir_x*final_dir_x + final_dir_y*final_dir_y);
    if(length > 0) {
        final_dir_x /= length;
        final_dir_y /= length;
    }

    // ת��Ϊ��������
    *dx = (int)(final_dir_x * base_step);
    *dy = (int)(final_dir_y * base_step);
}

/*******************************************************
 * �������ƣ�robot_update
 * ���ܣ����µ���������״̬
 *******************************************************/
void robot_update(Robot* bot) {
    int dx = 0, dy = 0;

    /* ״̬Ԥ���� */
    switch(bot->state) {
        case 0: // ��������״̬
            // �͵�����⣨���ͺ��ֹ�𵴣�
            if(bot->battery <= LOW_BATTERY + 5.0f) {
                // ����δ����Ŀ��ʱ��¼ԭʼλ��
                if(bot->orig_tx == 0 && bot->orig_ty == 0) {
                    bot->orig_tx = bot->tx;
                    bot->orig_ty = bot->ty;
                }
                // ���ó��վ���꣨�ϰ���4���ģ�
                bot->tx = (obs[4].x1 + obs[4].x2)/2;
                bot->ty = (obs[4].y1 + obs[4].y2)/2;
                bot->state = 1;
            }
            break;
            
        case 1: // ǰ�����վ״̬
            handle_charging(bot); // ����Ƿ񵽴�
            break;
            
        case 2: // �����״̬
            handle_charging(bot); // ���������
            return; // �����ƶ��߼�
    }

    /* ·���滮���ƶ����ǳ��״̬��*/ 
    if(bot->state != 2) {
        path_adjust(bot, &dx, &dy);
        
        // �ֲ���ײ���
        if(!check_collision(bot, dx, dy)) {
            bot->x += dx;
            bot->y += dy;
            bot->battery = fmaxf(bot->battery - BATTERY_COST, 0.0f);
        } else {
            // ��ײ���˱ܲ���
            dx = -dx / 2;
            dy = -dy / 2;
            if(!check_collision(bot, dx, dy)) {
                bot->x += dx;
                bot->y += dy;
            }
        }
    }

    /* ��¼״̬ */
    log_write(bot);
}

void handle_charging(Robot* bot) {
    // ������վ�������꣨�ϰ���4��
    const int charge_cx = (obs[4].x1 + obs[4].x2)/2;
    const int charge_cy = (obs[4].y1 + obs[4].y2)/2;

    /* ״̬1������ǰ�����վ */
    if(bot->state == 1) {
        // �����ж���3�����ݲ
        if(abs(bot->x - charge_cx) <= 3 && 
           abs(bot->y - charge_cy) <= 3) {
            bot->state = 2;  // ������״̬
            bot->x = charge_cx; // ��������
            bot->y = charge_cy;
        }
    }
    
    /* ״̬2������� */
    if(bot->state == 2) {
        // ������ʴ������������
        if(bot->battery < 100.0f) {
            bot->battery += CHARGE_RATE;
            if(bot->battery > 100.0f) {
                bot->battery = 100.0f;
            }
        }
        
        // ������ָ�����
        if(bot->battery >= 100.0f) {
            bot->state = 0;  // ���ع���״̬
            bot->tx = bot->orig_tx; // �ָ�ԭʼĿ��
            bot->ty = bot->orig_ty;
            
            // ����ԭʼĿ���ֹ��������
            bot->orig_tx = 0;
            bot->orig_ty = 0;
            
            // ����һ����־��¼
            log_write(bot);
        }
    }
}


/*******************************************************
 * �������ƣ�log_write
 * ���ܣ�д��״̬��־
 *******************************************************/
void log_write(Robot* bot) {
    fprintf(bot->logfile, "%d %d\n",bot->x, bot->y); 
    fflush(bot->logfile); // ȷ��ʵʱд��
}

/*******************************************************
 * �������ƣ�main_loop
 * ���ܣ���ѭ������
 *******************************************************/
void main_loop(void) {
    Robot* current;
    while(!kbhit()) { // ��������˳�
        current = robot_list;
        while(current) {
            robot_update(current);
            bar1(current->x - ROBOT_SIZE/2, current->y - ROBOT_SIZE/2, 
                current->x + ROBOT_SIZE/2, current->y + ROBOT_SIZE/2, 
                0XFFFF); // �����λ��
            draw_robot(current->x, current->y, 0); // ���ƻ�����
            current = current->next;
        }
        delay(1); // Լ10Hz����Ƶ��
    }
}
