
#include "td_tick.h"
#include "wk_tmr.h"

td_tick_t td_rt_tick;

/**
 * @brief 时间基准的初始化 采用了定时器 TIM7
 */
void td_timer_tick_init(void)
{
    
    // * 初始化时间基准
    td_rt_tick.tick = 0;
    td_rt_tick.get_tick = td_tick_current_value;
    td_rt_tick.update_tick = td_tick_update;
	// * 最后才启动定时器
	tmr_interrupt_enable(TMR7, TMR_OVF_INT, TRUE);
}

void td_tick_update(void)
{
    td_rt_tick.tick++;
}

uint32_t td_tick_current_value(void)
{
    return td_rt_tick.tick;
}
