/* 
 * File:   timer.h
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#define FLAG_SET 1
#define FLAG_RESET 0

void initTimer1();
void timer1On();
void timer1Off();
void initTimer2();
void delayMs(int delay);

#endif	/* TIMER_H */

