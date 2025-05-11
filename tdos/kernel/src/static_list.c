/**
 ******************************************************************************
 * @file    static_list.c
 * @author  ZhangHW
 * @version V1.2.0
 * @date    2024-08-21
 * @brief   基于静态内存管理的链表实现（无动态内存分配）
 * @note    适用于STM32全系列MCU，通过预分配内存池避免内存碎片[1]
 ******************************************************************************
 */
#include "static_list.h"

/* 链表节点结构体（静态内存管理） */
// #define MAX_TASKS 20 // 最大节点数（根据SRAM大小调整）
// typedef struct
// {
//     uint8_t task_id; // 数据域（可自定义数据类型）
//     void (*task_run)(void);
//     int8_t next;    // 下一节点索引（-1表示结尾）
//     uint16_t magic; // 魔数校验（0xAA55）
// } StaticListNode;

StaticListNode task_pool[MAX_TASKS]; // 静态内存池
int8_t free_head = 0;                // 空闲链表头索引
int8_t used_head = -1;               // 使用链表头索引

/**
 * @brief 初始化任务链表
 * @note 构建空闲链表并设置魔数校验
 */
void task_list_init(void)
{
    for (int i = 0; i < MAX_TASKS - 1; i++)
    {
        task_pool[i].next = i + 1;    // 构建空闲链表
        task_pool[i].magic = 0xAA55;  // 设置魔数校验标志
        task_pool[i].task_run = NULL; // 初始化函数指针
    }
    task_pool[MAX_TASKS - 1].next = -1;
    free_head = 0;
    used_head = -1;
}

// * 返回使用了的链表头索引
int8_t get_used_head(void)
{
    return used_head;
}

/**
 * @brief 分配任务节点
 * @return 成功返回节点索引，失败返回-1
 * @note 包含魔数校验和中断保护
 */
int8_t task_alloc(void)
{
    if (free_head == -1)
        return -1;

    // 关中断保护临界区（适用于RTOS）
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    int8_t new_node = free_head;
    free_head = task_pool[free_head].next;

    // 校验魔数防止内存越界
    if (task_pool[new_node].magic != 0xAA55)
    {
        __set_PRIMASK(primask);
        return -1;
    }

    // 初始化新节点
    task_pool[new_node].task_run = NULL;
    __set_PRIMASK(primask);
    return new_node;
}

/**
 * @brief 释放任务节点
 * @param node_idx 要释放的节点索引
 * @note 包含链表解除链接和内存回收
 */
void task_free(int8_t node_idx)
{
    if (node_idx < 0 || node_idx >= MAX_TASKS)
        return;

    // 查找前驱节点
    int8_t prev = -1, current = used_head;
    while (current != -1 && current != node_idx)
    {
        prev = current;
        current = task_pool[current].next;
    }

    // 解除链表链接
    if (prev == -1)
    {
        used_head = task_pool[node_idx].next; // 删除头节点
    }
    else
    {
        task_pool[prev].next = task_pool[node_idx].next;
    }

    // 回收节点到空闲链
    task_pool[node_idx].next = free_head;
    free_head = node_idx;

    // 清除敏感数据
    task_pool[node_idx].task_id = 0;
    task_pool[node_idx].task_run = NULL;
}

/**
 * @brief 头部插入任务节点
 * @param task_id 任务ID
 * @param task_func 任务函数指针
 * @return 成功返回节点索引，失败返回-1
 * @note 适用于高优先级任务插入
 */
int8_t task_insert_head(uint8_t task_id, void (*task_func)(void))
{
    int8_t new_node = task_alloc();
    if (new_node == -1)
        return -1;

    task_pool[new_node].task_id = task_id;
    task_pool[new_node].task_run = task_func;

    // 更新链表头
    task_pool[new_node].next = used_head;
    used_head = new_node;
    return new_node;
}

/**
 * @brief 尾部插入任务节点
 * @param task_id 任务ID
 * @param task_func 任务函数指针
 * @return 成功返回节点索引，失败返回-1
 * @note 适用于顺序执行任务队列
 */
int8_t task_insert_tail(uint8_t task_id, void (*task_func)(void))
{
    int8_t new_node = task_alloc();
    if (new_node == -1)
        return -1;

    task_pool[new_node].task_id = task_id;
    task_pool[new_node].task_run = task_func;
    task_pool[new_node].next = -1;

    if (used_head == -1)
    {
        used_head = new_node;
    }
    else
    {
        // 遍历到链表尾部
        int8_t current = used_head;
        while (task_pool[current].next != -1)
        {
            current = task_pool[current].next;
        }
        task_pool[current].next = new_node;
    }
    return new_node;
}

/**
 * @brief 验证链表完整性
 * @note 通过魔数校验检测内存损坏
 */
bool validate_list(void)
{
    int8_t current = used_head;
    while (current != -1)
    {
        if (task_pool[current].magic != 0xAA55)
        {
            return false; // 内存校验失败
        }
        current = task_pool[current].next;
    }
    return true;
}

/**
 * @brief 释放所有任务节点到空闲链表
 * @note 线程安全操作，清除任务数据并回收所有节点
 */
void task_free_all(void)
{
    uint32_t primask = __get_PRIMASK();
    __disable_irq(); // 关中断保护临界区

    int8_t current = used_head;
    while (current != -1)
    {
        int8_t next = task_pool[current].next; // 保存下一节点索引

        /* 清除敏感数据 */
        task_pool[current].task_id = 0;
        task_pool[current].task_run = NULL;

        /* 回收节点到空闲链头部 */
        task_pool[current].next = free_head;
        free_head = current;

        current = next; // 移动到下一节点
    }
    used_head = -1; // 清空使用链表头

    __set_PRIMASK(primask); // 恢复中断状态
}

/**
 * @brief 获取剩余内存大小
 *        空闲链表长度监控，预防内存耗尽
 * @return uint32_t 已经使用的大小
 */
uint32_t get_free_count(void)
{
    uint32_t count = 0;
    int8_t current = free_head;
    while (current != -1)
    {
        count++;
        current = task_pool[current].next;
    }
    return count;
}

/**
 * @brief 执行链表中的函数运行
 */
void task_list_run(void)
{
    int8_t current = get_used_head();
    while (current != -1)
    {
        if (task_pool[current].task_run)
        {
            task_pool[current].task_run();
        }
        current = task_pool[current].next;
    }
}