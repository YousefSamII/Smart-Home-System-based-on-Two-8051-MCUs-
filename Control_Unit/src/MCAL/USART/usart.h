 /*______________________________________________________________________________
  |																			    				      |
  | Module: UART															    				      |
  |																			    						|
  | File Name: uart.c														    					|
  |																			    						|
  | Description: Header file for the UART AVR driver					        		   |
  |																			    					 	|
  | Author: 													    					            |
  |______________________________________________________________________________|
*/

#ifndef USART_H_
#define USART_H_

#include "LIB/std_types.h"

#define UART_9600baudRate				0xFD
#define UART_4800baudRate				0xFA
#define UART_2400baudRate				0xF4
#define UART_1200baudRate				0xE8

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Functional responsible for Initialize the UART device by:
    1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
    2. Enable the UART.
    3. Setup the UART baud rate.
 */
void UART_init(uint8 baudrate);

/*
 * Description :
 -> Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 txdata);

/*
 * Description :
 -> Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 -> Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 -> Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
