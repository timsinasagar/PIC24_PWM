

#include <xc.h>
#include <p24FJ1024GB610.h>
#include "pwm.h"


void __attribute__((__interrupt__, auto_psv)) _T3Interrupt( void )
{
    
    _T3IF = 0;                  //clear the interrupt 
} 

void Init_Timer3(void)
{
    _T3IP   = 4;                // priority level 
    TMR3    = 0;                //clear the timer
    PR3       = PWM_PERIOD - 1;     
    
    T3CON   = 0x8000;           //TON, TSIDL, TGAGE, TCKPS, TCS 
    _T3IF   = 0;                //clear the interrupt flag
    _T3IE   = 1;                //enable T3 interrupt source 
}

void Init_OutputCompare1(void)
{
    //Mapping OC1, function number 13, to RP31. 
    //RP5R register is associated with PIN 48 
    RPOR2bits.RP5R      = 13; 
    OC1CON1bits.OCSIDL  = 0; 
    OC1CON1bits.OCFLT   = 0;
    OC1CON1bits.OCTSEL  = 0b001;    
    OC1CON1bits.OCM     = 0b110; 
    OC1CON2bits.SYNCSEL = 0b01101;  //synchronization with timer3 
    
    OC1R = OC1RS = PWM_PERIOD - 1; 
}

void Init_OutputCompare2(void)
{
    //Mapping OC2, function number 14, to 
    //RP30R register is associated with PIN  39 
    RPOR15bits.RP31R    = 14; 
    OC2CON1bits.OCSIDL  = 0; 
    OC2CON1bits.OCFLT   = 0;
    OC2CON1bits.OCTSEL  = 0b001;    
    OC2CON1bits.OCM     = 0b110; 
    OC2CON2bits.SYNCSEL = 0b01101;  //synchronization with timer3 
    
    OC2R = OC2RS = PWM_PERIOD - 1; 
}

void Init_PWM(void)
{
    Init_DirectionPins();
    Init_OutputCompare1();
    Init_OutputCompare2();

}


void Init_DirectionPins(void)
{
    SET_PIN_17 = OUTPUT;
    PIN_17     = LOW; 
    
    SET_PIN_39  = OUTPUT; 
    PIN_39      = LOW;
    
    SET_PIN_58  = OUTPUT;
    PIN_58      = LOW; 
    
    SET_PIN_59  = OUTPUT;
    PIN_59      = LOW; 
}

void Control_Motor(MOTOR motor,unsigned int dutyCycle, DIRECTION dir)
{
    //BOOM MOTOR 
    if(motor == 1)
    {
        //FORWARD 
        if (dir == 1)
        {
            //move forward 
            OC1R = dutyCycle;
            PIN_39  = LOW; 
            PIN_17  = HIGH;
        }
    
        //BACKWARD
        if (dir == 2)
        {
            //move backward
            OC1R = dutyCycle;
            PIN_17  = LOW; 
            PIN_39  = HIGH;
        }
    }
    
    //LOAD MOTOR 
    if (motor == 2)
    {
        //FORWARD
        if(dir == 1)
        {
            OC2R = dutyCycle;
            PIN_59  = LOW; 
            PIN_58  = HIGH;
        }
        
        //BACKWARD
        if(dir == 2)
        {
            OC2R = dutyCycle;
            PIN_58  = LOW;
            PIN_59  = HIGH; 
        }
    }
}
