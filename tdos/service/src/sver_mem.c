
#include "sver_mem.h"
#include "static_list.h"
#include "drv_usart.h"

#include "td_tick.h"
#include "td_delay.h"

#define TRIGGER_INTERVAL (100) // 1000ms = 100 * 10ms

typedef enum
{
    IDLE,
    RUNNING,
    WAIT_TRIGGER
} TaskMemState;

static uint16_t run_mem_cnt = 0;
static TaskMemState current_state = IDLE;

void free_mem_size_task(void)
{
    if (current_state == IDLE)
    {
        // * 初次进入空闲状态
        current_state = RUNNING;
        run_mem_cnt = 0;
    }
    else if (current_state == RUNNING)
    {
        // * 展开计数
        run_mem_cnt++;
        if (run_mem_cnt >= TRIGGER_INTERVAL)
        {
            // 计数完成之后触发
            current_state = WAIT_TRIGGER;
        }
    }
    else if (current_state == WAIT_TRIGGER)
    {
        /* 计数完成 执行获取内存大小 */
        uint32_t mem_size = get_free_count();
        debug_printf("mem size : %d\n", mem_size);
        uint32_t tick = td_rt_tick.get_tick();
        debug_printf("tick : %ul\n", tick);
        current_state = IDLE;
        run_mem_cnt = 0;
    }
}

typedef struct sver_mem_context
{
    long enter_cnt;
    TaskMemState current_state;
} sver_mem_context;

sver_mem_context sver_mem_ctx = {
    .current_state = IDLE,
    .enter_cnt = 0};

void free_mem_size_server(void)
{
    const long tick = td_rt_tick.get_tick();
    uint32_t elapsed;
    switch (sver_mem_ctx.current_state)
    {
    case IDLE:
        sver_mem_ctx.current_state = RUNNING;
        sver_mem_ctx.enter_cnt = tick;
        break;

    case RUNNING:
        elapsed = TIME_DIFF(tick, sver_mem_ctx.enter_cnt);
        if (elapsed >= TRIGGER_INTERVAL)
        {
            sver_mem_ctx.enter_cnt = tick;
            sver_mem_ctx.current_state = WAIT_TRIGGER;
        }
        break;

    case WAIT_TRIGGER:
        sver_mem_ctx.enter_cnt = tick;
        sver_mem_ctx.current_state = IDLE;
        /* 计数完成 执行获取内存大小 */
        uint32_t mem_size = get_free_count();
        debug_printf("mem size : %d\n", mem_size);
        long tick = delay_tick_get();
        debug_printf("tick : %d\n", tick);
        break;
    default:
        sver_mem_ctx.enter_cnt = tick;
        sver_mem_ctx.current_state = IDLE;
        break;
    }
}
