/****************************************************************
 * Module: LM35 Sensor
 *
 * File Name: LM35.h
 *
 * Description:	Header File for LM35 sensor
 *
 * Author: Yousef Samy
 *
 ****************************************************************/

#ifndef LM35_H_
#define LM35_H_

#include"standard_types.h"
/*
 ************************************************************************
						Definitions
 ************************************************************************
 */
#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150
/*
 ************************************************************************
						Function Prototypes
 ************************************************************************
 */
uint8 LM35_getTemperature(void);
#endif /* LM35_H_ */
