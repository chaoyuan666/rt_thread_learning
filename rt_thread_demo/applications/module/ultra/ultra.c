/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-22     chao       the first version
 */
#include "ultra.h"

#include <rtdevice.h>
#include <drv_common.h>


struct ultTime{
    rt_uint32_t tick;
    rt_uint32_t val;
};

void ultra_get_time(struct ultTime *t)
{
    t->tick = rt_tick_get();
    t->val = SysTick->VAL;
}

void ultra_init(struct sUltra *u)
{
    rt_pin_mode(u->trig, PIN_MODE_OUTPUT);
    rt_pin_write(u->trig, PIN_LOW);
    rt_pin_mode(u->echo, PIN_MODE_INPUT);
}

int ultra_measure(struct sUltra *u)
{
    int dst;
    struct ultTime t0, t1;
//    rt_tick_t t1, t2;
    rt_pin_write(u->trig, PIN_HIGH);
    rt_hw_us_delay(10);
    rt_pin_write(u->trig, PIN_LOW);

    while(rt_pin_read(u->echo) == PIN_LOW);
//    t1 = rt_tick_get_millisecond();
    ultra_get_time(&t0);
    while(rt_pin_read(u->echo) == PIN_HIGH);
//    t2 = rt_tick_get_millisecond();
    ultra_get_time(&t1);

//    dst = (t2 - t1) * 340 / 2;
    dst = 170 * ((t1.tick - t0.tick) * (SysTick->LOAD + 1) + (t0.val - t1.val)) / (SysTick->LOAD + 1);
    return dst;
}
