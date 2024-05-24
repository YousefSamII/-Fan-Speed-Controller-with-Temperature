/************************************************************************
  * Module: DC_Motor Driver
  *
  * File Name: DC_Motor.h
  *
  * Description: Header File For DC_Motor Driver
  *
  * Author:	Yousef Samy
  *
*************************************************************************/
#include "DC_MOTOR.h"
#include "GPI0.h"
#include "Timer0.h"


/*
 * Function Name: DcMotor_init
 * Description:
 * 	The Function responsible for setup the direction for the two
 *	motor pins through the GPIO driver.
 *	Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void)
{
	/* Make Motor which connected to motor O/P pins*/
	GPIO_setupPinDirection(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,OUTPUT_PIN);
	GPIO_setupPinDirection(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,OUTPUT_PIN);
	/*	Write LOW to make motor in Stop mode*/
	GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
}
/*
 * Function Name: DcMotor_Rotate()
 * Description:
 * 	The function responsible for rotate the DC Motor CW/ or A-CW or
 *	stop the motor based on the state input state value.
 *	Send the required duty cycle to the PWM driver based on the
 *  required speed value.
 */
void DcMotor_Rotate(DcMotor_State  state ,uint8 speed)
{
	/****Choose Configuration of Timer0 in DcMotor ,Beacuse in Main i'm Just deal with HAL*****/
	/*
	 * 1.Fast PWM MODE
	 * 2.Non Inverting
	 * 3.Prescaler 8
	 */
	Config_Timer0 Timer0_Confige= {PWM_Fast , Non_Inverting , P_8};
	/*Choose How DC_Motor Rotate CCW , CW ,Stop*/
	if(state==Stop)
	{
		/*Stop A=0  , B=0*/
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
	}
	else if(state==Clock_Wise)
	{
		/* CW A=1 ,B=0*/
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
	}
	else if(state==Anti_Clock_Wise)
	{
		/*Anti CCW A=0 ,B=1 */
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_HIGH);
	}
	/*Call PWM from MCAL Throug DC_motor in HAL not Main and send to it Configuration*/
	PWM_Timer0_Start( &Timer0_Confige , speed);
}

