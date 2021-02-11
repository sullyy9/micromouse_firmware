#include <p30Fxxxx.h> //picks the correct device automatically

#define compiler XC16 
#define Debug 1

#if compiler == XC16
    #pragma config FOS = PRI
    #pragma config FPR = XT_PLL8
    #pragma config FCKSMEN = CSW_FSCM_OFF
    #pragma config WDT = WDT_OFF
    #pragma config BOREN = PBOR_OFF
    #pragma config MCLRE = MCLR_EN
    #pragma config FPWRT = PWRT_64  
    #pragma config LPOL = PWMxL_ACT_HI
    #pragma config HPOL = PWMxH_ACT_LO
    #pragma config PWMPIN = RST_PWMPIN

#elif compiler == C30
    _FOSC(PRI  &  XT_PLL8 & CSW_FSCM_OFF  ); 
    _FWDT(WDT_OFF);    
    _FBORPOR( PBOR_OFF & MCLR_EN & PWRT_64 & PWMxL_ACT_HI &  PWMxH_ACT_LO &RST_PWMPIN); 
   
#endif


/********************** include files *****************************************/
#include "MotorDriver.h"
#include "GPIOSetup.h"
#include "Timer1Functions.h"
#include "Serial2.h"
#include "UARTSetup.h"
#include "PWMFunctions.h"
#include "Encoder.h"
#include "PID.h"
#include "MotorControl.h"
//testing - remove after
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
    
/*global variable*/
float speedUART;   //speed variable for PID
float speed2;
char directionUART;
char distanceUART;
char commSend[7];

unsigned int milliRunTime = 0;  //System clock
unsigned int minRunTime = 0;    //System clock

char buffer [16];

int main(void)
{
    
    /*Setup functions for modules*/ 
    GPIOSetup();    //Setup GPIO pins
    Timer1Setup();  //Setup Timer 1
    UART2config();  //UART2 setup  
    UART1Setup(16);  //UART1 setup 
    setupPWM();     //Setup PWM 
    init_QEI();     //setup encoder
    
    mySendString("Setup complete\n");
    
    while(1){
        
        MotorDriver(speedUART, 1);
            //test
    }
    
  return 0;
}
