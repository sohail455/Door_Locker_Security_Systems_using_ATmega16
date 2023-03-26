/****************************************************************************************
 * File Name: HMI.h
 *
 * Description: header file for HMI driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/

#ifndef HMI_H_
#define HMI_H_

#define F_CPU 8000000UL
#include"lcd.h"
#include"uart.h"
#include<string.h>
#include"keypad.h"
#include<util/delay.h>
#include"common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NEW_PASSWORD    0x01
#define ready           0x02
#define COMPARE         0x03
#define MATCHED         0x04
#define NOT_MATCHED     0x05
#define WARNING         0x0B
#define OPEN_DOOR       0x07
#define FAIL            0x08
#define GATE_IS_OPEN    0x09
#define GATE_IS_CLOSE   0x0A
#define SAFE            0x0C
#define PASSWORD_SIZE   6
#define UART_BAUD_RATE  9600

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void main_option(void);

void get_initial_password(void);

void send_password(uint8 *password);

void get_password(uint8 *password);

void reset_password_option(void);

void open_door_option(void);



#endif /* HMI_H_ */
