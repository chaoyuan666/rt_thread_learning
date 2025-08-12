/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-12     chao       the first version
 */
#include "buffer.h"
#include <rtdevice.h>
#include <drv_common.h>


void buffer_init(struct sbuffer *b)
{
    b->head = 0;
    b->tail = 0;
    rt_sem_init(&b->sLock, "sLock", 1, RT_IPC_FLAG_PRIO);
    rt_sem_init(&b->sFree, "sFree", BUFF_LEN, RT_IPC_FLAG_PRIO);
    rt_sem_init(&b->sFull, "sFull", 0, RT_IPC_FLAG_PRIO);
}

void buffer_write(struct sbuffer *b, char c)
{
    /* get free byte semaphore */
    rt_sem_take(&b->sFree, RT_WAITING_FOREVER);
    /* acquire shared resource lock */
    rt_sem_take(&b->sLock, RT_WAITING_FOREVER);
    b->buff[b->tail] = c;
    b->tail++;
    b->tail = b->tail % BUFF_LEN;
    rt_sem_release(&b->sFull);
    rt_sem_release(&b->sLock);
}


char buffer_read(struct sbuffer *b)
{
    char ret;
    /* get full byte semaphore */
    rt_sem_take(&b->sFull, RT_WAITING_FOREVER);
    /* acquire shared resource lock */
    rt_sem_take(&b->sLock, RT_WAITING_FOREVER);
    ret = b->buff[b->head];
    b->head++;
    b->head = b->head % BUFF_LEN;
    rt_sem_release(&b->sFree);
    rt_sem_release(&b->sLock);

    return ret;
}
