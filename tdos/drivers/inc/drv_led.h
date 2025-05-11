
#ifndef _DRV_LED_H_
#define _DRV_LED_H_

#include "typedef.h"
/* 状态机枚举类型 */
typedef enum
{
    LED_IDLE,     // 空闲状态
    LED_DEBOUNCE, // 触发防抖检测
    LED_BLINK_ON, // 闪烁亮阶段
    LED_BLINK_OFF // 闪烁灭阶段
} LedBlinkState;

#define DEBOUNCE_TIME 2   // 消抖时间20ms（2 * 10ms）
#define BLINK_INTERVAL 50 // 闪烁间隔500ms（50 * 10ms）
#define MAX_BLINKS 5      // 最大闪烁次数（可选限制）

#define PORT_LED1 GPIOD

/* 配置GPIO */
void drv_led_init(void);

/* GPIO控制函数（需根据硬件实现） */
void led_set_state(BOOL is_on);

// /* 触发LED闪烁（外部调用） */
// void start_led_blink(void);

// /* LED闪烁任务（每10ms调用一次） */
// void led_blink_task(void);

#endif
