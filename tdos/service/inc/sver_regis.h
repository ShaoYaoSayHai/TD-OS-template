/**
 * @file sver_regis.h
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

#ifndef _SVER_REGIS_H_
#define _SVER_REGIS_H_

#include "typedef.h"

typedef void (*regis_func_run)(void);                // while 循环中调用的函数指针
typedef void (*regis_func_set_trigger)(void);     // 触发运行的函数指针
typedef void (*regis_func_set_pointer)(uint8_t *);   // 传递指针
typedef uint8_t (*regis_func_get_value)(uint8_t);    // 获取服务中的某个参数
typedef uint8_t *(*regis_func_get_pointer)(uint8_t); // 获取服务中指针

typedef enum
{

    server_regis_success, // 注册成功
    server_regis_error,   // 注册失败
    server_regis_unfind,  // 没有找到注册的内容
    server_regis_null,    // 注册的指针为空
    server_regis_lose,    // 没有注册无法运行

} ServerRegisState;

typedef struct sver_regis_map
{
    uint8_t regis_id;
    // 注册函数指针
    regis_func_run run;
    regis_func_set_trigger start;
    regis_func_set_pointer set_pointer;

    // 获取服务的参数
    uint8_t (*get_value)(uint8_t);
    // 获取服务的指针
    uint8_t *(*get_pointer)(uint8_t);

} sver_regis_map;

extern sver_regis_map server_register_mapper[1];

// * 注册需要使用的服务
void sver_register_init(void) ; 

#endif
