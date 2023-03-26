/****************************************************************************************
 * File Name: keypad.c
 *
 * Description: source file for keypad.
 *
 * Author: Eng / Sohail Talaat.
 *
 * *************************************************************************************/

#include"gpio.h"
#include"keypad.h"

/***************************************************************************************
 *                      Functions Definitions
 ***************************************************************************************/


#if (KEYPAD_NUM_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 value);
#elif (KEYPAD_NUM_OF_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 value);
#endif

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col;
	uint8 row;
	uint8 value;
	while(1)
	{

		for(col = 0; col < KEYPAD_NUM_OF_COLS; col++)
		{
			/*each time i will make all pins as input pins*/
			GPIO_setupPortDirection(KEYPAD_PORT_ID, PORT_INPUT);

			/*each time i will make one pin of columns pins as output to out
			 *the zero from it and loop around the row to get the
			 *value*/
			GPIO_setupPinDirection(KEYPAD_PORT_ID, KEYPAD_FIRST_COLUMN_PIN_ID + col, PIN_OUTPUT);
#if(KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
			value = (~(1<<(KEYPAD_FIRST_COLUMN_PIN_ID + col)));
#elif(KEYPAD_BUTTON_PRESSED == LOGIC_HIGH)
			value = (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#endif

			GPIO_writePort(KEYPAD_PORT_ID, value);

			for(row = 0; row < KEYPAD_NUM_OF_ROWS; row++)
			{
				if(GPIO_readPin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row) == KEYPAD_BUTTON_PRESSED)
				{
#if(KEYPAD_NUM_OF_COLS == 3)
					return KEYPAD_4x3_adjustKeyNumber(col+KEYPAD_NUM_OF_COLS*row+1);
#elif(KEYPAD_NUM_OF_COLS == 4)
					return KEYPAD_4x4_adjustKeyNumber(col+KEYPAD_NUM_OF_COLS*row+1);
#endif
				}
			}
		}
	}
}

#if (KEYPAD_NUM_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 value)
{
	uint8 adjusted_value = value;

	switch(value)
	{
	case 10:
		adjusted_value = '*';
		break;
	case 11:
		adjusted_value = 0;
		break;
	case 12:
		adjusted_value = '#';
		break;
	}
	return adjusted_value;
}
#elif (KEYPAD_NUM_OF_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}
#endif
