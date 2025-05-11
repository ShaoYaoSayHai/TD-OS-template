
#include "sver.h"
#include "drv_led.h"
#include "td_tick.h"

#define DEBOUNCE_TICKS 2 // 20ms (2 * 10ms)
#define BLINK_TICKS 50   // 500ms (50 * 10ms)
#define MAX_BLINKS 5

typedef struct
{
    LedBlinkState status;
    uint32_t enter_time; // 状态进入时间戳
    uint8_t blink_count;
    BOOL is_blinking;
} LedContext;

static LedContext led_ctx = {LED_IDLE, 0, 0, FALSE};

void start_led_blink(void)
{
    if (!led_ctx.is_blinking)
    {
        led_ctx.status = LED_DEBOUNCE;
        led_ctx.enter_time = td_rt_tick.get_tick();
        led_ctx.blink_count = 0;
        led_ctx.is_blinking = TRUE;
    }
}

/**
 * @brief LED闪烁任务 状态机模式
 */
void led_blink_task(void)
{
    const uint32_t current_tick = td_rt_tick.get_tick();
    uint32_t elapsed;

    switch (led_ctx.status)
    {
    case LED_DEBOUNCE:
        elapsed = TIME_DIFF(current_tick, led_ctx.enter_time);
        if (elapsed >= DEBOUNCE_TICKS)
        {
            led_ctx.status = LED_BLINK_ON;
            led_ctx.enter_time = current_tick;
            led_set_state(TRUE);
        }
        break;

    case LED_BLINK_ON:
        elapsed = TIME_DIFF(current_tick, led_ctx.enter_time);
        if (elapsed >= BLINK_TICKS)
        {
            led_ctx.status = LED_BLINK_OFF;
            led_ctx.enter_time = current_tick;
            led_set_state(FALSE);

            if (++led_ctx.blink_count >= MAX_BLINKS)
            {
                led_ctx.status = LED_IDLE;
                led_ctx.is_blinking = FALSE;
            }
        }
        break;

    case LED_BLINK_OFF:
        elapsed = TIME_DIFF(current_tick, led_ctx.enter_time);
        if (elapsed >= BLINK_TICKS)
        {
            led_ctx.status = LED_BLINK_ON;
            led_ctx.enter_time = current_tick;
            led_set_state(TRUE);
        }
        break;

    default:
        led_ctx.status = LED_IDLE;
        led_ctx.is_blinking = FALSE;
        break;
    }
}