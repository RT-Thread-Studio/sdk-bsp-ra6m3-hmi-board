/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-11     Joyce        the first version
 */
#ifndef RT_TLSF_H_
#define RT_TLSF_H_

#include "tlsf.h"

void *rt_system_heap_add(void *begin_addr, void *end_addr);
void rt_system_heap_remove(void *heap);

#endif /* RT_TLSF_H_ */
