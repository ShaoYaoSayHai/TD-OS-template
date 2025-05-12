
#ifndef _SVER_H_
#define _SVER_H_

#include "typedef.h"

void check_key_server(void);

/**
 * @brief LED闪烁任务 状态机模式
 */
void led_blink_task(void) ; 

// 红灯闪烁
void led_red_blink_server(void) ; 
#endif
