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
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function responsible for receiving the password from HMI ECU
 */
void receive_password(uint8 *PasswordArr);


/*______________________________________________________________________________
 |                       		  Main Function                       		    |
 |______________________________________________________________________________|
 */

void main(void){

	uint8 Password_Arr1[5] , Password_Arr2[5] ;		/* Password buffer arrays */
	uint8 matching_flag ;	/* This flag is true if the two passwords are identical while creating new password */
	uint8 PasswordTempVar;	/* Variable to hold the data of EEPROM before using it */
	uint8 PasswordSetFlag;	/* This flag is true when the password is successfully created */
	uint8 MultiUsedCounter;

	UART_init(UART_9600baudRate);
	Timer0_init();
	servoMotor_rotate(SERVOMOTOR_ROTATE_0);
	BUZZER_off();
	RELAY1_toggle();
	RELAY2_toggle();
	//EEPROM_writeByte(PASSWORD_SET_FLAG_LOCATION , 0);


	while(1){

		switch(UART_recieveByte()){

		case IS_PASSWORD_SET:

			PasswordSetFlag = 0;

			/* reading password set flag from EEPROM */
			PasswordSetFlag = EEPROM_readByte(PASSWORD_SET_FLAG_LOCATION);

			if(PasswordSetFlag)				/* If the password was created */
				UART_sendByte(SETTED);		/* Informing HMI ECU */

			else							/* If the password wasn't created yet */
				UART_sendByte(NOT_SETTED);	/* Informing HMI ECU */

			break;

		case TAKE_THE_FIRST_PASSWORD :		/* Getting ready to receive the first password */

			receive_password(Password_Arr1);

			break;

		case TAKE_THE_SECOND_PASSWORD :		/* Getting ready to receive the second password */

			receive_password(Password_Arr2);

			break;

		case ARE_THEM_MATCHED :				/* Checking if the two passwords are identical or not */

			matching_flag = 1;

			for(MultiUsedCounter = 0 ; MultiUsedCounter < 5 ; MultiUsedCounter++){
				if(Password_Arr1[MultiUsedCounter] != Password_Arr2[MultiUsedCounter]){
					matching_flag = 0;
					break;
				}

			}

			if(matching_flag){		/* If the two password are identical */

				UART_sendByte(MATCHED);		/* Informing HMI ECU that they are identical */

				/* Store the password set flag into EEPROM */
				EEPROM_writeByte(PASSWORD_SET_FLAG_LOCATION , matching_flag);
				MSdelay(15);

				for(MultiUsedCounter = 0 ; MultiUsedCounter < 5 ; MultiUsedCounter++){
					EEPROM_writeByte(MultiUsedCounter , Password_Arr1[MultiUsedCounter]);
					MSdelay(10);
				}

			}

			else {
				UART_sendByte(UNMATCHED);
			}

			MSdelay(10);
			break;

		case TAKE_MAIN_PASSWORD :		/* Checking if the password is correct or not */

			matching_flag = 1;

			receive_password(Password_Arr1);	/* Receiving the password from HMI ECU */

			for(MultiUsedCounter = 0 ; MultiUsedCounter < 5 ; MultiUsedCounter++){
				PasswordTempVar = EEPROM_readByte(MultiUsedCounter);
				if(Password_Arr1[MultiUsedCounter] != PasswordTempVar)
					matching_flag = 0;
				MSdelay(10);
			}

			if(matching_flag)
				UART_sendByte(CORRECT_PASSWORD);	/* Informing HMI ECU that the password is correct */

			else
				UART_sendByte(WRONG_PASSWORD);		/* Informing HMI ECU that the password is wrong */

			break;

		case OPEN_DOOR	:							/* Unlocking the door */

			Timer0_init();
			servoMotor_rotate(SERVOMOTOR_ROTATE_90);
			MSdelay(500);
			break;
		
		case CLOSE_DOOR	:							/* Unlocking the door */
			Timer0_init();
			servoMotor_rotate(SERVOMOTOR_ROTATE_0);
			MSdelay(500);
			break;
			
		case ALARM_MODE :				      /* Alarm mode */
			MultiUsedCounter = 5;
			while(MultiUsedCounter > 0){
				BUZZER_on();
				MSdelay(500);
				BUZZER_off();
				MSdelay(500);
				MultiUsedCounter--;
			}
			break;
    
    	case TOGGLE_RELAY1:
      		RELAY1_toggle();
      		break;

    	case TOGGLE_RELAY2:
      		RELAY2_toggle();
      		break;
		}
	}
	
}

void receive_password(uint8 *PasswordArr){
	uint8 i;
	for(i = 0 ; i < 5 ; i++){
		PasswordArr[i] = UART_recieveByte();
		MSdelay(15);
	}
}
