
#ifndef _DRV_KEY_H_
#define _DRV_KEY_H_

#include "typedef.h"

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

#endif
