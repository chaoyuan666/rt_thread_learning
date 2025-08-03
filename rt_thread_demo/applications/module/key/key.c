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
