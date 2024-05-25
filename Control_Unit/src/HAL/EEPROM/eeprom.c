  /*____________________________________________________________________________
  |																			    |
  | Module: External EEPROM													    |
  |																			    |
  | File Name: ext_eeprom.h													    |
  |																			    |
  | Description: Source file for the External EEPROM Memory				        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/I2C/i2c.h"

/*
 * Description :
 -> Function to write a byte on the EEPROM
 */
void EEPROM_writeByte(uint16 u16addr, uint8 u8data){

    /* Send the Start Bit */
    I2C_start();

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));

    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));

    /* write byte to eeprom */
    I2C_writeByte(u8data);

    /* Send the Stop Bit */
    I2C_stop();
}

/*
 * Description :
 -> Function to write a multible bytes on the EEPROM
 */
void EEPROM_writeMultibleBytes(uint16 u16addr, uint8 *u8data, uint8 size){

    uint8 i;
    I2C_start();
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    I2C_writeByte((uint8)(u16addr));
    for(i = 0 ; i < size ; i++){
        I2C_writeByte(u8data[i]);
    }
    I2C_stop();

}

/*
 * Description :
 -> Function to read a byte from the EEPROM
 */
uint8 EEPROM_readByte(uint16 u16addr){

    uint8 u8data;

    /* Send the Start Bit */
    I2C_start();

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));

    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));

    /* Send the Repeated Start Bit */
    I2C_start();

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));

    /* Read Byte from Memory without send ACK */
    u8data = I2C_readByte();
    
    /* Send the Stop Bit */
    I2C_stop();

    return u8data;
}

/*
 * Description :
 -> Function to read a multiple byte from the EEPROM
 */
void EEPROM_readMultibleBytes(uint16 u16addr, uint8 *u8data, uint8 size){

    uint8 i;
    for ( i = 0; i < size; i++){
        u8data[i] = EEPROM_readByte(u16addr+i);
    }

}
