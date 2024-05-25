/*	____________________________________________________________________________
  |																			                                        |
  | Module: BUZZER															                                |
  |																			                                        |
  | File Name: buzzer.h														                              |
  |																			                                        |
  | Description: Header file for the buzzer								                      |
  |																			                                        |
  | Author: Youssif Hossam													                            |
  |_____________________________________________________________________________|
*/

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		      |
 |______________________________________________________________________________|
 */

#define BUZZER_PORT_ID			PORT2_ID
#define BUZZER_PIN_ID			  PIN1_ID

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function to enable the Buzzer.
 */
void BUZZER_on();

/*
 * Description :
 -> Function to disable the Buzzer.
 */
void BUZZER_off();

#endif /* HAL_BUZZER_BUZZER_H_ */
