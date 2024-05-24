/**************************************************
 * Module: ADC Driver
 *
 * File Name: ADC.h
 *
 * Description: Header File for ADC Driver
 *
 * Author: Yousef Samy
 *
 *************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "standard_types.h"
/************************************
 * 			Definitions		        *
 ***********************************/
typedef enum{
	Internal_Ref_off,AVCC,Reserved,Internal_Ref_ON
}REF_VOLT;


typedef enum{
	N_2 , N__2 , N_4 , N_8 , N_16 , N_32 , N_64 , N_128
}PRE_SCALER;

typedef struct{
	REF_VOLT refVolt;
	PRE_SCALER preScaler;
}ConfigType;

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/************************************
 * 			Function Prototypes     *
 ***********************************/
void ADC_init(const ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 ch_num);


#endif /* ADC_H_ */
