/*****************************************************************************
 *	Module: Implementation main for Fan controller System
 *
 *	File Name:	main.c
 *
 *	Created on May 12 , 2023
 *
 *	Author:	Yousef Samy
 ******************************************************************************/

#include "LCD.h"
#include "DC_MOTOR.h"
#include "ADC.h"
#include "LM35.h"
#include <util/delay.h>
/********************************************************
 *	Function Name : main(void)
 * 	Description:
 * 	Implementation a Simple Fan Controller System
 ********************************************************
 * 	HAL:	DC_MOTOR 		LCD			Temperature_Sensor
 * 	MCAL:	TIMER0(PWM)		DIO			ADC
 ********************************************************/
int main(void)
{
	uint8 temp;
	/* Start LCD and DcMotor*/
	LCD_init();
	DcMotor_init();
	/* Choose Internal_RefVolt and PreScaler 8*/
	ConfigType ADC_Config ={Internal_Ref_ON , N_8 };
	ADC_init( &ADC_Config);
	/*Just Display*/
	LCD_moveCursor(0,4);
	LCD_displayString("Hello :)");
	_delay_ms(200);
	LCD_moveCursor(0,2);
	LCD_displayString("Fan Controller");
	LCD_moveCursor(1,6);
	LCD_displayString("System");
	_delay_ms(200);
	LCD_clearScreen();
	LCD_moveCursor(0,4);
	LCD_displayString("FAN IS OFF");
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =    C");
	while(1)
	{
		/* Get Temperature from Sensor*/
		temp=LM35_getTemperature();
		/*Check temp and Display ON or OFF*/
		if(temp>=100)
		{
		LCD_moveCursor(1,11);
		LCD_integerToString(temp);
		_delay_ms(20);			/*Just delay for hanging in Protues*/
		}
		else
		{
		LCD_moveCursor(1,11);
		LCD_integerToString(temp);
		LCD_displayCharacter(' ');	/*To delete Difference betweeen num two ,Three digits in LCD*/
		}
		_delay_ms(20);			/*Just delay for hanging in Protues*/
		if(temp >=30)
		{
			LCD_moveCursor(0,11);
			LCD_displayString("ON ");
			_delay_ms(20);		/*Just delay for hanging in Protues*/
		}
		else
		{
			LCD_moveCursor(0,11);
			LCD_displayString("OFF");
			_delay_ms(20);		/*Just delay for hanging in Protues*/
		}
		/*
		 * Accroding to temperature will send speed*/

		if(temp<30)
		{
			DcMotor_Rotate(Stop,0);
		}

		else if(temp >=30 && temp<60)
		{
			DcMotor_Rotate(Clock_Wise,25);
		}
		else if(temp >=60 && temp <90)
		{
		DcMotor_Rotate(Clock_Wise,50);
		}
		else if(temp>=90 && temp <120)
		{
			DcMotor_Rotate(Clock_Wise,75);
		}
		else if(temp>=120)
		{
			DcMotor_Rotate(Clock_Wise,100);
		}
		_delay_ms(20);		/*Just delay for hanging in Protues*/
	}


}

