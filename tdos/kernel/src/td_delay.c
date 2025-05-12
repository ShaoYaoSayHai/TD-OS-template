/**
 ******************************************************************************
 * @file    td_delay.c
 * @author  ZhangHW
 * @version V1.2.0
 * @date    2025-05-12
 * @brief   非阻塞延迟的实现，伴随函数server的实现
 * @note    需要严格注意调用规范，避免过于复杂的使用场景
 ******************************************************************************
 */

#include "td_delay.h"
#include "wk_tmr.h"

// * 全局变量
volatile long g_sys_tick = 0;

inline void delay_tick_update(void)
{
    g_sys_tick++;
}

long delay_tick_get(void)
{
    return g_sys_tick ; 
}

// * 初始化定时器 delay所使用
void td_delay_timer_init(void)
{
    crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK, TRUE);
    tmr_cnt_dir_set(TMR6, TMR_COUNT_UP);
    tmr_period_buffer_enable(TMR6, TRUE);
    tmr_base_init(TMR6, 999, 239);
    tmr_primary_mode_select(TMR6, TMR_PRIMARY_SEL_RESET);
    tmr_counter_enable(TMR6, TRUE);
    nvic_irq_enable(TMR6_GLOBAL_IRQn, 7, 0);

    // * 最后才启动定时器
	tmr_interrupt_enable(TMR6, TMR_OVF_INT, TRUE);
}
