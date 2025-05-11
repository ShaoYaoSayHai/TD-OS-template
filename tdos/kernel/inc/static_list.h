/**
 ******************************************************************************
 * @file    static_list.h
 * @author  ZhangHW
 * @version V1.2.0
 * @date    2024-08-21
 * @brief   基于静态内存管理的链表实现（无动态内存分配）
 * @note    适用于STM32全系列MCU，通过预分配内存池避免内存碎片[1]
 ******************************************************************************
 */
#ifndef _STATIC_LIST_H_
#define _STATIC_LIST_H_

#include "typedef.h"

#define MAX_TASKS 20 // 最大节点数（根据SRAM大小调整）
typedef struct StaticListNode
{
    uint8_t task_id; // 数据域（可自定义数据类型）
    void (*task_run)(void);
    int8_t next;    // 下一节点索引（-1表示结尾）
    uint16_t magic; // 魔数校验（0xAA55）
} StaticListNode;
extern StaticListNode task_pool[MAX_TASKS];

/**
 * @brief 初始化任务链表
 * @note 构建空闲链表并设置魔数校验
 */
void task_list_init(void);

/**
 * @brief 分配任务节点
 * @return 成功返回节点索引，失败返回-1
 * @note 包含魔数校验和中断保护
 */
int8_t task_alloc(void);

/**
 * @brief 释放任务节点
 * @param node_idx 要释放的节点索引
 * @note 包含链表解除链接和内存回收
 */
void task_free(int8_t node_idx);

/**
 * @brief 头部插入任务节点
 * @param task_id 任务ID
 * @param task_func 任务函数指针
 * @return 成功返回节点索引，失败返回-1
 * @note 适用于高优先级任务插入
 */
int8_t task_insert_head(uint8_t task_id, void (*task_func)(void));

/**
 * @brief 尾部插入任务节点
 * @param task_id 任务ID
 * @param task_func 任务函数指针
 * @return 成功返回节点索引，失败返回-1
 * @note 适用于顺序执行任务队列
 */
int8_t task_insert_tail(uint8_t task_id, void (*task_func)(void));

/**
 * @brief 验证链表完整性
 * @note 通过魔数校验检测内存损坏
 */
bool validate_list(void);

/**
 * @brief 释放所有任务节点到空闲链表
 * @note 线程安全操作，清除任务数据并回收所有节点
 */
void task_free_all(void);

/**
 * @brief 返回使用了的链表头索引
 * @return int8_t used_head
 */
int8_t get_used_head(void);

/**
 * @brief 获取剩余内存大小
 *        空闲链表长度监控，预防内存耗尽
 * @return uint32_t 已经使用的大小
 */
uint32_t get_free_count(void);

/**
 * @brief 执行链表中的函数
 */
void task_list_run(void);

#endif
