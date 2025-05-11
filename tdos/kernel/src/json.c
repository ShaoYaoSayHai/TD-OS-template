

#include "string.h"
#include "stdlib.h"
#include "json.h"

float json_get_float(const char *json, const char *key)
{
    char key_pattern[32];
    sprintf(key_pattern, "\"%s\":", key); // 生成需要匹配的键名

    // 查找键名位置
    char *key_pos = strstr(json, key_pattern);
    if (!key_pos)
    {
        return -1.0f; // 键名不存在
    }

    // 定位到冒号后的起始位置
    char *value_start = key_pos + strlen(key_pattern);
    while (*value_start == ' ' || *value_start == '\"')
    {
        value_start++;
    }

    // 提取数值字符串
    char value_str[16];
    int i = 0;
    while (*value_start && *value_start != ',' && *value_start != '}' && i < 15)
    {
        value_str[i++] = *value_start++;
    }
    value_str[i] = '\0';
    return atof(value_str);
}

int json_get_int(const char *json, const char *key)
{
    char key_pattern[32];
    sprintf(key_pattern, "\"%s\":", key); // 生成需要匹配的键名

    // 查找键名位置
    char *key_pos = strstr(json, key_pattern);
    if (!key_pos)
    {
        return -1.0f; // 键名不存在
    }

    // 定位到冒号后的起始位置
    char *value_start = key_pos + strlen(key_pattern);
    while (*value_start == ' ' || *value_start == '\"')
    {
        value_start++;
    }

    // 提取数值字符串
    char value_str[16];
    int i = 0;
    while (*value_start && *value_start != ',' && *value_start != '}' && i < 15)
    {
        value_str[i++] = *value_start++;
    }
    value_str[i] = '\0';
    return atoi(value_str);
}

int json_get_float_value(const char *json, const char *key, float *value)
{
    char key_pattern[32];
    sprintf(key_pattern, "\"%s\":", key); // 生成需要匹配的键名

    // 查找键名位置
    char *key_pos = strstr(json, key_pattern);
    if (!key_pos)
    {
        return key_undefined; // 键名不存在
    }

    // 定位到冒号后的起始位置
    char *value_start = key_pos + strlen(key_pattern);
    while (*value_start == ' ' || *value_start == '\"')
    {
        value_start++;
    }

    // 提取数值字符串
    char value_str[16];
    int i = 0;
    while (*value_start && *value_start != ',' && *value_start != '}' && i < 15)
    {
        value_str[i++] = *value_start++;
    }
    value_str[i] = '\0';
    *value = atof(value_str);
    return find_value_ok;
}

// 返回值：0=成功, -1=键不存在, -2=值格式错误, -3=缓冲区不足
int json_get_string(const char *json, const char *key, char *value_buf, int buf_size)
{
    char key_pattern[64];
    sprintf(key_pattern, "\"%s\":", key);

    // 查找键名位置
    char *key_pos = strstr(json, key_pattern);
    if (!key_pos)
        return -1; // 键不存在

    // 定位值起始位置（跳过冒号后的空格和引号）
    char *value_start = key_pos + strlen(key_pattern);
    while (*value_start == ' ')
        value_start++; // 仅跳过空格
    if (*value_start != '\"')
        return -2; // 值必须以引号开头

    value_start++; // 跳过起始引号

    // 提取字符串内容（处理转义字符）
    int i = 0;
    while (*value_start && *value_start != '\"' && i < buf_size - 1)
    {
        if (*value_start == '\\')
        { // 处理转义字符
            value_start++;
            switch (*value_start)
            {
            case '\"':
                value_buf[i++] = '\"';
                break;
            case '\\':
                value_buf[i++] = '\\';
                break;
            case '/':
                value_buf[i++] = '/';
                break;
            case 'n':
                value_buf[i++] = '\n';
                break;
            default:
                break; // 忽略其他转义
            }
        }
        else
        {
            value_buf[i++] = *value_start;
        }
        value_start++;
    }

    if (i >= buf_size - 1)
        return -3; // 缓冲区不足
    if (*value_start != '\"')
        return -2; // 未找到结束引号

    value_buf[i] = '\0'; // 终止符
    return 0;            // 成功
}