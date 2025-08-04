/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-04     chao       the first version
 */
#include "task.h"
#include "led.h"
#include "key.h"
#include <rtdef.h>
#include <rtdevice.h>
#include <drv_common.h>

void task_static_test(void)
{
    rt_thread_t tled, tkey;
    tled = rt_thread_create("LED", led_test, RT_NULL, 1024, 20, 10);
    tkey = rt_thread_create("KEY", key_beep, RT_NULL, 1024, 20, 10);

    rt_thread_startup(tled);
    rt_thread_startup(tkey);
}

struct rt_thread led_thread;
ALIGN(RT_ALIGN_SIZE)
char led_stack[1024];

void task_test(void)
{
    rt_thread_t tkey;
    rt_thread_init(&led_thread, "LED", led_test, RT_NULL, led_stack, 1024, 20, 10);
    tkey = rt_thread_create("KEY", key_beep, RT_NULL, 1024, 20, 10);

    rt_thread_startup(&led_thread);
    rt_thread_startup(tkey);
}
