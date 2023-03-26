/****************************************************************************************
 * File Name: buzzer.h
 *
 * Description: header file for buzzer driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID  PORTD_ID
#define BUZZER_PIN_ID   PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * function responsible to initial the pin of the buzzer
 * 1- make this pin as output pin
 * 2- make it zero output
 */
void buzzer_init(void);
/*
 * Description :
 * function responsible to turn the buzzer on.
 */
void buzzer_on(void);
/*
 * Description :
 * function responsible to turn the buzzer off.
 */
void buzzer_off(void);

#endif /* BUZZER_H_ */
