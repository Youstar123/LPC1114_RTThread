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
#include "oled.h"

extern volatile uint8_t key_flag;
int main(int argc, char **argv)
{
    LED_Init();
    KEY_IRQ_Init();
    OLED_Init();       // 初始化OLED显示屏

    /* OLED显示静态字符串 */
    OLED_ShowString(1, 1, "T:000-000-0");	//格式为：T:发送成功计次-发送失败计次-发送标志位
    OLED_ShowString(3, 1, "R:000-000-0");	//格式为：R:接收成功计次-接收失败计次-接收标志位
    while (1) {

        LED_Toggle();
        rt_thread_mdelay(1000);
    }

}
