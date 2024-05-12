/*
 * PWM.c
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Shawareb
 */

#include "PWM.h"
#include <avr/io.h>
#include "gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	uint16 duty;
	 duty=((duty_cycle*255)/100);

	 TCCR0 = (1<<WGM01) |  (1<<WGM00) | (1<<COM01) | (1<<CS01);

	 TCNT0 = 6;

	 OCR0 = duty;

}
