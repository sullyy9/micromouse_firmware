/*******************************************************************************/
/*  File :          PWMFunctions.c                                             */
/*  Functionality:  PID velocity controller function                           */
/*  Author:         Lecture notes                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/

#include "PWMFunctions.h"
#include <p30Fxxxx.h> //picks the correct device automatically



void setupPWM()
{
    
    PTCONbits.PTEN = 0;        //clear PTEN = switch off PWM
    PTCONbits.PTCKPS = 3;      //set PTCKPS = choose prescaler (1,4,16, 64) set to divide by 4
    PTPER = 999;               //set PTPER = set the PWM period 0x3E80  will give a frequency of 250hz
    PWMCON1bits.PEN1H = 0;     //Disable PWM on pin37 make IO only 
    PWMCON1bits.PEN1L = 1;     //set PEN1L = enable PWM 1 lows-side drive
    PWMCON1bits.PEN2L = 0;     //Disable PWM on pin 36 make IO only
    PWMCON1bits.PEN2H = 0;     //Disable PWM on pin 35 make IO only
    PWMCON1bits.PMOD1 = 1;     //set PMOD1 = set PWM1 mode
   
    //PWMCON1bits.PEN1H =1;//set PEN1H = enable PWM 1 high-side drive
    // IEC2bits.PWMIE = 0;
    PTCONbits.PTEN = 1; //set PTEN = finally go
      
}
void __attribute__((interrupt, auto_psv)) _PWMInterrupt(void) 
{  
    
  
 
}
