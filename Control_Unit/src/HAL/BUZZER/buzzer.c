/*	____________________________________________________________________________
  |																			                                        |
  | Module: BUZZER															                                |
  |																			                                        |
  | File Name: buzzer.c														                              |
  |																			                                        |
  | Description: Source file for the buzzer								                      |
  |																			                                        |
  | Author: 													                                          |
  |_____________________________________________________________________________|
*/

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"
/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */


/*
 * Description :
 -> Function to enable the Buzzer.
 */
void BUZZER_on(){

	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_HIGH);

}

/*
 * Description :
 -> Function to disable the Buzzer.
 */
void BUZZER_off(){

	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);

}
