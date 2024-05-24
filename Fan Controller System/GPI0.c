/********************************************************************
 *	Module: GPIO
 *
 *	File Name: GPIO.c
 *
 *	Description: Source File For GPIO Driver
 *
 *  Author: Yousf Samy
 *
 ********************************************************************/
#include "GPI0.h"
#include "MACROS.h"
#include <avr/io.h>			/*TO use IO PORTS Registers*/

/* Function Name: GPIO_setupPinDirection
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num , uint8 pin_num ,GPIO_pinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num>=NUM_OF_PORTs) || (pin_num>=NUM_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == OUTPUT_PIN)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == OUTPUT_PIN)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == OUTPUT_PIN)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == OUTPUT_PIN)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}
/* Function Name: GPIO_writePin
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num ,uint8 pin_num ,uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num>=NUM_OF_PORTs) || (pin_num>=NUM_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if( value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if( value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if( value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if( value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}
/* Function Name: GPIO_readPin
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num ,uint8 pin_num)
{
	uint8 pin_value= LOGIC_LOW;
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (port_num>=NUM_OF_PORTs) || (pin_num>=NUM_PINS_PER_PORT))
	{
		/*Do Nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PORTA,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PORTB,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PORTC,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PORTD,pin_num))
			{
				pin_value= LOGIC_HIGH;
			}
			else
			{
				pin_value= LOGIC_LOW;
			}
			break;
		}
	}
	return pin_value;
}

/* Function Name: GPIO_setupPortDirection
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction)
{
	/*
	 * Check if port_num Greater Than PORTS of MC
	 */
	if(port_num>=NUM_OF_PORTs)
	{
		/* Do NoThing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC= direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/* Function Name: GPIO_writePort
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if port_num Greater Than PORTS of MC
	 */
	if(port_num>=NUM_OF_PORTs)
	{
		/* Do NoThing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA=value;
			break;
		case PORTB_ID:
			PORTB=value;
			break;
		case PORTC_ID:
			PORTC=value;
			break;
		case PORTD_ID:
			PORTD=value;
			break;
		}
	}
}

/* Function Name: GPIO_readPort
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 port_value=LOGIC_LOW;
	/*
	 * Check if port_num Greater Than PORTS of MC
	 */
	if(port_num>=NUM_OF_PORTs)
	{
		/* Do NoThing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			port_value= PINA;			/* PIN : READ Registers*/
			break;
		case PORTB_ID:
			port_value= PINB;
			break;
		case PORTC_ID:
			port_value = PINC;
			break;
		case PORTD_ID:
			port_value= PIND;
			break;
		}
	}
	return port_value;
}


