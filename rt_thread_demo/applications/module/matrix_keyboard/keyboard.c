/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     chao       the first version
 */
#include "keyboard.h"
#include <rtdevice.h>
#include <drv_common.h>

#define DBG_TAG "kBoard"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


#define ROW_NUM  4  /* Keyboard row definition */
#define COL_NUM  4  /* Keyboard column definition */

struct keyboard{
    rt_sem_t sem;
    char key[ROW_NUM][COL_NUM]; /* Keyboard key definition */
    rt_base_t row_pin[ROW_NUM]; /* Row pin definition */
    rt_base_t col_pin[COL_NUM]; /* Column pin definition */
    int row;
    int col;
    struct sbuffer buff;
};

#define KEYBOARD_VALUE  {  \
    {'1', '2', '3', 'A'},  \
    {'4', '5', '6', 'B'},  \
    {'7', '8', '9', 'C'},  \
    {'*', '0', '#', 'D'},  \
}

#define ROW_PIN_CONFIG  {GET_PIN(E, 12), GET_PIN(E, 13),  \
        GET_PIN(E, 14), GET_PIN(E, 15)     \
}

#define COL_PIN_CONFIG  {GET_PIN(E, 4), GET_PIN(E, 5),  \
        GET_PIN(E, 6), GET_PIN(E, 7)     \
}

struct keyboard kBoard = {
        .key = KEYBOARD_VALUE,
        .col_pin = COL_PIN_CONFIG,
        .row_pin = ROW_PIN_CONFIG
};


void keyboard_cb(void *r)
{
    kBoard.row = *(int *)r;
    rt_sem_release(kBoard.sem);
}

void keyboard(void)
{
    int i;
    buffer_init(&kBoard.buff);
    kBoard.sem = rt_sem_create("ksem", 0, RT_IPC_FLAG_PRIO);
    for (i = 0; i < COL_NUM; ++i) {
        rt_pin_mode(kBoard.col_pin[i], PIN_MODE_OUTPUT);
        rt_pin_write(kBoard.col_pin[i], PIN_HIGH);
    }
    for (i = 0; i < ROW_NUM; ++i) {
        rt_pin_mode(kBoard.row_pin[i], PIN_MODE_INPUT_PULLDOWN);
        rt_pin_attach_irq(kBoard.row_pin[i], PIN_IRQ_MODE_RISING, keyboard_cb, (void *)&i);
        rt_pin_irq_enable(kBoard.row_pin[i], PIN_IRQ_ENABLE);
    }
    while (1)
    {
        rt_sem_take(kBoard.sem, RT_WAITING_FOREVER);
        rt_thread_mdelay(30);
        if (rt_pin_read(kBoard.row_pin[kBoard.row]) == PIN_LOW) {
            LOG_D("DouDong!");
            continue;
        }

        rt_pin_mode(kBoard.row_pin[kBoard.row], PIN_MODE_OUTPUT);
        rt_pin_write(kBoard.row_pin[kBoard.row], PIN_HIGH);
        for (i = 0; i < COL_NUM; ++i) {
            rt_pin_mode(kBoard.col_pin[i], PIN_MODE_INPUT_PULLDOWN);
            if (rt_pin_read(kBoard.col_pin[i]) == PIN_LOW) {
                kBoard.col = i;
                LOG_D("row = %d, col = %d, value = %d", kBoard.row, kBoard.col, kBoard.key[kBoard.row][kBoard.col]);
                buffer_write(&kBoard.buff, kBoard.key[kBoard.row][kBoard.col]);
                break;
            }
        }

        for (i = 0; i < COL_NUM; ++i) {
            rt_pin_mode(kBoard.col_pin[i], PIN_MODE_OUTPUT);
            rt_pin_write(kBoard.col_pin[i], PIN_HIGH);
        }
        rt_pin_mode(kBoard.row_pin[kBoard.row], PIN_MODE_INPUT_PULLDOWN);
    }
};

struct sbuffer* keyboard_get_buffer(void)
{
    return &kBoard.buff;
}
