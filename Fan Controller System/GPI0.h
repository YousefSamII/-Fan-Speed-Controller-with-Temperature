/************************************************************
 * Module: GPIO
 *
 * File Name: GPIO.h
 *
 *  Description: Header File for The AVR GPIO
 *
 *  Author: Yousef Samy
 *
 ***********************************************************/


/* To Avoid Duplicate File*/
#ifndef GPI0_H_
#define GPI0_H_
#include "standard_types.h"

/********************************************************
 * 						Definitions						*
 *******************************************************/
#define NUM_PINS_PER_PORT		8
#define	NUM_OF_PORTs			4

	/*Just ID for PINS*/
#define PIN0_ID					0
#define PIN1_ID					1
#define PIN2_ID					2
#define PIN3_ID					3
#define PIN4_ID					4
#define PIN5_ID					5
#define PIN6_ID					6
#define PIN7_ID					7

	/*Just ID for PORTs*/
#define PORTA_ID				0
#define PORTB_ID				1
#define PORTC_ID				2
#define PORTD_ID				3
/********************************************************
 * 						Types Declaration				*
 *******************************************************/
typedef enum{
	INPUT_PIN,OUTPUT_PIN
}GPIO_pinDirectionType;

typedef enum{
	INPUT_PORT,OUTPUT_PORT=0xFF
}GPIO_portDirectionType;

/********************************************************
 * 						Functions Prototypes			*
 *******************************************************/

/* Function Name: GPIO_setupPinDirection
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num , uint8 pin_num ,GPIO_pinDirectionType direction);

/* Function Name: GPIO_writePin
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num ,uint8 pin_num ,uint8 value);

/* Function Name: GPIO_readPin
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num ,uint8 pin_num);

/* Function Name: GPIO_setupPortDirection
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/* Function Name: GPIO_writePort
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/* Function Name: GPIO_readPort
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);





#endif /* GPIO_H_ */
