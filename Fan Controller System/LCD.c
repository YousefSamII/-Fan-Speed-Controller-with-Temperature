/***************************************************************
 * 	Module: LCD Driver
 *
 *	File Name: LCD.c
 *
 *  Description: Source Code For LCD Driver
 *
 *  Author: Yousef Samy
 *
 ***************************************************************/
#include"LCD.h"
#include "GPI0.h"
#include"MACROS.h"
#include <util/delay.h>
/*
 * Function Name: LCD_init()
 * Description:
 * 	Initialization for LCD Driver
 */
void LCD_init(void)
{
	/* Make both Rs and E  output pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,OUTPUT_PIN);
	/* LCD Power ON delay always > 15ms */
	_delay_ms(20);
	/* Make Data Path O/P Port*/
#ifdef	LCD_FOUR_BIT_MODE
	GPIO_setupPinDirection(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+1,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+2,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+3,OUTPUT_PIN);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif
#ifndef LCD_FOUR_BIT_MODE
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,OUTPUT_PORT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */



}

/*
 * Function Name: LCD_sendCommand()
 * Description:
 * 	Send a Command To LCD Through Data Path accroding to Data Sheet
 */
void LCD_sendCommand(uint8 command)
{
	/* Make RS=*/
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID ,LOGIC_LOW);
	/* From AC Characteristic of LCD tas must delay by 50 nSec*/
	_delay_ms(1);
	/*Make Enable=1*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID ,LOGIC_HIGH);
	/* From AC Characteristic of LCD  must delay (tpw-tdsw) by 190 nSec*/
	_delay_ms(1);
	/* Send Command*/
#ifndef LCD_FOUR_BIT_MODE
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	/* From AC Characteristic of LCD  must delay tdsw by 100 nSec*/
	_delay_ms(1);
	/* Return E=0*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID ,LOGIC_LOW);
	/* From AC Characteristic of LCD  must delay th by 13 nSec*/
	_delay_ms(1);
#endif
#ifdef LCD_FOUR_BIT_MODE
	/*Rotate command to Right To Get Last Four Bits*/
	ROR(command,4);
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID ,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+1 ,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+2 ,GET_BIT(command,3));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+3 ,GET_BIT(command,4));
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	/*Return command to its original position*/
	ROL(command,4);
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID ,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+1 ,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+2 ,GET_BIT(command,3));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+3 ,GET_BIT(command,4));
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif

}
/*
 * Function Name: LCD_displayCharacter()
 * Description:
 * 	Display a Character  To LCD Through Data Path accroding to Data Sheet
 */
void LCD_displayCharacter(uint8 data)
{
	/* Make RS=1*/
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID ,LOGIC_HIGH);
	/* From AC Characteristic of LCD tas must delay by 50 nSec*/
	_delay_ms(1);
	/*Make Enable=1*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID ,LOGIC_HIGH);
	/* From AC Characteristic of LCD  must delay (tpw-tdsw) by 190 nSec*/
	_delay_ms(1);
	/* Send Command*/
#ifndef LCD_FOUR_BIT_MODE
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	/* From AC Characteristic of LCD  must delay tdsw by 100 nSec*/
	_delay_ms(1);
	/* Return E=0*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID ,LOGIC_LOW);
	/* From AC Characteristic of LCD  must delay th by 13 nSec*/
	_delay_ms(1);
#endif
#ifdef LCD_FOUR_BIT_MODE
	/*Rotate command to Right To Get Last Four Bits*/
	ROR(data,4);
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID ,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+1 ,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+2 ,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+3 ,GET_BIT(data,3));
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	/*Return command to its original position*/
	ROL(data,4);
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID ,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+1 ,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+2 ,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_FOUR_BIT_PORT_ID,LCD_DATA_FOUR_BIT_PIN_ID+3 ,GET_BIT(data,3));
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	#endif

}

/*
 * Function Name: LCD_displayString()
 * Description:
 * 	Display a String on LCD
 */
void LCD_displayString(const char*str)
{
	uint8 i=0;
	while(str[i]!='\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
	/***************************************
	 * 			Another Method			   *
	 ***************************************
	 while((*str)!='\0')
	 {
	 LCD_displayCharacter((*str));
	 //increment by 1 byte char to pointer
	 str++;
	 }
	 **************************************/
/*
 * Function Name: LCD_moveCursor()
 * Description:
 * 	Move Cursor to the specific location accroding to row and col
 */
void LCD_moveCursor(uint8 row ,uint8 col)
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
	}
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);

}

/*
 * Function Name: LCD_displayStringRowColumn()
 * Description :
 * 		Display a String At any Position in LCD
 */
void LCD_displayStringRowColumn(uint8 row ,uint8 col,const char*str)
{
	/* go to required position*/
	LCD_moveCursor(row,col);
	/*display*/
	LCD_displayString(str);
}
/*
 * Function Name: LCD_integerToString()
 * Description:
 * 		Convert interger to String and Display it
 */
void LCD_integerToString(int data)
{
	/*Make Array of Character to store ascii of num and size=16,because this Max num can show*/
	char buffer[16];
	/*Using C-Built in-function , 10 is the Base of Number*/
	itoa(data,buffer,10); /* buffer[0]=ASCII for first digit of integer num and So on*/
	LCD_displayString(buffer);
}

/* Function Name: LCD_clearScreen
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
