#ifndef APP_MAIN_H_
#define APP_MAIN_H_

//global variable for speed
uint8 speed;


//function that adjust the fan

#define adjustFan() {\
	uint8 temp;\
	char DCMotor_Staus[3] = "OFF";\
	temp = LM35_getTemperature();\
	LCD_moveCursor(1, 7);\
	if(temp < 10){\
		/*stop the fan*/ \
		speed = 0;\
		*DCMotor_Staus = "OFF";\
		DcMotor_Rotate(STOP, speed);\
		LCD_moveCursor(1, 7);\
		LCD_displayString(" ");\
		LCD_moveCursor(1, 8);\
		LCD_intgerToString(temp);\
		LCD_moveCursor(1, 9);\
		LCD_displayString(" ");\
	} else if (temp < 30) {\
		/*stop the fan*/ \
		speed = 0;\
		*DCMotor_Staus = "OFF";\
		DcMotor_Rotate(STOP, speed);\
		LCD_intgerToString(temp);\
		LCD_moveCursor(1, 9);\
		LCD_displayString(" ");\
	} else if (temp >= 30 && temp < 60) {\
		/*rotate clockWise with 25% of it's max speeed*/\
		speed = 25;\
		*DCMotor_Staus = "ON ";\
		DcMotor_Rotate(CW, speed);\
		LCD_intgerToString(temp);\
		LCD_moveCursor(1, 9);\
		LCD_displayString(" ");\
	} else if (temp >= 60 && temp < 90) {\
		/*rotate clockWise with 50% of it's max speeed*/\
		speed = 50;\
		*DCMotor_Staus = "ON ";\
		DcMotor_Rotate(CW, speed);\
		LCD_intgerToString(temp);\
		LCD_moveCursor(1, 9);\
		LCD_displayString(" ");\
	} else if (temp >= 90 && temp < 100) {\
		/*rotate clockWise with 75% of it's max speeed*/\
		speed = 75;\
		*DCMotor_Staus = "ON ";\
		DcMotor_Rotate(CW, speed);\
		LCD_intgerToString(temp);\
		LCD_moveCursor(1, 9);\
		LCD_displayString(" ");\
	} else if(temp >= 100 && temp < 120){\
		/*rotate clockWise with 75% of it's max speeed*/\
		speed = 75;\
		*DCMotor_Staus = "ON ";\
		DcMotor_Rotate(CW, speed);\
		LCD_intgerToString(temp);\
	}else {\
		/*rotate clockWise with 100% of it's max speeed*/\
		speed = 100;\
		*DCMotor_Staus = "ON ";\
		DcMotor_Rotate(CW, speed);\
		LCD_intgerToString(temp);\
	}\
	LCD_moveCursor(0, 8);\
	LCD_displayString(*DCMotor_Staus);\
}

#endif /* APP_MAIN_H_ */
