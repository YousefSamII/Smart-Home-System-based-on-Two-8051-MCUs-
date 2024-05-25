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

#ifndef HAL_RELAY1_H_
#define HAL_RELAY1_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                               		Definitions                        		      |
 |______________________________________________________________________________|
 */

#define RELAY1_PORT_ID			  PORT2_ID
#define RELAY1_PIN_ID			    PIN5_ID

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */


/*
 * Description :
 -> Function to enable the Relay.
 */
void RELAY1_toggle();


#endif /* HAL_BUZZER_BUZZER_H_ */
