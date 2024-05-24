/*********************************************
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description:	Sourc Code file for Timer0 (Not Complete Driver)
 *
 * Author: Yousef Samy
 *
 *********************************************/
#include "Timer0.h"
#include "GPI0.h"
#include "MACROS.h"
#include <avr/io.h>

/*
 * Function Name: PWM_Timer0_Start()
 * Description:
 * Generate Waveform on OC0 pin with frequency 488.28 HZ
 */
void PWM_Timer0_Start(const Config_Timer0 * Confige_Ptr , uint8 duty_cycle)
{
	/***********************************************************
	 * 1.Set up Timer in Fast PWM Mode
	 * 2.Because WGM01 and WGM00 ,They're Not in Order
	 * 3.WGM01 BIT NUM 3 in TCCR0
	 * 4.WGM00 BIT NUM 6 in TCCR0
	 ************************************************************/
	TCCR0= (TCCR0 & 0xB7) | ((GET_BIT(Confige_Ptr ->Config_Mode,0))<<6) | (( GET_BIT(Confige_Ptr->Config_Mode,1))<<3);
	/* Non-Inverting PWM Mode Start from HIGH*/
	TCCR0 = ( TCCR0 & 0xCF) | (( Confige_Ptr->PWM_Mode)<<4);
	/*Choose PreScaler*/
	TCCR0 = ( TCCR0 & 0xF8 ) | (Confige_Ptr->Config_Prescaler);
	/*initial value 0 to timer register*/
	TCNT0=0;
	/* Pass I/P value to compare Register
	 * Multiple *2.55 because Range speed from 0to 100 but Range
	 * */
	duty_cycle=	(uint8)(((uint16)duty_cycle * 255)/100);
	OCR0=duty_cycle;
	/*Make OC0/PB3 Output pin*/
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,OUTPUT_PIN);
}
