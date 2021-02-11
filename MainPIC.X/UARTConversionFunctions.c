/*
 * File to hold the UART functions for PIC to PIC communications in the mouse.
 * 
 * data_to_UART() takes a float of speed and a character of direction and distance. It returns an array of 7 chars.
 * 
 * UART_to_data() takes an array of 7 chars (like the output of the previous function), and two addresses. It returns
 *  a float for speed directly, and places a char for direction and distance at the two addresses respectively.
 * 
 */

#include <p30Fxxxx.h>


/*Send data to UART*/
void data_to_UART(float speed_data, char dir_data, char dist_data){
    
    extern char commSend[7];//define the output array
    
    int tens = (speed_data/10); //devolve float to int representatives
    int units = ((speed_data - 10*tens)/1);
    int tenths = ((speed_data - 10*tens - units)/0.1);
    int hundredths = ((speed_data - 10*tens - units - 0.1*tenths)/0.01);
    int thousandths = ((speed_data - 10*tens - units - 0.1*tenths - 0.01*hundredths)/0.001);
    
    commSend[0] = '0' + tens; //assign first 5 chars as the float values
    commSend[1] = '0' + units; //'0' + (0-9) will give the char of 0-9 not the char of value 0-9
    commSend[2] = '0' + tenths;
    commSend[3] = '0' + hundredths;
    commSend[4] = '0' + thousandths;
    commSend[5] = dir_data; //directly add direction and distance identifying char
    commSend[6] = dist_data;
    
    U1TXREG = commSend[0];  //kickstart send process
    
}

/*Receive data from UART*/
float UART_to_data(char *CommArray, char *dir_dest, char *dist_dest){
    
    return 0;
}
