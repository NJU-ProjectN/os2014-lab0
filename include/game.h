#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

/* 初始化串口 */
void init_serial();

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key(int ch);
bool query_key(int ch);
int last_key_code(void);

/* 定义fly_t链表 */
LINKLIST_DEF(fly)
	float x, y;
	int text;
	float v;
LINKLIST_DEF_FI(fly)

/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
void create_new_letter(void);
void update_letter_pos(void);
bool update_keypress(void);

int get_hit(void);
int get_miss(void);
int get_fps(void);
void set_fps(int fps);
fly_t characters(void);

void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

#endif
