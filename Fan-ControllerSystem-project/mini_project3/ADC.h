/*
 * ADC.h
 *
 *  Created on: Oct 9, 2023
 *      Author: Ahmed Shawareb
 */

#ifndef ADC_H_
#define ADC_H_
#define ADC_REF_VOLT_VALUE		2.56
#define ADC_MAXIMUM_VALUE		 5

#include "std_types.h"
typedef enum
{
		PRESCALER_2 , PRESCALER_4=2 , PRESCALER_8 ,PRESCALER_16 , PRESCALER_32 , PRESCALER_64 , PRESCALER_128
}ADC_Prescaler;

typedef enum
{
	AREF , AVCC , INTERNAL=3
}ADC_ReferenceVolatge;

typedef struct{
      ADC_ReferenceVolatge ref_volt;
      ADC_Prescaler prescaler;
}ADC_ConfigType;
/**********************************
 *      FUNCTION PROTOTYPES
 **********************************/


void ADC_init(const ADC_ConfigType * Config_Ptr) ;

uint16 ADC_readChannel (uint8 ch_num);

#endif /* ADC_H_ */
