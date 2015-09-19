/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0
#define PU_ENABLE 1
#define PU_DISABLE 0


void initSwitch1(){
    //TODO: Initialize switch 1
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = PU_ENABLE;
}