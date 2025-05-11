
#ifndef _JSON_H_
#define _JSON_H_

#include "typedef.h"

float json_get_float(const char *json, const char *key);

int json_get_int(const char *json, const char *key);

int json_get_float_value(const char *json, const char *key, float *value);
// 返回值：0=成功, -1=键不存在, -2=值格式错误, -3=缓冲区不足
int json_get_string(const char *json, const char *key, char *value_buf, int buf_size);

#endif
