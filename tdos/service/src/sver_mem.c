
#include "sver_mem.h"
#include "static_list.h"
#include "drv_usart.h"

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
        current_state = IDLE;
        run_mem_cnt = 0;
    }
}