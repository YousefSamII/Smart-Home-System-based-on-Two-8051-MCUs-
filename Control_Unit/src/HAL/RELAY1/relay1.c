/*	____________________________________________________________________________
  |																			                                        |
  | Module: Relay															                                  |
  |																			                                        |
  | File Name: relay.c														                              |
  |																			                                        |
  | Description: Source file for the relay								                      |
  |																			                                        |
  | Author: 													                                          |
  |_____________________________________________________________________________|
*/

#include "relay1.h"
#include "../../MCAL/GPIO/gpio.h"
/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */


/*
 * Description :
 -> Function to enable the Buzzer.
 */
void RELAY1_toggle(){

	GPIO_writePin(RELAY1_PORT_ID , RELAY1_PIN_ID , !GPIO_readPin(RELAY1_PORT_ID , RELAY1_PIN_ID));

}

