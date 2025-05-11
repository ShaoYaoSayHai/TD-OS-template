/**
 * @file drv_usart.h
 * @author ZhangHW
 * @brief  串口驱动
 * @version 0.2
 * @date 2025-05-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _DRV_USART_H_
#define _DRV_USART_H_

#include "wk_usart.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#define RX_BUFFER_SIZE (0xFF)

#define USART_RECV_COM1 (0x01)
#define USART_RECV_COM2 (0x02)

#define DEBUG_USART USART1

typedef struct usart_recv_type_t
{
    uint16_t size;
    uint8_t *buffer;
    uint8_t flag;
} usart_recv_type_t;

// * 重设接收数组信息
void reset_usart_recv(usart_recv_type_t *p);
// * 获取接收数组的指针
usart_recv_type_t *get_usart_recv_info(uint8_t usart_cnt);
// * 获取接收到的数组
uint8_t *get_usart_recv_buffer(usart_recv_type_t *p);

/**
 * 函    数：串口发送一个数组
 * 参    数：data 要发送数组的首地址
 * 参    数：size 要发送数组的长度
 * 返 回 值：无
 */
void usart_write_block(usart_type *usart_x, uint8_t *data, uint16_t size);

// 线程安全的打印
void debug_printf(const char *format, ...);

void print_START( void ) ; 

#endif
