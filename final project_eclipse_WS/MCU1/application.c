/****************************************************************************************
 * File Name: application.c
 *
 * Description: source file for MCU1 driver.
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/
#include"HMI.h"



int main(void)
{
	UART_ConfigType uart_configtype={UART_BAUD_RATE,EIGHT_BITS,DISABLE,ONE_BIT};
	UART_init(&uart_configtype);
	LCD_init();
	get_initial_password();
	while(1)
	{
		main_option();
	}
}

