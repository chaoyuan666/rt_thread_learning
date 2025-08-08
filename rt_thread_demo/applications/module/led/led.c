/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-03     chao       the first version
 */
#include "led.h"
#include <rtdevice.h>
#include <drv_common.h>

#define LED1_PIN    GET_PIN(D, 8)

extern uint8_t stop_flag;

void led_test(void)
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        if (stop_flag == 1) {
            rt_thread_suspend(rt_thread_self());
            rt_schedule();
        }
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}


rt_sem_t sem_pwm;

void pwm(void)
{
    sem_pwm = rt_sem_create("pwm", 0, RT_IPC_FLAG_PRIO);
    uint8_t width = 0;
    uint8_t cycle = 10;
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_sem_take(sem_pwm, RT_WAITING_FOREVER);
        for (width = 0; width < cycle; ++width) {
            for (int i = 0; i < 5; ++i) {
                rt_pin_write(LED1_PIN, PIN_HIGH);
                rt_thread_mdelay(width);
                rt_pin_write(LED1_PIN, PIN_LOW);
                rt_thread_mdelay(cycle-width);
            }
        }
        for (width = cycle; width > 0; --width) {
            for (int i = 0; i < 5; ++i) {
                rt_pin_write(LED1_PIN, PIN_HIGH);
                rt_thread_mdelay(width);
                rt_pin_write(LED1_PIN, PIN_LOW);
                rt_thread_mdelay(cycle-width);
            }
        }
    }
}

