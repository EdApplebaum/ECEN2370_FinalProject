/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_


#include "stm32f4xx_hal.h"
#include "GameDriver.h"
//#include "LCD_Driver.h"
#include "Timer_Driver.h"
#include "Scheduler.h"


void ApplicationInit(void);
void LCD_Visual_Demo(void);
void Button_Init(void);
uint8_t Check_Start();

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */
