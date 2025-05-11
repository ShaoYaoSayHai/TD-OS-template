
#ifndef _TD_TICK_H_
#define _TD_TICK_H_

#include "typedef.h"

// 判断时间a是否在b之后（考虑溢出）
#define time_after(a, b) ((long)(b) - (long)(a) < 0)

// 判断时间a是否在b之前
#define time_before(a, b) time_after(b, a)

// 带等于条件的判断
#define time_after_eq(a, b) ((long)(a) - (long)(b) >= 0)
#define time_before_eq(a, b) time_after_eq(b, a)

/* 时间差值计算（防溢出）*/
#define TIME_DIFF(current, previous) \
    ((current) >= (previous)) ? ((current) - (previous)) : (0xFFFFFFFF - (previous) + (current) + 1)

typedef struct td_tick_t
{
    void (*update_tick)(void);
    uint32_t (*get_tick)(void);
    long tick;
} td_tick_t;

extern td_tick_t td_rt_tick;
;

void td_tick_update(void);

uint32_t td_tick_current_value(void);

/**
 * @brief 时间基准的初始化 采用了定时器 TIM7
 */
void td_timer_tick_init(void);

#endif
