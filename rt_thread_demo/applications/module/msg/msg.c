/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-21     chao       the first version
 */

#include <rtthread.h>

#include "msg.h"

#define MSG_QUEUE_LEN 16

rt_mq_t msg_queue = RT_NULL;

void msg_init(){
    if(!msg_queue){
        msg_queue = rt_mq_create("msg", sizeof(struct msg), MSG_QUEUE_LEN, RT_IPC_FLAG_PRIO);
    }
}

void msg_send(struct msg* m){
    rt_mq_send(msg_queue, m, sizeof(struct msg));
}

void msg_rcv(struct msg* m){
    rt_mq_recv(msg_queue, m, sizeof(struct msg), RT_WAITING_FOREVER);
}

