
#ifndef _DRV_LED_H_
#define _DRV_LED_H_

#include "typedef.h"

#define PORT_LED1 GPIOD

/* 配置GPIO */
void drv_led_init(void);

/* GPIO控制函数（需根据硬件实现） */
void led_set_state(BOOL is_on);

/* 触发LED闪烁（外部调用） */
void start_led_blink(void);

/* LED闪烁任务（每10ms调用一次） */
void led_blink_task(void);

#endif
