/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>

#define ENABLED 1
#define DISABLED 0

#define T1PS_256 3
#define T2PS_1 0

#define SET 1
#define RESET 0

#define INTERNAL_CLOCK 0

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 2 seconds. Enable its interrupt
    T1CONbits.ON = DISABLED; //turn it off. We'll turn it on before we want to use it.
    T1CONbits.TCKPS = T1PS_256; //set pre-scaler to 256
    T1CONbits.TCS = INTERNAL_CLOCK; //internal clock selected rather than an external one.
    IEC0bits.T1IE = ENABLED; //enable T1 interrupts
    TMR1 = 0; //clear the register it uses to count
    PR1 = 4882; //period register = ceil(625k /256(pre-scaler) * 2s - 1)
}

void timer1On()
{
    TMR1 = 0; //clear the count register
    IFS0bits.T1IF = RESET; //reset the flag, just in case someone forgot to beforehand
    T1CONbits.ON = ENABLED; //turn it on
}

void timer1Off()
{
    T1CONbits.ON = DISABLED; //turn it off
    IFS0bits.T1IF = RESET; //reset the flag for other people
    TMR1 = 0; //clear the counting register just in case
}

initTimer2(){
    T2CONbits.ON = DISABLED; //turn it off
    TMR2 = 0; //clear its counting register
    T2CONbits.TCKPS = INTERNAL_CLOCK;// set the pre-scaler to 1
    T2CONbits.TCS = T2PS_1;
    IFS0bits.T2IF = RESET;
    PR2 = 6666; //clcok is 8MHZ * 20 / 12 / 2 / 1 * 1ms - 1 = 6665.667
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is 1 ms.
    
    //reset flag, set the timer, etc.
    TMR2 = 0;
    IFS0bits.T2IF = RESET;
    T2CONbits.ON = ENABLED;
    
    //cycle through this delay milliseconds. This makes a timer that can be delayed up to 2 million seconds
    for( ; delay > 0; --delay)
    {
        while(IFS0bits.T2IF == RESET);
        IFS0bits.T2IF = RESET;
    }
    
    T2CONbits.ON = DISABLED;
    TMR2= 0; //reset its register for next time
}