/* add user code begin Header */
/**
 **************************************************************************
 * @file     at32f403a_407_int.c
 * @brief    main interrupt service routines.
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

/* includes ------------------------------------------------------------------*/
#include "at32f403a_407_int.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
// #include "wk_usart.h"
#include "drv_usart.h"
#include "drivers_config.h"
#include "td_tick.h"
#include "td_delay.h"
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

/* external variables ---------------------------------------------------------*/
/* add user code begin external variables */
extern usart_recv_type_t usart_debug_recv_info; // 接收数据句柄
/* add user code end external variables */

/**
 * @brief  this function handles nmi exception.
 * @param  none
 * @retval none
 */
void NMI_Handler(void)
{
    /* add user code begin NonMaskableInt_IRQ 0 */

    /* add user code end NonMaskableInt_IRQ 0 */

    /* add user code begin NonMaskableInt_IRQ 1 */

    /* add user code end NonMaskableInt_IRQ 1 */
}

/**
 * @brief  this function handles hard fault exception.
 * @param  none
 * @retval none
 */
void HardFault_Handler(void)
{
    /* add user code begin HardFault_IRQ 0 */

    /* add user code end HardFault_IRQ 0 */
    /* go to infinite loop when hard fault exception occurs */
    while (1)
    {
        /* add user code begin W1_HardFault_IRQ 0 */

        /* add user code end W1_HardFault_IRQ 0 */
    }
}

/**
 * @brief  this function handles memory manage exception.
 * @param  none
 * @retval none
 */
void MemManage_Handler(void)
{
    /* add user code begin MemoryManagement_IRQ 0 */

    /* add user code end MemoryManagement_IRQ 0 */
    /* go to infinite loop when memory manage exception occurs */
    while (1)
    {
        /* add user code begin W1_MemoryManagement_IRQ 0 */

        /* add user code end W1_MemoryManagement_IRQ 0 */
    }
}

/**
 * @brief  this function handles bus fault exception.
 * @param  none
 * @retval none
 */
void BusFault_Handler(void)
{
    /* add user code begin BusFault_IRQ 0 */

    /* add user code end BusFault_IRQ 0 */
    /* go to infinite loop when bus fault exception occurs */
    while (1)
    {
        /* add user code begin W1_BusFault_IRQ 0 */

        /* add user code end W1_BusFault_IRQ 0 */
    }
}

/**
 * @brief  this function handles usage fault exception.
 * @param  none
 * @retval none
 */
void UsageFault_Handler(void)
{
    /* add user code begin UsageFault_IRQ 0 */

    /* add user code end UsageFault_IRQ 0 */
    /* go to infinite loop when usage fault exception occurs */
    while (1)
    {
        /* add user code begin W1_UsageFault_IRQ 0 */

        /* add user code end W1_UsageFault_IRQ 0 */
    }
}

/**
 * @brief  this function handles svcall exception.
 * @param  none
 * @retval none
 */
void SVC_Handler(void)
{
    /* add user code begin SVCall_IRQ 0 */

    /* add user code end SVCall_IRQ 0 */
    /* add user code begin SVCall_IRQ 1 */

    /* add user code end SVCall_IRQ 1 */
}

/**
 * @brief  this function handles debug monitor exception.
 * @param  none
 * @retval none
 */
void DebugMon_Handler(void)
{
    /* add user code begin DebugMonitor_IRQ 0 */

    /* add user code end DebugMonitor_IRQ 0 */
    /* add user code begin DebugMonitor_IRQ 1 */

    /* add user code end DebugMonitor_IRQ 1 */
}

/**
 * @brief  this function handles pendsv_handler exception.
 * @param  none
 * @retval none
 */
void PendSV_Handler(void)
{
    /* add user code begin PendSV_IRQ 0 */

    /* add user code end PendSV_IRQ 0 */
    /* add user code begin PendSV_IRQ 1 */

    /* add user code end PendSV_IRQ 1 */
}

/**
 * @brief  this function handles systick handler.
 * @param  none
 * @retval none
 */
void SysTick_Handler(void)
{
    /* add user code begin SysTick_IRQ 0 */

    /* add user code end SysTick_IRQ 0 */

    /* add user code begin SysTick_IRQ 1 */

    /* add user code end SysTick_IRQ 1 */
}

/**
 * @brief  this function handles USART1 handler.
 * @param  none
 * @retval none
 */
void USART1_IRQHandler(void)
{
    /* add user code begin USART1_IRQ 0 */
    if (usart_flag_get(DEBUG_USART, USART_RDBF_FLAG) != RESET)
    {
        usart_debug_recv_info.buffer[usart_debug_recv_info.size++] = usart_data_receive(DEBUG_USART);
        usart_flag_clear(DEBUG_USART, USART_RDBF_FLAG);
    }
    /* add user code end USART1_IRQ 0 */
    /* add user code begin USART1_IRQ 1 */
    if (usart_flag_get(DEBUG_USART, USART_IDLEF_FLAG) != RESET)
    {
        usart_flag_clear(DEBUG_USART, USART_IDLEF_FLAG);
#if USE_RTOS
        BaseType_t pxTaskPriorityWakeUp = pdFALSE; // * 必须默认为FALSE 否则会出现错误

        // 信号量释放
        if (xSemaphoreGiveFromISR(xSemphrBinaryUsartRecvFinished, &pxTaskPriorityWakeUp))
        {
            usart1_recv_info.flag = true;
        }
#else
        // 未使用OS的处理
        usart_debug_recv_info.flag = true;
#endif
    }
    /* add user code end USART1_IRQ 1 */
}

/**
 * @brief  this function handles TMR7 handler.
 * @param  none
 * @retval none
 */
void TMR7_GLOBAL_IRQHandler(void)
{
    /* add user code begin TMR7_GLOBAL_IRQ 0 */

    /*************************************************
     * 时间基准定时器 提供10ms的tick
     *************************************************/
    if (tmr_flag_get(TMR7, TMR_OVF_FLAG) != RESET)
    {
        td_rt_tick.update_tick();
        tmr_flag_clear(TMR7, TMR_OVF_FLAG);
    }

    /* add user code end TMR7_GLOBAL_IRQ 0 */

    /* add user code begin TMR7_GLOBAL_IRQ 1 */

    /* add user code end TMR7_GLOBAL_IRQ 1 */
}

/* add user code begin 1 */
/**
 * @brief  this function handles TMR7 handler.
 * @param  none
 * @retval none
 */
void TMR6_GLOBAL_IRQHandler(void)
{
    /*************************************************
     * 时间基准定时器 提供1ms的tick
     *************************************************/
    if (tmr_flag_get(TMR6, TMR_OVF_FLAG) != RESET)
    {
        // * 添加更新时间片代码
        delay_tick_update(); // 更新延迟
        tmr_flag_clear(TMR6, TMR_OVF_FLAG);
    }
}
/* add user code end 1 */
