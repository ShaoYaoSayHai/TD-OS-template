/**
 * @file sver_regis.c
 * @author ZhangHW
 * @brief   设备注册实现
 *          以设备注册的形式 将状态机触发func与状态机保持func注册 只有注册之后的函数可以被调用
 *          以便于进行程序外设的裁剪实现，注册相关的服务，框架流程为 驱动/工具/内核/模块->服务->注册->应用
 * @version 0.1
 * @date 2025-05-11
 *
 * @copyright Copyright (c) 2025
 *
 */

// * 导入头文件
#include "sver_regis.h"
#include "drv_led.h"

sver_regis_map server_register_mapper[1];

// * 注册需要使用的服务
void sver_register_init(void)
{
//    server_register_mapper[0].regis_id = 0;
//    server_register_mapper[0].run = led_blink_task;
//    server_register_mapper[0].start = start_led_blink;
}
