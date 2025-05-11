
#include "op_string.h"

/**
 *
// char str1[] = "test-equal\n";
// char str2[] = "test-equal\n";
// BOOL status = string_equals_enhanced(str1, str2);
// debug_printf("is equal : %s\n", ((status == TRUE) ? "TRUE" : "FALSE"));
 *
 */

/**
 * @brief 判断字符串是否相等
 *
 * @param str1 字符串1
 * @param str2 字符串2
 * @return int TRUE(1)
 *             FALSE(0)
 */
bool string_equals_enhanced(const char *str1, const char *str2)
{
    // 开发阶段启用断言[1,5](@ref)
    assert(str1 != NULL && str2 != NULL);

    // 逐字符比对
    while (*str1 || *str2)
    { // 任一未结束则继续
        if (*str1 != *str2)
            return false;
        if (*str1 == '\0')
            break; // 同步结束验证
        str1++;
        str2++;
    }
    return true;
}

