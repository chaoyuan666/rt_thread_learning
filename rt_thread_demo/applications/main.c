/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-04     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <rtdevice.h>
#include <drv_common.h>

#include "led.h"
#include "key.h"
#include "task.h"
#include "keyboard.h"
#include "ultra.h"


int main(void)
{
//    key_beep_irq_test();
//    task_static_test();
//    task_test();
//    key();
//    keyboard();
//
//    rt_thread_startup(rt_thread_create("tkey", key, RT_NULL, 1024, 20, 10));
//    rt_thread_startup(rt_thread_create("tpwm", pwm, RT_NULL, 1024, 20, 10));
//
//    int count = 1;
//
//    while (count++)
//    {
//        LOG_D("Hello RT-Thread!");
//        rt_thread_mdelay(1000);
//    }

    /*
    rt_thread_startup(rt_thread_create("keyboard", keyboard, RT_NULL, 1024, 20, 10));
    rt_thread_mdelay(10000);

    while (1)
    {
        LOG_D("key is %c", buffer_read(keyboard_get_buffer()));
    }
    */

    struct sUltra csb_model = {
            GET_PIN(B, 0),
            GET_PIN(B, 1),
    };
    ultra_init(&csb_model);

    while(1) {
        LOG_D("dst is %d", ultra_measure(&csb_model));
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
