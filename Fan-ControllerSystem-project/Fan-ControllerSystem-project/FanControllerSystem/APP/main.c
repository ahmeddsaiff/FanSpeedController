#include"../CommonHeader-UsedFiles/std_types.h"
#include"../MCAL/ADC.h"
#include "../HAL/lcd.h"
#include "../HAL/lm35_sensor.h"
#include "../HAL/DC_MOTOR.h"
#include "./main.h"

int main(void) {

	ADC_ConfigType config = { VREF_2_56V, F_CPU_8 };
	ADC_init(&config);

	DcMotor_init();

	LCD_init();
	LCD_displayString("FAN IS ");
	LCD_displayStringRowColumn(1, 0, "TEMP =    C");

	while (1) {
		adjustFan();
	}

}


