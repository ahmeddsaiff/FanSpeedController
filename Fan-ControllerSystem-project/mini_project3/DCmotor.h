/*
 * DCmotor.h
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Shawareb
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

typedef enum
{
	STOP , Clockwise , Anti_clockwise
}DcMotor_State;
/***********************************
 *       FUNCTION PROTOTYPE
 ***********************************/


void DcMotor_Init(void);

/*The Function responsible for setup the direction for the two
motor pins through the GPIO driver. */

void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* DCMOTOR_H_ */
