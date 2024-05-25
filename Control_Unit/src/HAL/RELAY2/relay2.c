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

#include "relay2.h"
#include "../../MCAL/GPIO/gpio.h"
/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */


/*
 * Description :
 -> Function to enable the Buzzer.
 */
void RELAY2_toggle(){

	GPIO_writePin(RELAY2_PORT_ID , RELAY2_PIN_ID , !GPIO_readPin(RELAY2_PORT_ID , RELAY2_PIN_ID));

}
