#include <p30Fxxxx.h> //picks the correct device automatically

#include "MotorControl.h"
#include "MotorDriver.h"
#include "Encoder.h"
#include "Serial2.h"
#include "GPIOSetup.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern unsigned int milliRunTime;
extern float speed2;
extern char buffer[8];       //for sending out data

/*for debugging
char buffer6[8];
sprintf(buffer6, "%d",distToTarget );//to 5 decimal places
mySendString(buffer6);
mySendString("cruising\t\r\n ");
*/


int controllerTest(int targetDist, char action){
    
    int errFlag;    //Used to store return, but not used yet
    
    switch(action){
        case 'f':
            errFlag = forwardMove(targetDist);
            break;
            
        case 'r':
            /*!!calculate wheel travel dist!!*/
            /*for rotation each wheel needs to travel (angle*pi*radious of axel)/180*/
            if(targetDist > 0){
                errFlag = rotationMove(NINTYTURN, 'r');
            }
            else{
                errFlag = rotationMove(NINTYTURN, 'l');
            }
            break;
    }
    
    return errFlag;
}

int forwardMove(int targetDist){
    float speedMulti;               //multiplier to mouses cruise speed
    int distToTarget;               
    int errFlag;                    
    
    /*ACCELERATE*/
    speedMulti = 0;     
    
    do {                
       /*!!Sensors!!*/
       if(milliRunTime % 50 == 0){
            speedMulti += ACCELRATE;
            
            /*!!Speed to UART!!*/
            data_to_UART(CRUISESPEED*speedMulti, 'f', 0);
               
            errFlag = MotorDriver(CRUISESPEED*speedMulti, 1);
            
            
            if(Debug){
                sprintf(buffer, "%f", speed2);//to 5 decimal places
                mySendString(buffer);
                mySendString(" Accelerating ");
                sprintf(buffer, "%f", getEncoderVelocity());
                mySendString(buffer);
                mySendString("\n");
            }
            
        }
    } while(speedMulti < 1);
    /*END ACCELERATION*/
    
    /*CRUISE*/
    do {
        /*!!Sensors!!*/
        distToTarget = targetDist - (int)getDistance();                              //update distance to target
        if(Debug){
            sprintf(buffer, "%d",   distToTarget);//to 5 decimal places
            mySendString(buffer);
            mySendString(" dist\r\n\n ");
        }
        
    } while(distToTarget > BRAKINGDIST);
    /*END CRUISE*/
    
    /*DECELERATE*/
    speedMulti = 1;
    do {
        /*!!Sensors!!*/
        if(milliRunTime % 50 == 0){
            speedMulti -= DECELRATE;
        }
        if(speedMulti < MINSPEED){
            speedMulti = MINSPEED;
        }
        
        if(Debug){
            sprintf(buffer, "%d",   distToTarget);//to 5 decimal places
            mySendString(buffer);
            mySendString(" decel\r\n\n ");
        }
        
        /*!!Speed to UART!!*/
        data_to_UART(CRUISESPEED*speedMulti, 'f', 0);
        errFlag = MotorDriver(CRUISESPEED*speedMulti, 1);          //pass speed to motor driver
        
        distToTarget = targetDist - (int)getDistance();
    } while(distToTarget > STOPTHRESHOLD);
    
    errFlag = MotorDriver(0, 0);                                            //set speed 0
    /*!!Speed to UART!!*/
    /*END DECELERATION*/
}

/*for rotation each wheel needs to travel (angle*pi*radious of axel)/180*/
int rotationMove(int targetDist, char direction){
    
    float speedMulti;  //multiplier to mouses cruise speed
    float distToTarget;
    int errFlag;
    
    /*ACCELERATE*/
    speedMulti = 0;                                                             //set speed to first increment       
    
    do {                
       /*!!Sensors!!*/
       if(milliRunTime % 50 == 0){                                              //every 50ms
            speedMulti += ACCELRATE;
            if(direction == 'r'){
                errFlag = MotorDriver(TURNSPEED*speedMulti, -1);  //pass speed to motor driver
                /*!!Speed to UART!!*/
            }
            else{
                errFlag = MotorDriver(TURNSPEED*speedMulti, 1);  //pass speed to motor driver
                /*!!Speed to UART!!*/
            }
        }
    } while(speedMulti < 1);
    /*END ACCELERATION*/
    
    /*CRUISE*/
    do {
        /*!!Sensors!!*/
        distToTarget = targetDist - getDistance();                              //update distance to target
    } while(distToTarget > STOPTHRESHOLD);
    /*END CRUISE*/
    
    errFlag = MotorDriver(0, 0);                                            //set speed 0
    /*!!Speed to UART!!*/
    /*END DECELERATION*/
}