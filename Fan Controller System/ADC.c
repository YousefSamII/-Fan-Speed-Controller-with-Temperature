/*****************************************************
 * Module: ADC Driver
 *
 * File Name: ADC.c
 *
 * Description: Source File for ADC Driver
 *
 * Author: Yousef Samy
 *
 *****************************************************/

#include "ADC.h"
#include"MACROS.h"
#include <avr/io.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function Name: ADC_init()
 * Description:
 * 	Enable Module ADC
 */

void ADC_init(const ConfigType * Config_Ptr)
{
	/*			ADMUX Register
	 * 1.Choose Choose Referance Volt
	 * 2.ADC Left AdjustResult =0 (disable)
	 * 3.Channel Zero as initial value MUX0:MUX4=0
	 */
	ADMUX= (ADMUX & 0x3F) | ((Config_Ptr->refVolt<<6));
	/*		ADCSRA Register
	 * 1.Enable ADC
	 * 2.Disable Interrupt
	 * 3.Choose Prescaler		F of ADC Range 50:200 KHZ
	 */
	SET_BIT(ADCSRA,ADEN);
	ADCSRA= (ADCSRA & 0xF8) | (Config_Ptr->preScaler);
}
/*
 * Function Name: ADC_readChannel()
 * Description:
 * 	Return digital Value of ADC
 */

uint16 ADC_readChannel(uint8 ch_num)
{
	/*Insert Num of channel to MUX0:Mux4*/
	ADMUX=(ADMUX & 0xE0) | (ch_num & 0x07);
	/*Start Conversion*/
	SET_BIT(ADCSRA,ADSC);
	/* Using Polling Techniques*/
	while(BIT_IS_CLEAR(ADCSRA,ADSC)){};
	/*Clear Flag */
	SET_BIT(ADCSRA,ADIF);
	/* Return Data Register*/
	return ADC;
}
