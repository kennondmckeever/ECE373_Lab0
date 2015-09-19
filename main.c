/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    init, waitPress, waitRelease, dec, inc 
    //led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

stateType state = init;

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer1();
    
    
    
    //DEBUGGING TEST CODE -- basically tests that the timer frequency is 2 
    TRISDbits.TRISD13 = 1;
    TRISDbits.TRISD1 = 0;
    CNPUDbits.CNPUD13 = 1;
    initTimer1();
    timer1On();
    while(1){
        if (IFS0bits.T1IF)
        {
            IFS0bits.T1IF = 0;
            LATDbits.LATD1 = !LATDbits.LATD1;
        }
    }
    
   

    
    //current LED that is on
 int curr_led = 0;
   
    while(1){
//        LATDbits.LATD2 = !LATDbits.LATD2;
        switch(state)
        {
            case init:
                curr_led = 0;
                turnOnLED(curr_led);
                turnOffLED(1);
                turnOffLED(2);
                state = waitPress;
                break;
            case waitPress:
                if(PORTDbits.RD6 == 0) //0 is pressed because of the internal pull-up
                {
                    state = waitRelease;
                    timer1On();
                }
                break;
            case waitRelease:
                
                if(PORTDbits.RD6 == 1) //1 means released in this case because of the pull-up
                {
                    state = inc; //for debugging purposes
                    
                    state = IFS0bits.T1IF ? dec : inc;
                    IFS0bits.T1IF = 0; //reset the flag
                    timer1Off();
                }
                break;
            case dec:
                state = waitPress;
                
                turnOffLED(curr_led);
                curr_led = (curr_led - 1);
                if(curr_led < 0) curr_led += 3; //fix to be in range
                turnOnLED(curr_led);
                break;
            case inc:
                state = waitPress;
                
                turnOffLED(curr_led);
                curr_led = (curr_led + 1);
                if (curr_led > 2) curr_led -= 3; //fix to be in range
                turnOnLED(curr_led);
                break;
            default: break;            
        }    
    }
    
    return 0;
}

