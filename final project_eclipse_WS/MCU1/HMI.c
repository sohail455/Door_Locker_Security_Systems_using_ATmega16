/****************************************************************************************
 * File Name: HMI.c
 *
 * Description: source file for HMI driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/

#include"HMI.h"

uint8 counter1 = 0;
uint8 counter2 = 0;

/***************************************************************************************
 *                      Functions Definitions
 ***************************************************************************************/

/*
 * Description :
 * function responsible to get the password from the user and check one more time
 * 1- if the password in the second time match with first time it will send the password
 * to controller mcu.
 * 2- else it will ask the user to enter the password again.
 */

void get_initial_password(void)
{
	uint8 password[PASSWORD_SIZE];
	uint8 confirm_password[PASSWORD_SIZE];
	LCD_clearScreen();
	LCD_displayString("enter pass:");
	LCD_moveCursor(1, 0);
	get_password(password);

	LCD_clearScreen();
	LCD_displayString("confirm pass:");
	LCD_moveCursor(1, 0);
	get_password(confirm_password);
	LCD_clearScreen();

	if(strcmp(password,confirm_password) != 0)
	{
		LCD_displayString("No Match!");
		_delay_ms(500);
		LCD_clearScreen();
		LCD_displayString("Please re-enter");
		LCD_moveCursor(1, 0);
		LCD_displayString("Password");
		_delay_ms(1000);
		get_initial_password();
	}
	else
	{
		LCD_displayString("Right Pass");
		_delay_ms(1000);
		LCD_clearScreen();
		UART_sendByte(NEW_PASSWORD);
		send_password(password);
	}
}


/*
 * Description :
 * function responsible to display main options:
 * 1- (+) to open the door.
 * 2- (-) to change the password.
 */

void main_option(void)
{

	LCD_clearScreen();
	LCD_displayString("+:open door");
	LCD_moveCursor(1, 0);
	LCD_displayString("-:change pass");

	while(KEYPAD_getPressedKey() != '-'  && KEYPAD_getPressedKey() != '+')
	{

	}

	if(KEYPAD_getPressedKey() == '+')
	{
		_delay_ms(500);
		open_door_option();
	}
	else if(KEYPAD_getPressedKey() == '-')
	{
		_delay_ms(500);
		reset_password_option();
	}

}

/*
 * Description :
 * function responsible to:
 * 1-ask the user to enter a password.
 * 2-send the password to controller mcu.
 * 3-if the password match it will ask to open the door.
 * 4-else repeat asking three times then cancel the process.
 */

void open_door_option(void)
{
	uint8 entered_pass[PASSWORD_SIZE];
	++counter1;
	if(counter1 == 4)
	{
		UART_sendByte(WARNING);
		LCD_clearScreen();
		LCD_displayString("WARNING");
		_delay_ms(1000);
		counter1 = 0;
		while(UART_receiveByte() != SAFE);
		main_option();
	}

	LCD_clearScreen();
	LCD_displayString("confirm pass");
	LCD_moveCursor(1, 0);
	get_password(entered_pass);
	UART_sendByte(COMPARE);
	send_password(entered_pass);

	UART_sendByte(ready);

	if(UART_receiveByte() == MATCHED)
	{
		UART_sendByte(OPEN_DOOR);
		LCD_clearScreen();
		LCD_displayString("opening door");
		while(UART_receiveByte() != GATE_IS_OPEN)
		{

		}
		LCD_clearScreen();
		LCD_displayString("closing door");
		while(UART_receiveByte() != GATE_IS_CLOSE)
		{

		}
		counter1 = 0;
		main_option();
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Wrong pass!");
		_delay_ms(1000);
		open_door_option();
	}

}

/*
 * Description :
 * function responsible to:
 * 1-ask the user to enter a password.
 * 2-send the password to controller mcu.
 * 3-if the password match it will ask to change the password.
 * 4-else repeat asking three times then cancel the process.
 */

void reset_password_option(void)
{
	uint8 entered_pass[PASSWORD_SIZE];
	++counter2;
	if(counter2 == 4)
	{
		UART_sendByte(WARNING);
		LCD_clearScreen();
		LCD_displayString("WARNING");
		_delay_ms(1000);
		counter2 = 0;
		while(UART_receiveByte() != SAFE);
		main_option();
	}

	LCD_clearScreen();
	LCD_displayString("confirm pass");
	LCD_moveCursor(1, 0);
	get_password(entered_pass);
	UART_sendByte(COMPARE);
	send_password(entered_pass);

	UART_sendByte(ready);

	if(UART_receiveByte() == MATCHED)
	{
		get_initial_password();
		main_option();
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Wrong pass!");
		_delay_ms(1000);
		reset_password_option();
	}

}

/*
 * Description :
 * function responsible to get the password from user to confirm the process
 */

void get_password(uint8 *password)
{
	uint8 key;
	uint8 i;
	for(i = 0; i < PASSWORD_SIZE - 1; i++)
	{
		key = KEYPAD_getPressedKey();
		password[i] = key;
		LCD_displayCharacter('*');
		_delay_ms(500);
	}
	password[i] = '\0';
}

/*
 * Description :
 * function responsible to send the password from user to controller mcu.
 */

void send_password(uint8 *password)
{
	uint8 i;
	for(i = 0; i < PASSWORD_SIZE - 1; i++)
	{
		if(UART_receiveByte() == ready)
			UART_sendByte(password[i]);
	}
}






