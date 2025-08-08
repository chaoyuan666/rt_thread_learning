/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-03     chao       the first version
 */
#include "key.h"
#include <rtdevice.h>
#include <drv_common.h>

#define KEY_PIN     GET_PIN(A, 0)
#define BEEP_PIN    GET_PIN(A, 5)


void key_beep_test(void)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BEEP_PIN, PIN_LOW);

    while (1)
    {
        if (rt_pin_read(KEY_PIN) == PIN_LOW)
        {
            rt_pin_write(BEEP_PIN, PIN_LOW);
        }else
        {
            rt_pin_write(BEEP_PIN, PIN_HIGH);
        }
    }
}

void cb()
{
    rt_pin_write(BEEP_PIN, PIN_LOW);
    while(rt_pin_read(KEY_PIN) == PIN_LOW);
    rt_pin_write(BEEP_PIN, PIN_HIGH);
}

void key_beep_irq_test(void)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BEEP_PIN, PIN_HIGH);

    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, cb, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);
}

void key_beep(void)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BEEP_PIN, PIN_HIGH);

    while (1)
    {
        if (rt_pin_read(KEY_PIN) == PIN_LOW)
        {
            rt_pin_write(BEEP_PIN, PIN_LOW);
        }
        else {
            rt_pin_write(BEEP_PIN, PIN_HIGH);
        }
    }
}

rt_sem_t semkey;
static void callback()
{
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_DISABLE);
    rt_sem_release(semkey);
}

extern uint8_t width;

void key(void)
{
    semkey = rt_sem_create("skey", 0, RT_IPC_FLAG_PRIO);
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BEEP_PIN, PIN_HIGH);

    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, callback, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);
    while (1)
    {
        rt_sem_take(semkey, RT_WAITING_FOREVER);
        rt_thread_mdelay(20);  /* Eliminate the effect of button press jitter */
        if (rt_pin_read(KEY_PIN) == PIN_LOW) {
            rt_pin_write(BEEP_PIN, !rt_pin_read(BEEP_PIN));
            width++;
        }
        rt_thread_mdelay(300); /* Eliminate the effect of button release jitter */
        rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);
    }
}

