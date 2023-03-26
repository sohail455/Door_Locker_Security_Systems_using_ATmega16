/****************************************************************************************
 * File Name: application.c
 *
 * Description: source file for MCU2 driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/
#include"controller.h"



int main(void)
{

	SREG |=(1<<7);
	buzzer_init();
	UART_ConfigType uart_configtype={UART_BAUD_RATE,EIGHT_BITS,DISABLE,ONE_BIT};
	UART_init(&uart_configtype);
	TWI_ConfigerType twi_configtype = {TWI_BIT_RATE,TWI_PRESCALER,TWI_ADDRESS};
	TWI_init(&twi_configtype);

	while(1)
	{
		switch(UART_receiveByte())
		{
		case NEW_PASSWORD:
			save_password();
			break;
		case COMPARE:
			get_password();
			break;
		case OPEN_DOOR:
			open();
			break;
		case  WARNING:
			alarm_on();
			break;

		}

	}
}

