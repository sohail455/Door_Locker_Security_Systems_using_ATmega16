/****************************************************************************************
 * File Name: lcd.c
 *
 * Description: source file for lcd driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/
#define F_CPU 8000000UL
#include<util/delay.h>
#include"lcd.h"
#include"gpio.h"

/***************************************************************************************
 *                      Functions Definitions
 ***************************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */

void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+3, PIN_OUTPUT);
	LCD_sendCommand(LCD_GO_TO_HOME);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#else
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Send the required command to the screen
 */

void LCD_sendCommand(uint8 command)
{
	uint8 lcd_port_value = 0;
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (command & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0F0) | ((command & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0F0) | (command & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif


}

/*
 * Description :
 * Display the required character on the screen
 */

void LCD_displayCharacter(uint8 data)
{
	uint8 lcd_port_value = 0;
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (data & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0F0) | ((data & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0F0) | (data & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif
}


/*
 * Description :
 * Display the required string on the screen
 */

void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 value;
	switch(row)
	{
	case 0:
		value = col;
		break;
	case 1:
		value = col + 0x40;
		break;
	case 2:
		value = col+ 0x10;
		break;
	case 3:
		value = col + 0x50;
		break;
	}
	LCD_sendCommand(LCD_SET_CURSOR_LOCATION | value);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col);
	LCD_displayString(Str);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */

void LCD_intgerToString(int data)
{
	uint8 buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Display custom character on the screen
 */

void LCD_customChar(const uint8 *Symble,const uint8 location)
{
	uint8 i = 0;
	LCD_sendCommand(0x40 | (location * 8));
	for(i = 0; i < 8; i++)
	{
		LCD_displayCharacter(Symble[i]);
	}

}