/*
 * DCmotor.c
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Shawareb
 */

#include "gpio.h"
#include "PWM.h"
#include "DCmotor.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);

	GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{

	switch (state)
	{
	case 0 :

		GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);

		break;

	case 1 :

		GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);

		break;

	case 2 :

		GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);

		break;

	}

	 PWM_Timer0_Start(speed);
}
