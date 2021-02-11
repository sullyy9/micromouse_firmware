/*******************************************************************************/
/*  File :          Serial.c                                                   */
/*  Functionality:  Setup and includes Serial receive and transmit functions   */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/ 


#include "Serial2.h"
#include "GPIOSetup.h"
#include <p30Fxxxx.h> //picks the correct device automatically
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static char TempReceive[8];  //Temporary buffer to store received data  
//static unsigned char *RXTPtr; //not used
//static char StringLength = 0; //not used
union DataUnion{
   unsigned int TempData;
   char DataReceived[2];
}Data2;

unsigned int Flag = 0;    //Used to indicate Serial data destined for chip1
unsigned int Flag2 = 0;   //Used to indicate Serial data destined for chip2
static unsigned char Temp2[6];
char Temp3[6];
char Data[6];
//extern int Speedrequired; 
//static unsigned char TempChar;  //not used
//static unsigned int PWMValue;   //not used
static unsigned int CharCount = 0;
//static unsigned int CharCount2 = 0;
int TempPDC1 = 0;
//extern textString;


/****************Setup UART registers *************************************/
void UART2config()
{
    
    U2MODEbits.UARTEN = 0; // disable UART during config
    U2BRG = 103;//16;//57600;    //choose appropriate baud rate 
    U2MODEbits.LPBACK = 0; //disable loopback mode  
    U2MODEbits.WAKE = 0;   //do not wake-up on serial activity (don?t care) 
    U2MODEbits.ABAUD = 0;  // no auto-baud detection 
    U2MODEbits.PDSEL = 0;  // 8 databits, no parity 
    U2MODEbits.STSEL = 0;  //one stop bit 
    U2STAbits.URXISEL = 0; //receive interrupt when 1 character arrives 
    IFS1bits.U2RXIF = 0;   //clear rx interrupt flag  
    IPC6bits.U2RXIP =4;    //set receive interrupt priority 
    IEC1bits.U2RXIE = 1;   //enable receive interupts 
    U2MODEbits.UARTEN=1;   //now, enable UART!  
    U2STAbits.UTXEN = 1;   //set UTXEN //and enable transmission (order important) 
    
     
    
}
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
 

  IFS1bits.U2RXIF = 0;           // reset receive interrupt 
  
   
 Data2.TempData =  U2RXREG;            //copy received buffer to temporary variable2
 

   
  if(U2STAbits.OERR == 1)
  { 
       U2STAbits.OERR = 0;
  
  }  

  
  Temp2[CharCount] =  Data2.DataReceived[0]; //copy one character at time to from union to array  
     
             
      
  if ((Data2.DataReceived[0] == '<')&&(Data2.DataReceived[0] != '(')) //Looks for < then reads in data   
  {
            Flag = 1;          //If '<' sets flag and read in data
  }
  
          
  if (Flag)
  {    
            ReadData();        //calls read function to read in data
            Data2.TempData = 0;
            // LED3Latch =!LED3Latch;  //Test indicator remove later
  } 
  else
      Flag =0;                 //if Flag is not equal to 1 makes sure its 0
 
 
  if((Data2.DataReceived[0] == '(')&&(Data2.DataReceived[0] != '>'))
  {
      Flag2 = 1;                //Set Flag data destined for secon chip
      //LED2Latch =!LED2Latch;  //Test indicator remove later
    
  }
  //else
  //    Flag2 = 0;
//  if(Data2.DataReceived[0] == ')' )
//  {
 //     Flag2 =0;
      //LED2Latch =0;
 // }
  if (Flag2)
  {    
             SendStringChip2(Data2.DataReceived);   //send data to chip2
             Data2.TempData = 0;
  } 
  else 
      Flag2 =0;                 //if Flag2 is not equal to 1 makes sure its 0
  

}


