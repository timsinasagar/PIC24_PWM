

#ifndef  PWM_H
#define  PWM_H

#include <stdbool.h>

#define SET_PIN_17      TRISAbits.TRISA0
#define PIN_17          LATAbits.LATA0 

#define SET_PIN_39      TRISAbits.TRISA1
#define PIN_39          LATAbits.LATA1

#define SET_PIN_58      TRISAbits.TRISA2
#define PIN_58          LATAbits.LATA2 

#define SET_PIN_59      TRISAbits.TRISA3
#define PIN_59          LATAbits.LATA3 


#define HIGH    1
#define LOW     0
#define OUTPUT  0
#define INPUT   1 


#define Fcy 16000000L               //clock frequency 
#define Desired_Frequency 500000L    //500KHz

//update the PWM_PERIOD 
#define PWM_PERIOD 30000

typedef enum {
    BOOM = 1,
    LOAD = 2
} MOTOR;

typedef enum {
    FORWARD = 1, 
    BACKWARD = 2
} DIRECTION;

void Init_Timer3(void);

void Init_OutputCompare1(void);

void Init_OutputCompare2(void);

void Init_PWM(void);

void Init_DirectionPins(void);

void Control_Motor(MOTOR motor, unsigned int dutyCycle, DIRECTION dir);

#endif //PWM_H
