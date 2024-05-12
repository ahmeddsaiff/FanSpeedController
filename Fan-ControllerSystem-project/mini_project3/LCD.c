 /*
 * LCD.c
 *
 *  Created on: Oct 16, 2023
 *      Author: Ahmed Shawareb
 */


#include "LCD.h"
#include "gpio.h"
#include "common_macros.h"
#include <util/delay.h>


/************************************************************************
 *                      Functions Definitions
 ************************************************************************/

void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	_delay_ms(20); /*LCD needs 15 ms to turn on*/

#if (LCD_DATA_BITS_MODE == 4)

	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID , PIN_OUTPUT);
	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);


#elif (LCD_DATA_BITS_MODE == 8)

	GPIO_setupPortDirection(PORTA_ID,PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif
	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}


void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);

	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

#endif
}


void LCD_displayCharacter(uint8 data)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(data,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID , GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID , GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID , GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , GET_BIT(data,3));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, data);

	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_E_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

#endif

}


void LCD_displayString(const char *Str)
{


	while ((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
}


void LCD_moveCursor(uint8 row , uint8 col)
{
	uint8 lcd_memory_address;
	switch (row)
	{
	case 0 :
		lcd_memory_address=col;
		break;
	case 1 :
		lcd_memory_address=col+0x40;
		break;
	case 2 :
		lcd_memory_address=col+0x10;
		break;
	case 3 :
		lcd_memory_address=col+0x50;
		break;
	}

	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);

}


void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col);
	LCD_displayString(Str); /* display the string */
}


void LCD_intgerToString(int data)
{

	 char buff[16]; /* String to hold the ascii result */
	   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	   LCD_displayString(buff); /* Display the string */

}


void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
