 /*	____________________________________________________________________________
  |																			    |
  | Module: GPIO															    |
  |																			    |
  | File Name: gpio.h														    |
  |																			    |
  | Description: Source file for the 8051 GPIO driver					        |
  |																			    |
  | Author: 																    |
  |_____________________________________________________________________________|
*/
#include "gpio.h"
#include <reg52.h>
#include "LIB/common_macros.h"
/*
 * Description :
 -> Setup the direction of the required pin input/output.
 -> If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinInput(uint8 port_num, uint8 pin_num)
{
	/*
	 -> Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	    Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 -> In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORT0_ID:
			SET_BIT(P0,pin_num);
			break;
		case PORT1_ID:
			SET_BIT(P1,pin_num);
			break;
		case PORT2_ID:
			SET_BIT(P2,pin_num);
			break;
		case PORT3_ID:
			SET_BIT(P3,pin_num);
			break;
		}
	}
}

/*
 * Description :
 -> Write the value Logic High or Logic Low on the required pin.
 -> If the input port number or pin number are not correct, The function will not handle the request.
 -> If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 -> Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	    Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 -> In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORT0_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(P0,pin_num);
			}
			else
			{
				CLEAR_BIT(P0,pin_num);
			}
			break;
		case PORT1_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(P1,pin_num);
			}
			else
			{
				CLEAR_BIT(P1,pin_num);
			}
			break;
		case PORT2_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(P2,pin_num);
			}
			else
			{
				CLEAR_BIT(P2,pin_num);
			}
			break;
		case PORT3_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(P3,pin_num);
			}
			else
			{
				CLEAR_BIT(P3,pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 -> Read and return the value for the required pin, it should be Logic High or Logic Low.
 -> If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	/*
	 -> Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	    Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 -> In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{
		case PORT0_ID:
			if(BIT_IS_SET(P0,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORT1_ID:
			if(BIT_IS_SET(P1,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORT2_ID:
			if(BIT_IS_SET(P2,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORT3_ID:
			if(BIT_IS_SET(P3,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}

/*
 * Description :
 -> Setup the direction of the required port all pins input/output.
 -> If the direction value is PORT_INPUT all pins in this port should be input pins.
 -> If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 -> If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortInput(uint8 port_num)
{
	/*
	 -> Check if the input number is greater than NUM_OF_PORTS value.
	 -> In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORT0_ID:
			P0 = 0xFF;
			break;
		case PORT1_ID:
			P1 = 0xFF;
			break;
		case PORT2_ID:
			P2 = 0xFF;
			break;
		case PORT3_ID:
			P3 = 0xFF;
			break;
		}
	}
}

/*
 * Description :
 -> Write the value on the required port.
 -> If any pin in the port is output pin the value will be written.
 -> If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 -> If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 -> Check if the input number is greater than NUM_OF_PORTS value.
	 -> In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORT0_ID:
			P0 = value;
			break;
		case PORT1_ID:
			P1 = value;
			break;
		case PORT2_ID:
			P2 = value;
			break;
		case PORT3_ID:
			P3 = value;
			break;
		}
	}
}

/*
 * Description :
 -> Read and return the value of the required port.
 -> If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 -> Check if the input number is greater than NUM_OF_PORTS value.
	 -> In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORT0_ID:
			value = P0;
			break;
		case PORT1_ID:
			value = P1;
			break;
		case PORT2_ID:
			value = P2;
			break;
		case PORT3_ID:
			value = P3;
			break;
		}
	}

	return value;
}
