/* 
 * UART2 Setup header file
 */

#ifndef UARTSETUP_H
#define	UARTSETUP_H

#include <p30Fxxxx.h>

#define UARTEN U2MODEbits.UARTEN

#define LPBACK U1MODEbits.LPBACK
#define WAKE U1MODEbits.WAKE
#define ABAUD U1MODEbits.ABAUD
#define PDSEL U1MODEbits.PDSEL
#define STSEL U1MODEbits.STSEL
#define URXISEL U1STAbits.URXISEL

#define U1RXIFlag IFS0bits.U1RXIF
#define U1RXIPriority IPC2bits.U1RXIP
#define U1RXIEnable IEC0bits.U1RXIE

#define UTXEN U1STAbits.UTXEN

void UART1Setup(int);

void data_to_UART(float, char, char);

float UART_to_data(char, char, char);

#endif	/* UARTSETUP_H */

