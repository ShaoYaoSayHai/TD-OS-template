
#include "sver.h"
#include "td_tick.h"
#include "drv_key.h"
#include <limits.h> // 添加LONG_MAX定义
#include "drv_usart.h"

// 状态机时间参数定义
#define DEBOUNCE_TICKS 2                 // 20ms（2 * 10ms）
#define LONG_PRESS_TICKS 100             // 1000ms
#define MAX_SAFE_INTERVAL (LONG_MAX / 2) // 最大安全间隔

// 时间差计算宏（防溢出）
#define TIME_DIFF_NOW(start) \
    ((td_rt_tick.get_tick() >= (start)) ? (td_rt_tick.get_tick() - (start)) : (LONG_MAX - (start) + td_rt_tick.get_tick() + 1))

typedef struct
{
    KeyState status;
    long press_start;    // 改为long类型
    long debounce_start; // 分离防抖计时
} KeyContext;

KeyContext key_ctx = {IDLE, 0, 0};

void check_key_server(void)
{
    const long current_ticks = td_rt_tick.get_tick();
    long elapsed;

    static KeyState prev_state = IDLE; // 用于调试状态跳转
    // 仅调试状态切换时打印 调试时候打开
    if (prev_state != key_ctx.status)
    {
        debug_printf("State changed: %d -> %d\n", prev_state, key_ctx.status);
        prev_state = key_ctx.status;
    }

    switch (key_ctx.status)
    {
    case IDLE:
        if (is_key_pressed())
        {
            key_ctx.debounce_start = current_ticks;
            key_ctx.status = DEBOUNCE;
        }
        break;

    case DEBOUNCE:
        elapsed = TIME_DIFF_NOW(key_ctx.debounce_start);

        // 添加安全间隔检查
        if (elapsed > MAX_SAFE_INTERVAL)
        {
            key_ctx.status = IDLE;
            break;
        }

        if (elapsed >= DEBOUNCE_TICKS)
        {
            if (is_key_pressed())
            {
                key_ctx.press_start = current_ticks;
                key_ctx.status = PRESSED;
            }
            else
            {
                key_ctx.status = IDLE;
            }
        }
        break;

    case PRESSED:
    {
        long safe_interval = (LONG_PRESS_TICKS > MAX_SAFE_INTERVAL) ? MAX_SAFE_INTERVAL : LONG_PRESS_TICKS;
        elapsed = TIME_DIFF_NOW(key_ctx.press_start);

        if (!is_key_pressed())
        {
            on_short_hold_func();
            key_ctx.status = IDLE;
        }
        else if (elapsed >= safe_interval)
        { // 安全边界限制
            on_long_hold_func();
            key_ctx.status = LONG_CHECK;
            key_ctx.press_start = current_ticks; // 重置计时
        }
        break;
    }

    case LONG_CHECK:
        if (TIME_DIFF_NOW(key_ctx.press_start) > MAX_SAFE_INTERVAL)
        {
            key_ctx.status = IDLE;
        }
        else if (!is_key_pressed())
        {
            key_ctx.status = IDLE;
        }
        break;
    }
}