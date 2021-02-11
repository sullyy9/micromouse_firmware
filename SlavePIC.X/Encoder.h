/*******************************************************************************/
/*  File :          Encoder.h                                                  */
/*  Functionality:  Set up encoder                                             */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/


// This is a guard condition so that contents of this file are not included more than once.  
#ifndef ENCODER_H
#define	ENCODER_H
#define LeftWheel 0.063709 //(42.83mm diameter) //1/(2112/PI*D) 
#define RightWheel 0.063709
void init_QEI(void);
float getEncoderVelocity();
float getDistance();
void __attribute__((interrupt, auto_psv)) _QEIInterrupt(void);

#endif	/*ENCODER_H */



