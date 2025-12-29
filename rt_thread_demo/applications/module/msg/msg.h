/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-21     chao       the first version
 */
#ifndef APPLICATIONS_MODULE_MSG_MSG_H_
#define APPLICATIONS_MODULE_MSG_MSG_H_

struct msg {
    uint8_t type;
    uint32_t value;
};

enum MSG_TYPE {
    MSG_TYPE_KEY = 0,
    MSG_TYPE_DIST = 1
};


void msg_init();
void msg_send(struct msg* m);
void msg_rcv(struct msg* m);

#endif /* APPLICATIONS_MODULE_MSG_MSG_H_ */
