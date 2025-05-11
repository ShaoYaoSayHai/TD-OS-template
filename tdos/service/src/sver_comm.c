
#include "sver_comm.h"
#include "drv_usart.h"

extern usart_recv_type_t usart_debug_recv_info; // 接收数据句柄

void debug_comm_task(void)
{
    if (usart_debug_recv_info.flag == true)
    {
        debug_printf("port recv ok\n");
        usart_write_block(DEBUG_USART, usart_debug_recv_info.buffer, usart_debug_recv_info.size);
        reset_usart_recv(&usart_debug_recv_info);
    }
}