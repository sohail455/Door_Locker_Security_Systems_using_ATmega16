/****************************************************************************************
 * File Name: uart.h
 *
 * Description: header file for uart driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/


#ifndef UART_H_
#define UART_H_
#include"std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	DISABLE,EVEN_PARITY=2,ODD_PARITY

}UART_ParityMood;

typedef enum
{
	ONE_BIT,TWO_BITS

}UART_StopBitNum;

typedef enum
{
	FIVE_BITS,SIX_BITS,SEVEN_BITS,EIGHT_BITS,NINE_BITS=7

}UART_CharacterSize;

typedef struct
{
	uint32 baude_rate;
	UART_CharacterSize character_size;
	UART_ParityMood parity_mood;
	UART_StopBitNum  stop_bit_num;

}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *ConfigType);
/*
 * Description :
 * Functional responsible for receive byte to another UART device.
 */
uint8 UART_receiveByte(void);
/*
 * Description :
 * Functional responsible for send byte from another UART device.
 */
void UART_sendByte(uint8 data);
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 *Str);
/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str);



#endif /* UART_H_ */
