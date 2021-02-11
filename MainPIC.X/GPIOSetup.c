/*******************************************************************************/
/*  File :          GPIOSetup.c                                                  */
/*  Functionality:                                                             */
/*  Author:         Paul Mathison                                              */
/*  Created on:     27/02/2019                                                 */
/*  Version:        v1.0                                                       */
/*******************************************************************************/


#include"GPIOSetup.h"
#include <p30Fxxxx.h> //picks the correct device automatically
/******************* Sets pin to either input or output**********************/

void GPIOSetup()
{
  /***Set switch pin to input***/
    TRISDbits.TRISD2=1;
  /***Set LED2 pin to output***/
    TRISDbits.TRISD1=0;
  /***Set LED3 pin to output***/
    TRISDbits.TRISD3 =0;
  /***Set LED4 pin to output***/
    TRISEbits.TRISE0 = 0;
  /***Set PWM 1L output***/    
    TRISEbits.TRISE1 = 0;
  /***Set PWM 1H output***/ 
    TRISEbits.TRISE2 = 0;
  /***Set PWM 2L output***/  
    TRISEbits.TRISE3 = 0;
  /***Set PWM 2H output***/  
    TRISEbits.TRISE4 = 0;
  /**Set RB1 to output for motor drive direction*/
    TRISBbits.TRISB1 = 0;
  /**Set RB2 to output for motor drive direction*/
    TRISBbits.TRISB2 = 0;

    
    
    
}
