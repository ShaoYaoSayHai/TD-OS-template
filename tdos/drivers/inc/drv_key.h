
#ifndef _DRV_KEY_H_
#define _DRV_KEY_H_

#include "typedef.h"

// * 定义按键状态的枚举类型 ， 包括空闲、去抖动、释放、长按
typedef enum
{

    IDLE,
    DEBOUNCE,
    PRESSED,
    LONG_CHECK,

} KeyState;

BOOL is_key_pressed(void);
// * 初始化按键
void drv_key_gpio_init(void);

// * 按键任务
/**
 * @brief  按键任务 防抖实现 10ms时间基准下运行 状态机下使用定时器设置时间基准
 *         防抖节流和按键长按的功能均可实现
 * @author ZhangHW
 * @private  IDLE,
 * @private  DEBOUNCE,
 * @private  PRESSED,
 * @private  LONG_CHECK
 * @interface 短按 on_short_hold_func
 * @interface 长按 on_long_hold_func
 */
void check_key_task(void);

// * 长时间按下函数
void on_long_hold_func(void);

// * 短时间按下函数
void on_short_hold_func(void);

#endif
