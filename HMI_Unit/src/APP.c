/*	______________________________________________________________________________
   |																			  |
   | APP: Human Machine Interface ECU Application								  |
   |																			  |
   | File Name: APP.h															  |
   |																			  |
   | Description: Source file for the HMI ECU Application						  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "LIB/std_types.h"
#include "MCAL/USART/usart.h"
#include "MCAL/GPIO/gpio.h"
#include "HAL/KEYPAD/keypad.h"
#include "HAL/LCD/lcd.h"
#include "MCAL/TIMER0/timer0.h"
#include "MCAL/DELAY/delay.h"
#include <REG52.H>
#include "commands.h"

#define PAGE1				0
#define PAGE2				1
#define UNLOCKED			0
#define LOCKED				1
#define TRIES_PERMITTED		3
/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Function responsible for transfer the password to Control ECU
 */
void send_password(uint8 *password_arr);

/*
 * Description :
 -> Function responsible for showing alarm screen
 */
void Alarm_mode(void);

/*
 * Description :
 -> Function responsible for taking the password from the user using keypad
 */
void take_password_from_user(void);

/*______________________________________________________________________________
 |                         Global Variables Deceleration                        |
 |______________________________________________________________________________|
 */
uint8  MultiUsedCounter = 0 , PasswordBuff[5] , i, pageNumber = PAGE1;

/*______________________________________________________________________________
 |                       		  Main Function                       		    |
 |______________________________________________________________________________|
 */
