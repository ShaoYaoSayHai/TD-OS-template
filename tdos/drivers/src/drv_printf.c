/**
 * @file drv_printf.c
 * @author ZhangHW
 * @brief  线程安全的printf
 * @version 0.1
 * @date 2025-05-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdarg.h>
#include "stdio.h"
#include "stdint.h"

// #include "drivers_config.h"
#include "drivers_config.h"

#if USE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#include "drv_usart.h"

// 定义互斥量（需在初始化时创建）
SemaphoreHandle_t xPrintfMutex = NULL;
#endif

void debug_printf(const char *format, ...)
{
    static char buffer[128]; // 静态缓冲区避免动态内存分配
    va_list args;
    va_start(args, format);
#if USE_RTOS
    // 获取互斥量，超时100ms防止死锁
    if (xSemaphoreTake(xPrintfMutex, pdMS_TO_TICKS(100)) == pdTRUE)
    {
        vsnprintf(buffer, sizeof(buffer), format, args);                   // 格式化字符串
        usart_write_block(DEBUG_USART, (uint8_t *)buffer, strlen(buffer)); // 发送到串口
        xSemaphoreGive(xPrintfMutex);                                      // 释放互斥量
    }
#else
    // * 未使用多线程
    vsnprintf(buffer, sizeof(buffer), format, args);                   // 格式化字符串
    usart_write_block(DEBUG_USART, (uint8_t *)buffer, strlen(buffer)); // 发送到串口
#endif
    va_end(args);
}

void print_START(void)
{
    // 逐行打印字符组合
    debug_printf("\n");
    debug_printf("**********************************************\n");
    debug_printf("  _____   _______   _____   _____   _______ \n");   // S T A R T 顶部结构[1,4](@ref)
    debug_printf(" / ____| |__   __| |  _  | |  _  | |__   __|\n");   // 竖线支撑结构
    debug_printf("| (___      | |    | |_| | | |_| |    | |   \n");   // 中间横梁
    debug_printf(" \\___ \\     | |    |  _  | |  _  |    | |   \n"); // 下部结构
    debug_printf(" ____) |    | |    | | | | | | | |    | |   \n");   // 字母连接部分
    debug_printf("|_____/     |_|    |_| |_| |_| |_|    |_|   \n");   // 底部收尾
    debug_printf("**********************************************\n");
}
