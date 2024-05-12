/*
 * ADC.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Ahmed Shawareb
 */

#include "ADC.h"
#include "avr/io.h"
#include "common_macros.h"

/**********************************
 *      FUNCTION DEFENITION
 **********************************/


void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	ADMUX = (ADMUX & 0X3F) | ((Config_Ptr->ref_volt)<<6);

	/*to make ADMUX channels bits =0*/
	ADMUX &= 0b11000000;
	ADCSRA = (1<<ADEN);
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);
}

uint16 ADC_readChannel (uint8 ch_num)
{
	ADMUX = ((ADMUX & 0xE0) | (ch_num & 0x07));
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */

	SET_BIT(ADCSRA,ADIF);

	return ADC;
}
