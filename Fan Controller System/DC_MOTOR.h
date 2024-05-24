/************************************************************************
  * Module: DC_Motor Driver
  *
  * File Name: DC_Motor.h
  *
  * Description: Header File For DC_Motor Driver
  *
  * Author:	Yousef Samy
  *
************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "standard_types.h"
/***********************************************************
 * 					Definitions							   *
 **********************************************************/
#define	DC_MOTORT_PORT_ID					PORTB_ID

#define DC_MOTOR_INPUT_FIRST_PIN_ID			PIN0_ID
#define DC_MOTOR_INPUT_SECOND_PIN_ID		PIN1_ID

typedef enum{
	Stop , Anti_Clock_Wise ,Clock_Wise
}DcMotor_State;

/***********************************************************
 * 					Functions Prototypes				   *
 **********************************************************/
void DcMotor_init(void);
void DcMotor_Rotate(DcMotor_State state ,uint8 speed);
#endif /* DC_MOTOR_H_ */
