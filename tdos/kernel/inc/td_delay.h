
#ifndef _TD_DELAY_H_
#define _TD_DELAY_H_

#include "typedef.h"

// * 延迟控制块
typedef struct DelayControl_t
{
    long start_tick;
    long delay_ms;
    BOOL is_running;
} DelayControl_t;

// * 用于定时器中断中更新当前的全局延迟 tick
void delay_tick_update(void);

// * 返回当前时间基准
long delay_tick_get(void) ; 

// * 初始化定时器 delay所使用
void td_delay_timer_init(void);

#endif
