
#include "keypad.h"
#include "gpio.h"
#include "std_types.h"

unsigned char KEYPAD_getPressedKey(){
	
	while(1){
		
		GPIO_writePin(KEYPAD_COL1_PORT_ID, KEYPAD_COL1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_COL2_PORT_ID, KEYPAD_COL2_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_COL3_PORT_ID, KEYPAD_COL3_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_COL4_PORT_ID, KEYPAD_COL4_PIN_ID, LOGIC_HIGH);
		
		GPIO_writePin(KEYPAD_ROW1_PORT_ID, KEYPAD_ROW1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(KEYPAD_ROW2_PORT_ID, KEYPAD_ROW2_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_ROW3_PORT_ID, KEYPAD_ROW3_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_ROW4_PORT_ID, KEYPAD_ROW4_PIN_ID, LOGIC_HIGH);
		
		if(GPIO_readPin(KEYPAD_COL1_PORT_ID, KEYPAD_COL1_PIN_ID) == LOGIC_LOW){
			return '1';
		}
		if(GPIO_readPin(KEYPAD_COL2_PORT_ID, KEYPAD_COL2_PIN_ID) == LOGIC_LOW){
			return '2';
		}
		if(GPIO_readPin(KEYPAD_COL3_PORT_ID, KEYPAD_COL3_PIN_ID) == LOGIC_LOW){
			return '3';
		}
		if(GPIO_readPin(KEYPAD_COL4_PORT_ID, KEYPAD_COL4_PIN_ID) == LOGIC_LOW){
			return 'A';
		}
			
		GPIO_writePin(KEYPAD_ROW1_PORT_ID, KEYPAD_ROW1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_ROW2_PORT_ID, KEYPAD_ROW2_PIN_ID, LOGIC_LOW);
		
		if(GPIO_readPin(KEYPAD_COL1_PORT_ID, KEYPAD_COL1_PIN_ID) == LOGIC_LOW){
			return '4';
		}
		if(GPIO_readPin(KEYPAD_COL2_PORT_ID, KEYPAD_COL2_PIN_ID) == LOGIC_LOW){
			return '5';
		}
		if(GPIO_readPin(KEYPAD_COL3_PORT_ID, KEYPAD_COL3_PIN_ID) == LOGIC_LOW){
			return '6';
		}
		if(GPIO_readPin(KEYPAD_COL4_PORT_ID, KEYPAD_COL4_PIN_ID) == LOGIC_LOW){
			return 'B';
		}
		
		GPIO_writePin(KEYPAD_ROW2_PORT_ID, KEYPAD_ROW2_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_ROW3_PORT_ID, KEYPAD_ROW3_PIN_ID, LOGIC_LOW);
		
		if(GPIO_readPin(KEYPAD_COL1_PORT_ID, KEYPAD_COL1_PIN_ID) == LOGIC_LOW){
			return '7';
		}
		if(GPIO_readPin(KEYPAD_COL2_PORT_ID, KEYPAD_COL2_PIN_ID) == LOGIC_LOW){
			return '8';
		}
		if(GPIO_readPin(KEYPAD_COL3_PORT_ID, KEYPAD_COL3_PIN_ID) == LOGIC_LOW){
			return '9';
		}
		if(GPIO_readPin(KEYPAD_COL4_PORT_ID, KEYPAD_COL4_PIN_ID) == LOGIC_LOW){
			return 'C';
		}
		
		GPIO_writePin(KEYPAD_ROW3_PORT_ID, KEYPAD_ROW3_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(KEYPAD_ROW4_PORT_ID, KEYPAD_ROW4_PIN_ID, LOGIC_LOW);
		
		if(GPIO_readPin(KEYPAD_COL1_PORT_ID, KEYPAD_COL1_PIN_ID) == LOGIC_LOW){
			return '*';
		}
		if(GPIO_readPin(KEYPAD_COL2_PORT_ID, KEYPAD_COL2_PIN_ID) == LOGIC_LOW){
			return '0';
		}
		if(GPIO_readPin(KEYPAD_COL3_PORT_ID, KEYPAD_COL3_PIN_ID) == LOGIC_LOW){
			return '#';
		}
		if(GPIO_readPin(KEYPAD_COL4_PORT_ID, KEYPAD_COL4_PIN_ID) == LOGIC_LOW){
			return 'D';
		}
	}
	
}