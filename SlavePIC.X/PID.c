/*******************************************************************************/
/*  File :          PID.c                                                      */
/*  Functionality:  PID velocity controller function                           */
/*  Author:         Lecture notes                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/

/******************************************
* PID velocity controller function
* ===================
* Returns a floating point valued drive
* Expects to receive a floating point argument as the desired velocity
******************************************/
#include "PID.h"
#include "Encoder.h"    //Just added 04/3/19
#include "GPIOSetup.h"
/*For testing */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Serial2.h"
#include <p30Fxxxx.h> //picks the correct device automatically
#include "Timer1Functions.h"

float  PID_controller (float desired_velocity ){
    
    float actual_velocity=0; // Measured velocity ( note: this is signed int )
    
    float Proportional_Component; // }
    float Derivative_Component; // } Separate components of controller
    
    float drive ; // Output of the controller
    float error; // Difference between desired and actual velocities
    
    static float error_1 = 0; // Previous difference between desired and actual velocities
    float error_deriv; // change in difference between desired and actual velocities
    float Kp, Kd; // PID Gains

    // Set gains (THESE MUST BE TUNED!)
    Kp = 20.0; //30 Proportional gain for left //40 for right 
    Kd = 4.0;//2.9;//0.5; // Derivative gain is value divide by 100, i.e. Kd=.2
    
    // Calculate difference between desired and actual velocities, i.e., calculate ERROR
    actual_velocity = getEncoderVelocity(); // re introduced 4/3/19from next weeks lecture
    error = desired_velocity - actual_velocity; // cast an int to a float
    
    // Calculate Proportional component
    Proportional_Component = error * Kp;
    
    // Calculate Derivative component
    error_deriv = error - error_1; // current error ? previous error
    Derivative_Component = error_deriv * Kd;
    
    error_1 = error; // update previous error for next control iteration
    drive = (Proportional_Component + Derivative_Component) ; // sum the components
    
    return drive; // return drive from function
}
