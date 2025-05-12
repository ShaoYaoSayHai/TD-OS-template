/* add user code begin Header */
/**
 **************************************************************************
 * @file     main.c
 * @brief    main program
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f403a_407_wk_config.h"
#include "wk_debug.h"
#include "wk_i2c.h"
#include "wk_spi.h"
#include "wk_tmr.h"
#include "wk_usart.h"
#include "wk_gpio.h"
#include "wk_system.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */

// * 导入头文件
#include "drv_led.h"
#include "drv_usart.h"
#include "drv_key.h"
#include "op_string.h"
#include "sver_regis.h"
#include "sver_mem.h"
#include "sver_comm.h"
#include "td_tick.h"
#include "td_delay.h"
#include "static_list.h"
#include "sver.h"

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
 * @brief main function.
 * @param  none
 * @retval none
 */
int main(void)
{
    /* add user code begin 1 */

    /* add user code end 1 */

    /* system clock config. */
    wk_system_clock_config();

    /* config periph clock. */
    wk_periph_clock_config();

    /* init debug function. */
    wk_debug_config();

    /* nvic config. */
    wk_nvic_config();

    /* timebase config. */
    wk_timebase_init();

    /* init usart1 function. */
    wk_usart1_init();

    /* init spi1 function. */
    wk_spi1_init();

    /* init i2c1 function. */
    wk_i2c1_init();

    /* init tmr7 function. */
    wk_tmr7_init();

    /* init gpio function. */
    wk_gpio_config();

    /* add user code begin 2 */
    drv_led_init();
    drv_key_gpio_init();
    // * 默认拉高电平
    gpio_bits_set(GPIOD, GPIO_PINS_13);

    /*************************************************
     * 服务注册
     ************************************************/
    task_list_init();
    task_insert_head(1, led_blink_task);
    task_insert_head(2, check_key_server);
    task_insert_head(3, free_mem_size_server);
    task_insert_head(4, debug_comm_task);
    task_insert_tail(6, led_red_blink_server);

    print_START();

    /************************************************
     * 启动时间基准定时器
     ************************************************/
    td_timer_tick_init();
    // 延迟函数基准
    // td_delay_timer_init();

    /* add user code end 2 */

    while (1)
    {
        /* add user code begin 3 */

        task_list_run();

        // wk_delay_ms(10);

        /* add user code end 3 */
    }
}

/* add user code begin 4 */

/* add user code end 4 */
