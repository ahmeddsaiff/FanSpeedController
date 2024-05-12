#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_

#include "../CommonHeader-UsedFiles/std_types.h"
#include "../CommonHeader-UsedFiles/common_macros.h"

#define ADC_MAX_VALUE 1023
#define ADC_VREF 2.56

typedef enum
{
	F_CPU_2=1,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef enum
{
	VREF_OFF,VREF_5V,VREF_Reserved,VREF_2_56V
}ADC_ReferenceVolatge;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* MCAL_ADC_H_ */
