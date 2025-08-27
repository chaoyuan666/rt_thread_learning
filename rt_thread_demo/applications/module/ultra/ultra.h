/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-22     chao       the first version
 */
#ifndef APPLICATIONS_MODULE_ULTRA_ULTRA_H_
#define APPLICATIONS_MODULE_ULTRA_ULTRA_H_

#include <rtthread.h>
struct sUltra{
    rt_base_t trig;
    rt_base_t echo;
};

void ultra_init(struct sUltra *u);
int ultra_measure(struct sUltra *u);

#endif /* APPLICATIONS_MODULE_ULTRA_ULTRA_H_ */
