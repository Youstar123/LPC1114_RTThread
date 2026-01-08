//
// Created by zero on 26-1-8.
//

#ifndef RTTHREAD_TIMER32_H
#define RTTHREAD_TIMER32_H

#include "rtthread.h"
#include "LPC11xx.h"

/* The test is either MAT_OUT or CAP_IN. Default is MAT_OUT. */
#define TIMER_MATCH		0

#define EMC0	4
#define EMC1	6
#define EMC2	8
#define EMC3	10

#define MATCH0	(1<<0)
#define MATCH1	(1<<1)
#define MATCH2	(1<<2)
#define MATCH3	(1<<3)

#define TIME_INTERVAL	(SystemCoreClock/100 - 1)
/* depending on the SystemFrequency and SystemAHBFrequency setting,
if SystemFrequency = 60Mhz, SystemAHBFrequency = 1/4 SystemAHBFrequency,
10mSec = 150.000-1 counts */

void delay32Ms(uint8_t timer_num, uint32_t delayInMs);

#if CONFIG_TIMER32_DEFAULT_TIMER32_0_IRQHANDLER==1
extern volatile uint32_t timer32_0_counter;
#endif

#if CONFIG_TIMER32_DEFAULT_TIMER32_1_IRQHANDLER==1
extern volatile uint32_t timer32_1_counter;
#endif

void enable_timer32(uint8_t timer_num);
void disable_timer32(uint8_t timer_num);
void reset_timer32(uint8_t timer_num);
void init_timer32(uint8_t timer_num, uint32_t timerInterval);
void init_timer32PWM(uint8_t timer_num, uint32_t period, uint8_t match_enable);
void setMatch_timer32PWM (uint8_t timer_num, uint8_t match_nr, uint32_t value);
#endif //RTTHREAD_TIMER32_H
