/**
 * @file drv_usart.c
 * @author ZhangHW
 * @brief  串口驱动
 * @version 0.2
 * @date 2025-05-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "drv_usart.h"

uint8_t usart1_rx_buffer[RX_BUFFER_SIZE];

usart_recv_type_t usart_debug_recv_info = {
    .buffer = &usart1_rx_buffer[0],
    .size = 0,
    .flag = false};

// * 重设接收数组信息
void reset_usart_recv(usart_recv_type_t *p)
{
    p->size = 0;
    p->flag = false;
    memset(usart1_rx_buffer, 0, (sizeof(usart1_rx_buffer) / sizeof(usart1_rx_buffer[0])));
}

// * 获取接收数组的指针
usart_recv_type_t *get_usart_recv_info(uint8_t usart_cnt)
{
    if (usart_cnt == USART_RECV_COM1)
    {
        return &usart_debug_recv_info;
    }
    return NULL;
}

uint8_t *get_usart_recv_buffer(usart_recv_type_t *p)
{
    if (p != NULL)
    {
        return p->buffer;
    }
    return NULL;
}

/**
 * 函    数：串口发送一个数组
 * 参    数: usart_x 需要发送数据的串口
 * 参    数：data 要发送数组的首地址
 * 参    数：size 要发送数组的长度
 * 返 回 值：无
 */
void usart_write_block(usart_type *usart_x, uint8_t *data, uint16_t size)
{
    uint16_t i = 0;
    while (usart_flag_get(usart_x, USART_TDBE_FLAG) == RESET)
        ; // 传输数据缓冲区空标志
    usart_flag_clear(usart_x, USART_TDBE_FLAG);
    for (i = 0; i < size; i++)
    {
        usart_data_transmit(usart_x, (uint16_t)data[i]);
        while (usart_flag_get(usart_x, USART_TDC_FLAG) == RESET)
            ;
        usart_flag_clear(usart_x, USART_TDC_FLAG);
    }
}
