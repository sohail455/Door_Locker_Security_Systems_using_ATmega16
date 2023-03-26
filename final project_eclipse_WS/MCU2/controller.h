/****************************************************************************************
 * File Name: controller.h
 *
 * Description: header file for controller driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#define F_CPU 8000000UL
#include"uart.h"
#include<string.h>
#include<util/delay.h>
#include"twi.h"
#include"external_eeprom.h"
#include"dc_motor.h"
#include"timer0.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"
#include"buzzer.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NEW_PASSWORD     0x01
#define ready            0x02
#define COMPARE          0x03
#define MATCHED          0x04
#define NOT_MATCHED      0x05
#define OPEN_DOOR        0x07
#define FAIL             0x08
#define PASSWORD_SIZE    6
#define EEPROM_ADDRESS   0x0000
#define GATE_IS_OPEN     0x09
#define GATE_IS_CLOSE    0x0A
#define WARNING          0x0B
#define SAFE             0x0C
#define ONE_MINUTE       1500
#define FIFTEEN_SECONDS  465
#define THREE_SECONDS    93
#define TWI_BIT_RATE     0x02
#define TWI_PRESCALER    0x00
#define TWI_ADDRESS      0x01
#define UART_BAUD_RATE  9600
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void save_password(void);

void get_password(void);

void open(void);

void open_mechanisim(void);

void alarm_on(void);

void alarm_off(void);


#endif /* CONTROLLER_H_ */
