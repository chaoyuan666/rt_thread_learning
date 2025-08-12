/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-12     chao       the first version
 */
#ifndef APPLICATIONS_MODULE_BUFFER_BUFFER_H_
#define APPLICATIONS_MODULE_BUFFER_BUFFER_H_
#include <rtthread.h>

#define BUFF_LEN 8

struct sbuffer{
    char buff[BUFF_LEN];
    int head;
    int tail;
    struct rt_semaphore sLock;
    struct rt_semaphore sFree;
    struct rt_semaphore sFull;
};


void buffer_init(struct sbuffer *b);
void buffer_write(struct sbuffer *b, char c);
char buffer_read(struct sbuffer *b);

#endif /* APPLICATIONS_MODULE_BUFFER_BUFFER_H_ */
