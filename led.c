/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define LED_ON 1
#define LED_OFF 0

#define OUTPUT 0
#define INPUT 1

void initLEDs(){
    
    //initialize all three LEDs
    //TRISD &= ; //could use something like this to set all of the pins to inputs or outputs at once
    TRISDbits.TRISD0 = OUTPUT; //0 for output
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD0 = LED_OFF;
    LATDbits.LATD1 = LED_OFF;
    LATDbits.LATD2 = LED_OFF;    
}

void turnOnLED(int led)
{
    LED_Set(led, LED_ON);
}

void turnOffLED(int led)
{
    LED_Set(led, LED_OFF);
}

void LED_Set(int led, int OnOrOff)
{
    if(led == 0)
        LATDbits.LATD0 = OnOrOff;
    else if(led == 1)
        LATDbits.LATD1 = OnOrOff;
    else if (led == 2)
        LATDbits.LATD2 = OnOrOff;
}
