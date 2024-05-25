/*	______________________________________________________________________________
   |																			  |
   | APP: Control ECU Application												  |
   |																			  |
   | File Name: APP.h															  |
   |																			  |
   | Description: Source file for the Control ECU Application					  |
   |																			  |
   | Author: 														  		      |
   |______________________________________________________________________________|
 */

#include "LIB/std_types.h"
#include "MCAL/USART/usart.h"
#include "MCAL/GPIO/gpio.h"
#include "MCAL/I2C/i2c.h"
#include "HAL/BUZZER/buzzer.h"
#include "HAL/EEPROM/eeprom.h"
#include "HAL/SERVO/servomotor.h"
#include "HAL/LCD/lcd.h"
#include "HAL/RELAY1/relay1.h"
#include "HAL/RELAY2/relay2.h"
#include "MCAL/DELAY/delay.h"
#include "MCAL/TIMER0/timer0.h"
#include "REG52.h"
#include "commands.h"


/*______________________________________________________________________________
 |                       		  Main Function                       		    |
 |______________________________________________________________________________|
 */
sbit servo = P2^7;

void mainS(void){

    Timer0_init();
    
	while(1){
        servoMotor_rotate_0();
        MSdelay(1000);
        servoMotor_rotate_90();
        MSdelay(1000);
        servoMotor_rotate_180();
        MSdelay(1000);
        
	}
	
}