void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{
   
       IEC1bits.U2TXIE = 0;
    
}
/*
void TransmitNextCharacter()
{
   static int Next =0;
   
   const char Character[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\n\r'};
   
   
    if (Next < 27)               //Step through characters in array
   {  
 
    U2TXREG =  Character[Next];  //Load UART Transmit register with next character to be sent
    Next++;
   
    LED2Latch =!LED2Latch;      //Turn LED ON/OFF as each character is sent
  
   }
   else
       Next = 0;                //When all the characters have been sent reset the count
   
  
}*/

 void mySendString(char * textString)
 {
    
   static char *TXTPtr;
      
   TXTPtr = &textString[0];
   
     
   while (*TXTPtr != 0)               //Step through characters in array
   {  
       if ((!U2STAbits.UTXBF)&&(*TXTPtr))
       {    
            U2TXREG = *TXTPtr++;  //Load UART Transmit register with next character to be sent
          
           // LED2Latch =!LED2Latch;      //Turn LED ON/OFF as each character is sent
           
       }
      
   }
                     //When all the characters have been sent reset the count
      TXTPtr = &textString[0];
     
 }

 void SendStringChip2(char * textString2)
 {
    
   static char *TXTPtr2;
      
   TXTPtr2 = &textString2[0];
   
     
   while (*TXTPtr2 != 0)               //Step through characters in array
   {  
       if ((!U1STAbits.UTXBF)&&(*TXTPtr2))
       {    
            U1TXREG    = *TXTPtr2++;  //Load UART Transmit register with next character to be sent
          
           // LED2Latch =!LED2Latch;      //Turn LED ON/OFF as each character is sent
           
       }
      
   }
                     //When all the characters have been sent reset the count
      TXTPtr2 = &textString2[0];
     
 }

 void SearchReceiveStringForValue()
 {
    static int j = 0;
    int k = 0;
    //static int FlagData = 0; not used
    char Temp[5];
  //  char Temp3[5];
  char *ptr;
   // int ReceivedPercentageValue=0;
    ptr = &TempReceive[0];
  
      
  //  do
  //  {
        
  //  if(ptr[j] == '<')
  //      FlagData = 1;
   
 //   if(ptr[j] == '>')
 //       FlagData = 0;
   
       
       
    
               if(( ptr[j] >= '0')&&(ptr[j] <= '9' )&&(ptr[j] != '>'))//&&(TempReceive[j] != '>'))
               {
                      Temp[k] =  ptr[j];
                     
                  k++;
                   j++;
                    //ReceivedPercentageValue = ReceivedPercentageValue + TempReceive[j];// + ((TempReceive[j+1])*10)+ ((TempReceive[j+2])*100); 
               }
               else
                   SendERRORmessage();
              
            // j++;
        //k++;  
      // */    
           
       // }
      //j++;
   // }
   //    ptr = '10';//&ReceivedPercentageValue; 
   // TempReceive[0];
     if (j > 1)
    {    
     j = 0;
     k = 0;
    // ptr = Temp;
   // Temp[0] =(char) (ReceivedPercentageValue) ;
  //  sprintf(Temp3, "%c", Temp);
     mySendString(Temp); 
    }  
    
        
   
 }
 void SendERRORmessage()
 {
    mySendString("ERROR!!\r\n"); 
   
 }
 
 
 void SetPWM(char *val)
 {
     
      int clean =0; //unused
     
      TempPDC1 =  atoi(val);///(Temp3);
      PDC1 = TempPDC1*10;
      sprintf(Temp3, "%d", PDC1 );
      mySendString("\n\rPDC1 = "); //works removed after testing
      mySendString(Temp3); 
      mySendString(" \n\r");
      
      /*Clean temp array*/
      for ( clean = 0; clean != 6; clean++)
      {    
            Temp3[CharCount] = 0;
      }
 }
 
 void ReadData()
 {
  
   
        /***********If the first character is '<' then further characters are stored in the array*/
        if((Temp2[CharCount] != '<')&&(Temp2[CharCount] != '>')&&(isdigit(Temp2[CharCount])))
        {    
         Data[CharCount]= Temp2[CharCount]; //Moves number part to another array
         CharCount = CharCount + 1;         //Steps through the array as each character arrives
         
        }
        else 
            { 
                Data[CharCount] = '\0';            //Adds a NULL to convert to a string
                CharCount = 0;                     //Resets the count to zero
            }
     
        
        if (isdigit(Data[CharCount]))              //Checks if a number
        {   
        
        if ((atoi(Data) < 101)&&(atoi(Data)>= 0)) //Checks if a valid number between 0 and 100
        {    
            
           
            //Speedrequired = (atoi(Data));//SetPWM(Data);                             //Sets PWM
           // mySendString("OK: ");
           // mySendString(Data);
            
           // mySendString("% \n\r");
        }
        else
            SendERRORmessage();
        
        for ( CharCount = 0; CharCount != 6; CharCount = CharCount +1) //Clear buffer of data
        {    
          Data[CharCount] = 0; 
        //  Temp2[CharCount] = 0;
          
        }
        CharCount = 0;
        //CharCount2 = 0; 
        Flag =0;
     }
    // else   
      //   SendERRORmessage();
 }

 

 