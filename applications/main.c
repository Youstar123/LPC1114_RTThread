/*
 * Copyright (c) 2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-05     jg1uaa       the first version
 */

#include <rtthread.h>
#include "led.h"
#include "key.h"
extern volatile uint8_t key_flag;
int main(int argc, char **argv)
{
    LED_Init();
    KEY_IRQ_Init();

    while (1) {

        LED_Toggle();
        rt_thread_mdelay(1000);
    }

}
