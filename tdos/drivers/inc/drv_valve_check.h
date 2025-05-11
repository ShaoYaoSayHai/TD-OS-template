
#ifndef _DRV_VALVE_CHECK_H_
#define _DRV_VALVE_CHECK_H_

#include "typedef.h"

typedef enum {
    STATE_IDLE,        // 空闲状态
    STATE_ACTIVE,      // GPIO激活状态（拉高）
    STATE_DEBOUNCE     // 防抖等待状态
} gpio_state_t;

// * 初始化测试阀门相关引脚
void driver_vcheck_gpio_init(void);

// * 接地引脚调整
void driver_vcheck_ground_ready(void);

// * 测试一次
void driver_vcheck_start_once(BOOL* bTrigger);

#endif
