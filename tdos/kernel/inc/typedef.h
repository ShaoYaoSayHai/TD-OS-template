#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"

#include "assert.h" // 断言支持

#include "at32f403a_407.h"
#include "at32f403a_407_gpio.h"
#include "at32f403a_407_wk_config.h"
#include "wk_system.h"

typedef enum
{
    key_undefined = -4,
    value_size_out_of_range = -3,
    value_type_is_error = -2,
    value_undefined = -1,
    find_value_ok = 0

} JSON_STATUS;

typedef int BOOL;

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

// * 时钟初始化
#define Periph_GPIOC_Clk_Enable(cond)                              \
    do                                                             \
    {                                                              \
        if (cond)                                                  \
        {                                                          \
            crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE); \
        }                                                          \
    } while (0)

#define Periph_GPIOD_Clk_Enable(cond)                              \
    do                                                             \
    {                                                              \
        if (cond)                                                  \
        {                                                          \
            crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE); \
        }                                                          \
    } while (0)

#endif
