/*************************************************************
 * Module: LM35 Sensor
 *
 * File Name: LM35.h
 *
 * Description:	Source Code File for LM35 sensor
 *
 * Author: Yousef Samy
 *
 **************************************************************/
#include"ADC.h"
#include"LM35.h"

/*
 * Function Name : LM35_getTemperature()
 * Description:
 * 	return temperature value which sensor get it
 */
uint8 LM35_getTemperature(void)
{
	uint8 temp_value=0;
	uint16 digital_value=0;
	/*get digital Value after use ADC to convert Analog temperature to digital*/
	digital_value=ADC_readChannel(SENSOR_CHANNEL_ID);
	/* Sensor Equation to get temperature Value from digital reading*/
	temp_value=	(uint8)(((uint32)SENSOR_MAX_TEMPERATURE*digital_value*ADC_REF_VOLT_VALUE)/(SENSOR_MAX_VOLT_VALUE*ADC_MAXIMUM_VALUE));
	/*return temperature Value*/
	return temp_value;
}

