/************************** include files  ***********************************/
#include <p30Fxxxx.h> //picks the correct device automatically

#include "MotorDriver.h"
#include "PID.h"
#include "Serial2.h"
#include "Encoder.h"
#include "PWMFunctions.h"
#include "GPIOSetup.h"

//testing - remove after
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern float speedTarget;    //for PID
extern char buffer; 

/********************** Variable definitions *********************************/

int MotorDriver(float speed, int direction){ 
    char bufferDriver[8];
    /**************************** Set Direction **********************************/
 
    /**** Forward ******/   
    if (direction == 1){
        DriveLatch1 = 1; //PORTEbits.RE1 = 1;
        DriveLatch2 = 0; //PORTEbits.RE2 = 0;
    }   
 
    /***** Reverse *****/   
    if (direction == -1){
        DriveLatch1 = 0; //PORTEbits.RE1 = 0;
        DriveLatch2 = 1; //PORTEbits.RE2 = 1;
    
    }
 
    /**** Stop ******/   
    if (direction == 0){
        DriveLatch1 = 0; //PORTEbits.RE1 = 0;
        DriveLatch2 = 0; //PORTEbits.RE2 = 0;
    }      
    
    speedTarget = speed;
    
    return 0;  
}
