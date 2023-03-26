/****************************************************************************************
 * File Name: buzzer.c
 *
 * Description: source file for buzzer driver
 *
 * Author: Eng / Sohail Talaat
 *
 * *************************************************************************************/
#include"buzzer.h"
#include"gpio.h"

/***************************************************************************************
 *                      Functions Definitions
 ***************************************************************************************/

/*
 * Description :
 * function responsible to initial the pin of the buzzer
 * 1- make this pin as output pin
 * 2- make it zero output
 */
void buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * function responsible to turn the buzzer on.
 */

void buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * function responsible to turn the buzzer off.
 */
void buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

