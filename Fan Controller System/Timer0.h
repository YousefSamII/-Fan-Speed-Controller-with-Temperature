/*********************************************
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description:	header file for Timer0 (Not Complete Driver)
 *
 * Author: Yousef Samy
 *
 *********************************************/

#ifndef TIMER0_H_
#define TIMER0_H_
#include "standard_types.h"

/************************************************************
 * 					Definitions
 ***********************************************************/
typedef enum{
 No_Clk , P_1 , P_8 ,P_64 ,P_256 , P_1024 ,Extrenla_Falling , Extrenal_Rising
}Config_Prescaler;

typedef enum{
	PWM_Normal ,Timer_Reserved , Non_Inverting ,Inverting
}Config_Mode_Fast_PWM;

typedef enum{
	Timer_Normal , PWM_Phase ,CTC , PWM_Fast
}Config_Timer_Mode;

typedef struct{
	Config_Timer_Mode Config_Mode;
	Config_Mode_Fast_PWM PWM_Mode;
	Config_Prescaler Config_Prescaler;
}Config_Timer0;

/************************************************************
 * 					Function Prototypes
 ***********************************************************/
void PWM_Timer0_Start(const Config_Timer0 * Confige_Ptr,uint8 duty_cycle);

#endif /* TIMER0_H_ */
