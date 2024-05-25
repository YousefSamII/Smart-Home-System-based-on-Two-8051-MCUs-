 /*	____________________________________________________________________________
  |																				|
  | Module: UART																|
  |																				|
  | File Name: uart.c															|
  |																			   	|
  | Description: Source file for the UART AVR driver					        |
  |																				|
  | Author: 													    			|
  |_____________________________________________________________________________|
*/

#include "usart.h"
#include <reg52.h> /* To use the UART Registers */
#include "LIB/common_macros.h" /* To use the macros like SET_BIT */

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Functional responsible for Initialize the UART device by:
    1. Setup the Frame format like number of data bits and number of stop bits.
    2. Enable the UART.
    3. Setup the UART baud rate.
 */
void UART_init(uint8 baudrate)
{
	TMOD = (TMOD & 0x0F) | 0x20; 			/* Timer1 in Mode2.*/
	TH1 = baudrate; 		/* 9600 Baud rate at 11.0592 MHz */
	SCON = 0x50; 			/* Recieve Enabled, Mode 1 --> 8-bit, baudrate is variable */
	TR1 = 1; 				/* Turn ON the timer. */
	TI = 1; 				/* TI: set TI to send first char of UART */
}

/*
 * Description :
 -> Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 txdata)
{
	SBUF = txdata; 			/* Load the data to be transmitted */
	while(TI==0); 			/* Wait till the data is trasmitted */
	TI=0; 					/* Clear the flag for next cycle. */

}

/*
 * Description :
 -> Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	while(RI==0);
	RI = 0;
	return SBUF;
}

/*
 * Description :
 -> Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
