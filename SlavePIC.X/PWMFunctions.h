/*******************************************************************************/
/*  File :          PWMFunction.h                                              */
/*  Functionality:  Provide a PWM drive signal                                 */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/



#ifndef PWMFUNCTIONS_H
#define	PWMFUNCTIONS_H

void __attribute__((interrupt, auto_psv)) _PWMInterrupt(void); //PWM interrupt
void setupPWM();                                              //Setup PWM

#endif	/* PWMFUNCTIONS_H */

