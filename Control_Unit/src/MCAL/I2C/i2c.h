/*	____________________________________________________________________________
  |																			    |
  | Module: I2C																    |
  |																			    |
  | File Name: i2c.h														    |
  |																			    |
  | Description: Header file for the I2C 8051 driver				  		    |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#ifndef I2C_H_
#define I2C_H_

#include "../../LIB/std_types.h"
/*______________________________________________________________________________
 |                       	   Preprocessor Macros                   		   	|
 |______________________________________________________________________________|
 */

#define I2C_SDA_PORT_ID         PORT0_ID
#define I2C_SDA_PIN_ID          PIN0_ID

#define I2C_SCL_PORT_ID         PORT0_ID
#define I2C_SCL_PIN_ID          PIN1_ID


/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function to send the start bit
 */
void I2C_start(void);

/*
 * Description :
 -> Function to send the stop bit
 */
void I2C_stop(void);

/*
 * Description :
 -> Function to send a single byte over I2C
 */
void I2C_writeByte(uint8 data8);

/*
 * Description :
 -> Function to read a single byte without acknowledgment
 */
uint8 I2C_readByte(void);

#endif