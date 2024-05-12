#include "./ADC.h"
#include "avr/io.h"

void ADC_init(const ADC_ConfigType * Config_Ptr){
//ADMUX Register:
//	REFS1:0 --> 11 to choose the AREF = 2.56v
//	ADLAR = 0 right adjusted
//	MUX4:0 --> 00000 to choose ADC channel 0 as initialization
	ADMUX = (ADMUX & 0X3F) | ((Config_Ptr->ref_volt)<<6);

//ADCSRA Register:
//	ADEN = 1 to enable ADC
//	ADIE = 0 to disable ADC Interrupt
//	ADATE = 0 to disable ADC auto trigger
//	ADSP2:0 = 011 to choose ADC_CLOCK = F_CPU_8
	ADCSRA = (ADCSRA & 0X78) | (Config_Ptr->prescaler) | (1<<ADEN);
}

uint16 ADC_readChannel(uint8 channel_num){
//Input channel_num into the ADMUX Register
//channel_num should be from 0--->7 only (00111)
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);
//Start Conversion by writing '1' to ADSC in ADCSRA Register
	SET_BIT(ADCSRA , ADSC);
//wait until Conversion complete ---> ADIF "the ADC flag" becomes '1'
	while(BIT_IS_CLEAR(ADCSRA , ADIF));
//clear the flag by writing '1' to it
	SET_BIT(ADCSRA , ADIF);
//Return the data
	return ADC;
}
