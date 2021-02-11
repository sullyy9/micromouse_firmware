/******************************************************************************/ 
/* File:                Timer1Functions.h                                     */    
/* Functionality:       Timer1 setup                                          */
/* Author:              Paul Mathison                                         */
/* Created on:          27/02/2019                                            */
/* Version:             v1.0                                                  */
/******************************************************************************/


#include "Timer1Functions.h"
#include "Serial2.h"
#include "GPIOSetup.h"
#include <p30Fxxxx.h> //picks the correct device automatically
#include "MotorDriver.h"
#include "PID.h"
#include "Encoder.h"
#include "MotorDriver.h"
#include "MotorControl.h"


/*for system clock*/
extern unsigned int milliRunTime;
extern unsigned int minRunTime;

extern float speedTarget;

/*Encoder pulses*/
int NewPosCNT;
int OldPosCNT;

void Timer1Setup(){
    
    /********** Configure Timer 1 registers**********/
  
    T1CONbits.TON = 0;    /* Turn off Timer during setup                     */
    TMR1 = 0;             /* Clear TMR1 register, resets the timer to 0      */
    T1CONbits.TCKPS = 1;  /* was 3Prescaler 1=1:8                            */
    PR1 = 20000;//19000;  for 5.9ms//20000;          /*  20000Set the Timer 1 period to 10ms            */
    T1CONbits.TCS = 0;    /* Clear the TCS, chooses internal clock           */
    T1CONbits.TSYNC = 0;  /* TSYNC is ignored when using the internal clock  */
    T1CONbits.TSIDL = 1;  /* stop timer in idle mode                         */
    T1CONbits.TGATE =0;   /* do not gate the timer                           */
    IPC0bits.T1IP = 2;    /* Set interrupt priority                          */
    IEC0bits.T1IE = 1;    /* Enable Timer 1 interrupt                        */
    T1CONbits.TON = 1;    /* Turn on Timer 1                                 */  
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {  
    
    IFS0bits.T1IF = 0; //reset the timer 1 interrupt flag
    
    /*update encode pulses*/
    OldPosCNT = NewPosCNT;
    NewPosCNT = POSCNT;
            
    /*system clock*/
    if(milliRunTime == 60000){
        minRunTime++;
        milliRunTime = 0;
    }
    milliRunTime += 10;
    
    /*Udate the pwm with new value from PID for desired velocity in rad/s*/
    PDC1 = (PID_controller(speedTarget)*SpeedScaler); //12 left 13right
    
}

