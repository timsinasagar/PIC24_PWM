
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "xc.h"
#include "pwm.h"

int main ( void )
{
    Init_PWM();         //PWM Initialization

    while ( 1 )
    {
        //control command
        //30000 >> 1 gives 50% duty cycle 
        Control_Motor(BOOM, 30000 >> 1, BACKWARD);
        Control_Motor(LOAD, 30000 >> 1, BACKWARD);
        
    }
}

