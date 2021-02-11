/*******************************************************************************/
/*  File :          GPIOSetup.h                                                */
/*  Functionality:  Setup input output ports                                   */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/

#define Debug 1

#ifndef GPIOSETUP_H
#define	GPIOSETUP_H

  

void GPIOSetup();

/*****Define Switch ports ******************************/
#define S3Latch LATDbits.LATD2
#define S3Port  PORTDbits.RD2


/******Define LED2 port ********************************/
#define LED2Latch LATDbits.LATD1
#define LED2Port  PORTDbits.RD1

/******Define LED3 port ********************************/
#define LED3Latch LATDbits.LATD3
#define LED3Port  PORTDbits.RD3

/******Define LED4 port ********************************/
#define LED4Latch LATEbits.LATE0
#define LED4Port  PORTEbits.RD0

/******Define Drive direction pin 1 ****************************/
// FireCracker settings
//#define DriveLatch1 LATEbits.LATE1
//#define DrivePort1 PORTEbits.RE1


#define DriveLatch2 LATBbits.LATB1
#define DrivePort2 PORTBbits.RB1


/******Define Drive direction pin 2*******************/
// FireCracker settings
//#define DriveLatch2 LATEbits.LATE2
//#define DrivePort2  PORTEbits.RE2


#define DriveLatch1 LATBbits.LATB2
#define DrivePort1  PORTBbits.RB2


#endif	/* GPIOSETUP_H */
