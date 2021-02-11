/*******************************************************************************/
/*  File :          MotorDriver.h                                              */
/*  Functionality:  To control motor speed and distance/direction              */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MOTORDRIVER_H
#define	MOTORDRIVER_H

  

/* Variable definitions*/
#define OneCm 39.24        //Number of encoder pulses to move one centermetre
#define OneCell 706.32     //Number of encoder pulses to move one cell

/* Function definitions*/
int MotorDriver(float speed, int direction);



 

#endif	/* MOTORDRIVER_H */