int main (void){
	
	uint8 NumberOfTries = 0 ;	/* to count the no of wrong passwords will be entered */
	uint8 PasswordCorrectnessFlag = 0 ;	/* This flag is true when a correct password is entered */
	uint8 DoorState = LOCKED;
	/* This flag is true if the two password which user enters equal each other while creating new password */
	uint8 PasswordsMatchingFlag = 1 ;
	uint8 PasswordSetFlag;	/* This flag is true when the password is successfully created */
	/* The configuration structure of the UART protocol */
	P0 = 0xFF;
	P1 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	LCD_init();
	UART_init(UART_9600baudRate);

	LCD_displayString("   SMART HOME   ");
	LCD_moveCursor(1,0);
	LCD_displayString("     SYSTEM   ");
	MSdelay(2000);
	UART_sendByte(IS_PASSWORD_SET);		/* Asking Control ECU if the password was created or not? */
	
	if(UART_recieveByte() == SETTED)
		PasswordSetFlag = 1;
	else
		PasswordSetFlag = 0;
		
	while(1){

		if(PasswordSetFlag){			/* If the password was created */

			NumberOfTries = 0;			/* Reseting number of tries */
			LCD_clearScreen();

			if(pageNumber == PAGE1){
				/* Showing the menu */
				if(DoorState == LOCKED)
					LCD_displayStringRowColumn(0,0,"A : Open Door");
				else
					LCD_displayStringRowColumn(0,0,"A : Close Door");
				LCD_displayStringRowColumn(1,0,"B : Change Pass");
			}
			else if(pageNumber == PAGE2){
					LCD_displayStringRowColumn(0,0,"A Toggle Relay 1");
					LCD_displayStringRowColumn(1,0,"B Toggle Relay 2");
			}
			MSdelay(500);
			switch(KEYPAD_getPressedKey()){

			case 'A':
				/* Asking for the password while the user didn't enter correct password
				 * have remaining attempts */
				
				if(pageNumber == PAGE1){

					do{
					PasswordCorrectnessFlag = 0;	/* Reseting password correctness flag */

					LCD_clearScreen();
					LCD_displayString("Enter Password:");
					LCD_moveCursor(1,0);
					LCD_displayString("     ");

					/* Getting Control ECU ready to receive the password */
					UART_sendByte(TAKE_MAIN_PASSWORD);

					/* Taking the password from the user using keypad */
					take_password_from_user();

					/* Sending the password to Control ECU to check it */
					send_password(PasswordBuff);

					MSdelay(15);

					if(UART_recieveByte() == CORRECT_PASSWORD){	/* If the password is correct */

						PasswordCorrectnessFlag = 1;
						/* Ask Control ECU to unlock/lock the door */
						if(DoorState == UNLOCKED){
							UART_sendByte(CLOSE_DOOR);
							DoorState = LOCKED;
							LCD_clearScreen();
							LCD_displayStringRowColumn(0,0,"Locking...");
						}
						else if(DoorState == LOCKED){
							UART_sendByte(OPEN_DOOR);
							DoorState = UNLOCKED;
							LCD_clearScreen();
							LCD_displayStringRowColumn(0,0,"Unlocking...");
						}
						MSdelay(1000);
						LCD_clearScreen();
						
					}
					else {	/* If the password is wrong */
						PasswordCorrectnessFlag = 0;
						NumberOfTries++;

						LCD_clearScreen();
						LCD_displayString("Wrong Password!");
						LCD_moveCursor(1,0);
						LCD_displayString("Tries Remain: ");
						LCD_displayCharacter((TRIES_PERMITTED-NumberOfTries) | 0x30);
						MSdelay(2000);

					}
				}while((NumberOfTries < TRIES_PERMITTED) && (PasswordCorrectnessFlag == 0));
				
				/* If the user exhausted all attempts */
				if(NumberOfTries == TRIES_PERMITTED){
					NumberOfTries = 0;
					UART_sendByte(ALARM_MODE);	/* Ask Control ECU to make alarm */
					Alarm_mode();
				}
				}
				else if(pageNumber == PAGE2){
					UART_sendByte(TOGGLE_RELAY1);
					LCD_clearScreen();
					LCD_displayString("     Relay 1    ");
					LCD_displayStringRowColumn(1,0,"   is Toggled");
					MSdelay(1000);
				}
				break;

			case 'B':
				/* Asking for the password while the user didn't enter correct password
				 * have remaining attempts */

				if(pageNumber == PAGE1){
					do{
					PasswordCorrectnessFlag = 0;		/* Reseting password correctness flag */

					LCD_clearScreen();
					LCD_displayString("Enter Password:");
					LCD_moveCursor(1,0);
					LCD_displayString("     ");
					PasswordsMatchingFlag = 1;
					MSdelay(500);

					/* Getting Control ECU ready to receive the password */
					UART_sendByte(TAKE_MAIN_PASSWORD);

					/* Taking the password from the user using keypad */
					take_password_from_user();

					/* Sending the password to Control ECU to check it */
					send_password(PasswordBuff);

					MSdelay(15);

					if(UART_recieveByte() == CORRECT_PASSWORD){		/* If the password is correct */

						PasswordSetFlag = 0;		/* Make the user able to create new password */
						PasswordCorrectnessFlag = 1;
					}

					else{	/* If the password is wrong */

						NumberOfTries++;

						LCD_clearScreen();
						LCD_displayString("Wrong Password!");
						LCD_moveCursor(1,0);
						LCD_displayString("Tries Remain: ");
						LCD_displayCharacter((TRIES_PERMITTED-NumberOfTries) | 0x30);
						MSdelay(2000);

					}
					}
					while((NumberOfTries < TRIES_PERMITTED) && !PasswordCorrectnessFlag);

					if(NumberOfTries == TRIES_PERMITTED){
						NumberOfTries = 0;
						UART_sendByte(ALARM_MODE);		/* Ask Control ECU to make alarm */
						Alarm_mode();
					}
				}
				else if(pageNumber == PAGE2){
					UART_sendByte(TOGGLE_RELAY2);
					LCD_clearScreen();
					LCD_displayString("     Relay 2    ");
					LCD_displayStringRowColumn(1,0,"   is Toggled");
					MSdelay(1000);
				}
				break;

			case 'C':
				pageNumber ^= 1;
				break;
			}
			
		}

		else{

			LCD_clearScreen();
			LCD_displayString("Enter New Pass:");
			LCD_moveCursor(1,0);
			LCD_displayString("     ");

			PasswordsMatchingFlag = 1;

			/* Getting Control ECU ready to receive the password */
			UART_sendByte(TAKE_THE_FIRST_PASSWORD);

			/* Taking the password from the user using keypad */
			take_password_from_user();

			/* Sending the password to Control ECU to check it */
			send_password(PasswordBuff);

			LCD_clearScreen();
			LCD_displayString("Re-Enter Pass:");
			LCD_moveCursor(1,0);
			LCD_displayString("     ");
			MSdelay(15);

			/* Getting Control ECU ready to receive the password */
			UART_sendByte(TAKE_THE_SECOND_PASSWORD);

			/* Taking the password from the user using keypad */
			take_password_from_user();

			/* Sending the password to Control ECU to check it */
			send_password(PasswordBuff);

			MSdelay(15);

			/* Asking Control ECU if the two password are identical or not? */
			UART_sendByte(ARE_THEM_MATCHED);
			PasswordsMatchingFlag = UART_recieveByte();

			if(PasswordsMatchingFlag == MATCHED){	/* If identical */

				PasswordSetFlag = 1;
				PasswordsMatchingFlag = 0;
			}

			else {	/* If not identical */
				LCD_clearScreen();
				LCD_displayString("   Unmatched!  ");
				MSdelay(1000);
			}

		}

	}


}

void send_password(uint8 *password_arr){
	for(i = 0 ; i < 5 ; i++){
		UART_sendByte(password_arr[i]);
		MSdelay(15);
	}

}

void Alarm_mode(void){
	LCD_clearScreen();
	MultiUsedCounter = 5;
	while(MultiUsedCounter > 0){
		LCD_displayString("    WARNING!    ");
		MSdelay(500);
		LCD_clearScreen();
		MSdelay(500);
		MultiUsedCounter--;
	}

}
void take_password_from_user(void){
	for(MultiUsedCounter = 0 ; MultiUsedCounter < 5 ; MultiUsedCounter++){
		PasswordBuff[MultiUsedCounter] = KEYPAD_getPressedKey();
		if(PasswordBuff[MultiUsedCounter] >= '0' && PasswordBuff[MultiUsedCounter] <= '9'){
			LCD_displayCharacter(PasswordBuff[MultiUsedCounter]);
			MSdelay(500);
			LCD_moveCursor(1,5+MultiUsedCounter);
			LCD_displayCharacter('*');
		}
		else
			MultiUsedCounter--;
		MSdelay(15);
	}
	while(KEYPAD_getPressedKey() != '#');
}
