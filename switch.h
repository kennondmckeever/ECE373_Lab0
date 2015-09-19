/* 
 * File:   switch.h
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#ifndef SWITCH_H
#define	SWITCH_H

#define SWITCH_PRESSED 0 //it gets pulled down to GND when pressed
#define SWITCH_NOT_PRESSED 1 //1 becaue it has pullups

#define SWITCH1 PORTDbits.RD6 //this is the switch we're using
void initSwitches();

#endif	/* SWITCH_H */

