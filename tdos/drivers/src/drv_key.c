/**
 * @file drv_key.c
 * @author ZhangHW
 * @brief  非阻塞形式的key驱动
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "drv_key.h"
#include "drv_usart.h"
#include "drv_led.h"

extern void start_led_blink(void) ; 

// * 用状态机显示按键短按长按检测
// 初始化按键状态为空闲
static KeyState key_status = IDLE;
// 初始化计时器为0，用于记录时间（单位时间调用周期10ms）
static uint16_t key_timer = 0;

#define LONG_PRESS_TIME 100 // 1s

BOOL is_key_pressed(void)
{
    return (gpio_input_data_bit_read(GPIOA, GPIO_PINS_0) != RESET) ? TRUE : FALSE;
}

// * gpio引脚初始化
void drv_key_gpio_init(void)
{
    gpio_init_type gpio_init_struct;

    // * 时钟总线初始化
    // crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    // crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    Periph_GPIOC_Clk_Enable(TRUE);
    Periph_GPIOD_Clk_Enable(TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_13;
    gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_0;
    gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    gpio_init(GPIOA, &gpio_init_struct);

    key_status = IDLE;
}

// * 长时间按下函数
void on_long_hold_func(void)
{
    debug_printf("LONG TIME HOLD\r\n");

    /**************************************
     * 插入长按事件
     *************************************/
    start_led_blink();
}

// * 短时间按下函数
void on_short_hold_func(void)
{
    static uint8_t short_press_cnt = 0;
    short_press_cnt++;
    if (short_press_cnt % 2 == 1)
    {
        gpio_bits_reset(GPIOD, GPIO_PINS_14);
    }
    else if (short_press_cnt % 2 == 0)
    {
        gpio_bits_set(GPIOD, GPIO_PINS_14);
    }
}

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
void check_key_task(void)
{
    BOOL key_down = is_key_pressed();  // 获取当前是否被物理按下
    static KeyState prev_state = IDLE; // 用于调试状态跳转

    // 仅调试状态切换时打印 调试时候打开
    if (prev_state != key_status)
    {
        debug_printf("State changed: %d -> %d\n", prev_state, key_status);
        prev_state = key_status;
    }

    // 用连贯的if-else重写状态机
    if (key_status == IDLE)
    {
        if (key_down)
        {
            key_status = DEBOUNCE; // 初步检测到按下，进入消抖阶段
            key_timer = 0;         // 复位计时器
        }
        // 其余时间保持空闲状态
    }
    else if (key_status == DEBOUNCE)
    {
        if (key_down)
        {
            if (++key_timer >= 2) // 持续20ms消抖
            {
                key_status = PRESSED; // 确认为有效按下
                key_timer = 0;        // 复位长按计时器
            }
        }
        else
        {
            key_status = IDLE; // 已经释放则恢复初始状态
            key_timer = 0;
        }
    }
    else if (key_status == PRESSED)
    {
        if (key_down)
        {
            if (++key_timer >= LONG_PRESS_TIME) // 持续按压计数
            {
                on_long_hold_func();     // 触发长按事件
                key_status = LONG_CHECK; // 进入长按锁定状态
            }
        }
        else // 中途释放
        {
            on_short_hold_func(); // 触发短按事件
            key_status = IDLE;    // 回归初始状态
        }
    }
    else if (key_status == LONG_CHECK)
    {
        if (!key_down)
        {
            key_status = IDLE; // 长按后的释放动作
        }
    }
    else // 容错处理（非法状态时复位）
    {
        key_status = IDLE;
    }
}
