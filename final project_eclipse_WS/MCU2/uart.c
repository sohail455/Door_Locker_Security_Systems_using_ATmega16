/****************************************************************************************
 * File Name: uart.c
 *
 * Description: source file for uart driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/
#define F_CPU 8000000UL
#include"uart.h"
#include<avr/io.h>
#include"common_macros.h"

/***************************************************************************************
 *                      Functions Definitions
 ***************************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *ConfigType)
{
	uint16 ubrr_value = 0;
	UCSRA  = (1 << U2X);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRB |=(((ConfigType->character_size) & 0x04) << UCSZ2);
	UCSRC = (((ConfigType->character_size) & 0x03) << UCSZ0);
	UCSRC |=(((ConfigType->parity_mood) & 0x03) << UPM0);
	UCSRC |=((ConfigType->stop_bit_num) << USBS);
	ubrr_value = (uint16)((F_CPU / ((ConfigType->baude_rate) * 8UL)) - 1);
	UBRRH = ubrr_value >> 8;
	UBRRL = ubrr_value;
}
/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;
}
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

}
/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
