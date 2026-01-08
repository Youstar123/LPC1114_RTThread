//
// Created by zero on 26-1-8.
//

#ifndef RTTHREAD_TIMER16_H
#define RTTHREAD_TIMER16_H

#include "rtthread.h"
#include "LPC11xx.h"

/* TIMER_CLOCKFREQ是进入定时器预分频器的时钟频率 */
#define TIMER_CLOCKFREQ SystemCoreClock

/* MHZ_PRESCALE是设置预分频器的值，用于将定时器时钟设置为1MHz。
   时钟必须是1MHz的倍数，否则此设置无效。 */
#define MHZ_PRESCALE    (TIMER_CLOCKFREQ/1000000)

/* TIME_INTERVALmS是加载到定时器匹配寄存器的值，用于获得1毫秒的延迟 */
#define TIME_INTERVALmS	1000

/* 测试模式可以是MAT_OUT（匹配输出）或CAP_IN（捕获输入）。默认是MAT_OUT。 */
#define TIMER_MATCH		0

void delayMs(uint8_t timer_num, uint32_t delayInMs);

#define EMC0	4
#define EMC1	6
#define EMC2	8
#define EMC3	10

#define MATCH0	(1<<0)
#define MATCH1	(1<<1)
#define MATCH2	(1<<2)
#define MATCH3	(1<<3)

void TIMER16_0_IRQHandler(void);
void TIMER16_1_IRQHandler(void);

void enable_timer16(uint8_t timer_num);
void disable_timer16(uint8_t timer_num);
void reset_timer16(uint8_t timer_num);
void init_timer16(uint8_t timer_num, uint16_t timerInterval);
void init_timer16PWM(uint8_t timer_num, uint32_t period, uint8_t match_enable, uint8_t cap_enabled);
void setMatch_timer16PWM (uint8_t timer_num, uint8_t match_nr, uint32_t value);

#endif //RTTHREAD_TIMER16_H
