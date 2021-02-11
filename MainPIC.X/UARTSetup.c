/*
 *  UART2 Setup file 
 */

#include <p30F4011.h>
#include "UARTSetup.h"

void UART1Setup(int baudrate){
    
    UARTEN = 0;
    U1BRG = baudrate;
    LPBACK = 0;
    WAKE = 0;
    ABAUD = 0;
    PDSEL = 0;
    STSEL = 0;
    URXISEL = 0;
    
    U1RXIFlag = 0;
    U1RXIPriority = 3;
    U1RXIEnable = 1;
    
    /*Transmit interrupt*/
    U1STAbits.UTXISEL = 0;
    
    
    UARTEN = 1;
    UTXEN = 1;
    
}

extern char CommArray[7];
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    U1RXIFlag = 0;
    static char ReceivingArray[7];
    static int count = 0;
    
    ReceivingArray[count] = U1RXREG;//add the new char to the next place in the receiving array
    count++;
    
    if (count == 7){        //if we have received a whole "string"
        count = 0;
        //checking part
        char returned_dir;  //prep destinations
        char returned_dist;
    
    
        //float returned_speed = UART_to_data(ReceivingArray, &returned_dir, &returned_dist );
    }
}

int i=0;    //i=0 denotes no further transmission needed
extern char commSend[7];
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void){
    if(i=0){
        i=1;
    }
    
    if(i<7){
        U1TXREG = commSend[i];
    }
    
    i++;
    /*full transmission complete*/
    if(i=7){
        i=0;
    }
}
