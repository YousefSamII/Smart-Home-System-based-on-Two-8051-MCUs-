/*	____________________________________________________________________________
  |																			                                        |
  | Module: Relay															                                  |
  |																			                                        |
  | File Name: relay.h														                              |
  |																			                                        |
  | Description: Header file for the relay								                      |
  |																			                                        |
  | Author: Youssif Hossam													                            |
  |_____________________________________________________________________________|
*/

#ifndef HAL_RELAY2_H_
#define HAL_RELAY2_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		      |
 |______________________________________________________________________________|
 */

#define RELAY2_PORT_ID			  PORT2_ID
#define RELAY2_PIN_ID			    PIN3_ID

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */


/*
 * Description :
 -> Function to enable the Relay.
 */
void RELAY2_toggle();

#endif /* HAL_BUZZER_BUZZER_H_ */
