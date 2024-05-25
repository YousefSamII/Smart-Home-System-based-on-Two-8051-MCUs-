  /*____________________________________________________________________________
  |																			                                        |
  | Module: External EEPROM													                            |
  |																			                                        |
  | File Name: ext_eeprom.h													                            |
  |																			                                        |
  | Description: Header file for the External EEPROM Memory				              |
  |																			                                        |
  | Author: Youssif Hossam													                            |
  |_____________________________________________________________________________|
*/
#include "../../LIB/std_types.h"


/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function to write a byte on the EEPROM
 */
void EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/*
 * Description :
 -> Function to write a multible bytes on the EEPROM
 */
void EEPROM_writeMultibleBytes(uint16 u16addr, uint8 *u8data, uint8 size);

/*
 * Description :
 -> Function to read a byte from the EEPROM
 */
uint8 EEPROM_readByte(uint16 u16addr);

/*
 * Description :
 -> Function to read a multiple byte from the EEPROM
 */
void EEPROM_readMultibleBytes(uint16 u16addr, uint8 *u8data, uint8 size);



