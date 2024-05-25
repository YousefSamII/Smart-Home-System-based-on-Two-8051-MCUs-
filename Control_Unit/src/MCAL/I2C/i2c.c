 /*	____________________________________________________________________________
  |																			    |
  | Module: I2C																    |
  |																			    |
  | File Name: i2c.c														    |
  |																			    |
  | Description: Source file for the I2C 8051 driver				  		    |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/

#include "i2c.h"
#include "../GPIO/gpio.h"
#include "../DELAY/delay.h"

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function to send the start bit
 */
void I2C_start(void){

    GPIO_writePin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID, LOGIC_LOW);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 -> Function to send the stop bit
 */
void I2C_stop(void){

    GPIO_writePin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID, LOGIC_LOW);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID, LOGIC_HIGH);

}

/*
 * Description :
 -> Function to send a single byte over I2C
 */
void I2C_writeByte(uint8 data8){

    uint8 i;
    for (i = 0; i < 8; i++)
    {
        GPIO_writePin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID, ((data8 & 0x80)>>7));
        GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
        GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_LOW);
        data8 <<= 1;
    }
    while(GPIO_readPin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID) != LOGIC_LOW);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 -> Function to read a single byte without acknowledgment
 */
uint8 I2C_readByte(void){

    uint8 i , receivedData = 0x00;
    for ( i = 0; i < 8; i++)
    {
        GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
        receivedData <<= 1;
        receivedData |= GPIO_readPin(I2C_SDA_PORT_ID, I2C_SDA_PIN_ID);
        GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_LOW);
    }
    
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(I2C_SCL_PORT_ID, I2C_SCL_PIN_ID, LOGIC_LOW);
    
    return receivedData;
}