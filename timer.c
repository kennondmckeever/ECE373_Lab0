/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>

#define ENABLED 1
#define DISABLED 0

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 2 seconds. Enable its interrupt
    T1CONbits.ON = 0; //turn it off. We'll turn it on before we want to use it.
    T1CONbits.TCKPS = 3; //set prescaler to 256
    T1CONbits.TCS = 0; //internal clock selected rather than an external one.
    IEC0bits.T1IE = ENABLED; //enable T1 interrupts
    TMR1 = 0; //clear the register it uses to count
    PR1 = 5208; //period register = ceil(8M / 2 * 20 / 12 /256(prescaler) * 2s - 1)
    
}

void timer1On()
{
    TMR1 = 0; //clear the count register
    IFS0bits.T1IF = 0; //reset the flag, just in case someone forgot to beforehand
    T1CONbits.ON = ENABLED; //turn it on
}

void timer1Off()
{
    T1CONbits.ON = DISABLED; //turn it off
    TMR1 = 0; //clear the counting register just in case
}

//initTimer2(){
//    T2CONbits.ON = DISABLED; //turn it off
//    TMR2 = 0; //clear its counting register
//    T2CONbits.TCKPS = 0;// set the prescaler to 1
//  TODO: finish implementing this function
//}

//delayMs(int delay){
//    //TODO: Using timer 2, create a delay
//    // that is delay amount of ms.
//}