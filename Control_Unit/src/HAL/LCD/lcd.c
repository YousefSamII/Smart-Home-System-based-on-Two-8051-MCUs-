/*	____________________________________________________________________________
  |																			    |
  | Module: LCD																    |
  |																			    |
  | File Name: lcd.c														    |
  |																			    |
  | Description: Source file for the LCD driver							        |
  |																			    |
  | Author: Youssif Hossam													    |
  |_____________________________________________________________________________|
*/
#include "MCAL/GPIO/gpio.h"
#include "lcd.h"
#include "LIB/common_macros.h"
#include "MCAL/DELAY/delay.h"

void LCD_init(void){
	
	MSdelay(30);
	
#if(LCD_DATA_BITS_MODE == 4)
	
	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF); 		/* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
	
}

/*
 * Description :
 -> Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	MSdelay(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Write Mode RW=0 */
	MSdelay(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	MSdelay(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	MSdelay(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Data Mode RS=1 */
	MSdelay(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	MSdelay(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,7));

	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	MSdelay(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));

	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,character); /* out the required command to the data bus D0 --> D7 */
	MSdelay(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	MSdelay(1); /* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 -> Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/*
 * Description :
 -> Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;
	
	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
		default:
			lcd_memory_address=0x00;
				break;
	}					
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 -> Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 -> Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

/*
 * Description :
 -> Display the required decimal value on the screen
 */
void LCD_intgerToString(int number)
{
	char buff[16] = {'\0','\0','\0','\0','\0','\0','\0','\0',
									 '\0','\0','\0','\0','\0','\0','\0','\0'}; /* String to hold the ascii result */
	uint8 counter = 0;
	uint8 iterator = 0;
	uint8 swapper;
	uint8 negFlag = 0;									
	if(number & 0x8000){
		number = ~number;
		number += 1;
		negFlag = 1;
	}								 
	while(number != 0){
		buff[counter] = number % 10;
		buff[counter] |= 0x30;
		number /= 10;
		counter++;
	}
		if(negFlag){
			buff[counter] = '-';
			counter++;
		}
		
	counter--;
	while(iterator < counter){
		swapper = buff[iterator];
		buff[iterator] = buff[counter];
		buff[counter] = swapper;
		
		iterator++;
		counter--;
	}
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 -> Clear specific row
 */
void LCD_clearRow(uint8 row){
	LCD_displayStringRowColumn(row,0,"                ");
}

/*
 * Description :
 -> Storing the pattern of custom character on the CGRAM.
 -> The function take the pattern and the index you need to store in.
 */
void LCD_StoreCustomPtrn(uint8 *Pattern , uint8 CGRAM_index){
	uint8 LCD_CGRAM_address , indx ;
	if(CGRAM_index < 8){
		LCD_CGRAM_address = CGRAM_index * 8;
		LCD_sendCommand(LCD_CGRAM_address | LCD_SET_CGRAM_ADDRESS);
		for( indx = 0 ; indx < 8 ; indx++){
			LCD_displayCharacter(Pattern[indx]);
		}
		LCD_sendCommand(LCD_GO_TO_HOME);
	}
}

/*
 * Description :
 -> Showing the pattern of custom character on specific index in CGRAM.
 -> The function take the index in CGRAM and the row and the column to display at.
 */
void LCD_DisplayCustomPtrn(uint8 CGRAM_index , uint8 row , uint8 col){

	LCD_moveCursor(row , col);
	LCD_displayCharacter(CGRAM_index);
}
 