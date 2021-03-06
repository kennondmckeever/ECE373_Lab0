/* 
 * File:   main.c
 * Author: Kennon McKeever
 * Description: lab 0 - see readme
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
} stateType;

stateType state = init;

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    initSwitch1();
    initLEDs();
    initTimer1();
        
    int curr_led = 0; //current LED that is on
    
   
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
                if(SWITCH1 == SWITCH_PRESSED) //0 is pressed because of the internal pull-up
                {
                    state = waitRelease;
                    timer1On();
                    delayMs(10); //debounce. Do this after the timer is started to make the 2s check be accurate
                }
                break;
            case waitRelease:
                if(SWITCH1 == SWITCH_NOT_PRESSED) //1 means released in this case because of the pull-up
                {
                    state = inc; //for debugging purposes
                    
                    state = IFS0bits.T1IF ? dec : inc; //check the timer
                    IFS0bits.T1IF = 0; //reset the flag
                    timer1Off();
                    delayMs(10); //debounce after timer is checked
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

