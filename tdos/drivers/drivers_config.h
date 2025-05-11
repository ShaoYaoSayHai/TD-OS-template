
#ifndef _DRIVERS_CONFIG_H_
#define _DRIVERS_CONFIG_H_

#ifndef USE_RTOS
#define USE_RTOS (0x00)
#endif

/**
 * * 配置是否导入对应驱动
 */
#define USE_DRV_USART 1

/*************************************************
 * * 类导入
 *************************************************/
#if USE_DRV_USART
#include "drv_usart.h"
#endif

#endif
