/*******************************************************************************/
/*  File :          Serial.h                                                   */
/*  Functionality:  Setup serial for communication                             */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/




#ifndef SERIAL2_H
#define	SERIAL2_H


void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void);
void SearchReceiveStringForValue();
//void TransmitNextCharacter();
void UART2config();
void SendERRORmessage();
void mySendString(char * textString);
void SendStringChip2(char * textString2);
void SetPWM(char *val);
void ReadData();
#endif	/* SERIAL2_H */ 

