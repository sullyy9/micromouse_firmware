/*******************************************************************************/
/*  File :          Encoder.c                                                  */
/*  Functionality:                                                             */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/


#include "Encoder.h"
#include "MotorDriver.h"
#include <p30Fxxxx.h> //picks the correct device automatically
#include "MotorDriver.h"

/*   temporary for sending data while debugging*/
//testing - remove after
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*Globals: used in this file only*/
int overrun = 0;
int underrun = 0;

char bufferEncoder [8];

void init_QEI(void){
    // configure analogue pins as digital channels
    ADPCFGbits.PCFG5 = 1; // QEB on pin 7 shared with AN5
    ADPCFGbits.PCFG4 = 1; // QEA on pin 6 shared with AN4
    // note: IND pin is not connected on firecracker board
    
    // Configure QEI module
    QEICONbits.QEISIDL = 1; // Discontinue operation when in idle mode
    QEICONbits.QEIM = 0b111; // x4 edge gain and reset POSCNT when == MAXCNT
    QEICONbits.SWPAB = 0; // Do not swap the polarity of phase comparison
    QEICONbits.PCDOUT = 0; // Disable counter direction pin (normal I/O operation)
    QEICONbits.POSRES = 0; // index pulse does not reset POSCNT
    QEICONbits.TQCS = 0; // internal clock source (Tcy)
    DFLTCONbits.QEOUT = 0; // disable digital filters
    
    // set initial counter value and maximum range
    MAXCNT = 0xffff; // set the highest possible time out
    POSCNT = 0x7fff; // set POSCNT into middle of range
    
    // Configure Interrupt controller
    IFS2bits.QEIIF = 0; // clear interrupt flag
    IEC2bits.QEIIE = 1; // enable QEI interrupt
    IPC10bits.QEIIP = 5; // set QEI interrupt priority
}

void __attribute__((interrupt, auto_psv)) _QEIInterrupt(void){
    
    IFS2bits.QEIIF = 0; // clear interrupt flag


    if(POSCNT<32768){    
        
        overrun++; //xx_xx++; // over-run condition caused interrupt
        POSCNT = 32768;
    }
    
    else{
        
        underrun--;//xx_xx--; // under-run condition caused interrupt
        POSCNT = 32768;
    }
}

float getEncoderVelocity(){
    float Rad_s;
    extern int NewPosCNT; //in timer functions
    extern int OldPosCNT; //in timer functions
        //(2*PI/16) / (4 * 33) 33:1 ratio and 4 x as rising and falling edge
         Rad_s = (((NewPosCNT - OldPosCNT))) *   0.297499304;   //multiply by -1 for left wheel
        //PosCNTDifference = (NewPosCNT - OldPosCNT);

    //get velocity
    //Rad_s = (NewPosCNT - OldPosCNT) * 0.297499304;
    
    return  Rad_s;
}

float getDistance(){
    float Distance;
    
    /****************************************************************************/
    /*   gearbox 33:1 16 pulses per revolution = 528 pulses per revolution      */
    /*   measures on rising and falling edges therfore 4 * 528 = 2112 pulse/mm  */
    /*   circumference = 134.5541 2112/134.5541 =15.6962887 pulses/mm           */
    /*   dividing POSCNT equals 1/15.6962887 = 0.063709                         */
    /*   as the POSCNT  starts half way at 32768 this would equal 2087.627 pulse*/
    /*   therefore 2087.627 must be taken away to leave distance, for the given */
    /*   wheel size                                                             */
    /****************************************************************************/
    
    Distance = ((((POSCNT +(overrun * 65536))* RightWheel)- 2087.55273)) ;  //convert to mm (note *-1 for left wheel))
    
    /*As distance is a positive number if less than 1 convert to positive*/
    if(Distance < 0)
    {
        Distance = Distance* -1;
    }
    return Distance;
    
}
