/******************************************************************************/ 
/* File:                Timer1Functions.h                                     */    
/* Functionality:       Timer1 setup                                          */
/* Author:              Paul Mathison                                         */
/* Created on:          27/02/2019                                            */
/* Version:             v1.0                                                  */
/******************************************************************************/

/*****Guard against multiply inclusions*****/
#ifndef TIMER1FUNCTIONS_H
#define	TIMER1FUNCTIONS_H
 
/************ Timer variables ***************/
#define SpeedScaler 10.0 

 /********** Sets up Timer1 registers********/
void Timer1Setup();                          


/**********Timer1 interrupt ISR ************/ 
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);  

#endif	/* TIMER1FUNCTIONS_H */

