/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     chao       the first version
 */
#ifndef APPLICATIONS_MODULE_MATRIX_KEYBOARD_KEYBOARD_H_
#define APPLICATIONS_MODULE_MATRIX_KEYBOARD_KEYBOARD_H_
#include "buffer.h"

void keyboard(void);
struct sbuffer* keyboard_get_buffer(void);

#endif /* APPLICATIONS_MODULE_MATRIX_KEYBOARD_KEYBOARD_H_ */
