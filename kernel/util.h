/**
 * File: kernel/util.h
 * Author: Yan Xue <yanxue@paypal.com>
 * Date: 23/05/2017
 */

#include "../cpu/types.h"

void memory_copy(char *dst, char *src, int n);
void memory_set(u8 *dst, u8 val, u32 len);
void int_to_ascii(int n, char str[]);
void reverse(char *str);
int strlen(char *str);
