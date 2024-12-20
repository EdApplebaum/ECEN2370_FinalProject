/*
 * Timer_Driver.h
 *
 *  Created on: Nov 19, 2024
 *      Author: 14408
 */

#ifndef INC_TIMER_DRIVER_H_
#define INC_TIMER_DRIVER_H_
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"

#define CKD_OFFSET 8
#define TIM_CKD_1 0
#define TIM_CKD_2 1
#define TIM_CKD_4 2

#define ARPE_OFFSET 7
#define TIM_ARPE_NO 0
#define TIM_ARPE_YES 1

#define CMS_OFFSET 5
#define TIM_CMS_EDGE 0
#define TIM_CMS_DOWN 1
#define TIM_CMS_UP 2
#define TIM_CMS_Both 3

#define DIR_OFFSET 4
#define TIM_CD_YES 1
#define TIM_CD_NO 0

#define OPM_OFFSET 3
#define TIM_OPM_NO 0
#define TIM_OPM_YES 1

#define UDIS_OFFSET 1
#define TIM_UDIS_DISABLE 1
#define TIM_UDIS_ENABLE 0

#define MMS_OFFSET 4
#define TIM_MMS_RST 0
#define TIM_MMS_EN 1
#define TIM_MMS_UPD 2
#define TIM_MMS_CMPP 3
#define TIM_MMS_OC1 4
#define TIM_MMS_OC2 5
#define TIM_MMS_OC3 6
#define TIM_MMS_OC4 7

#define UIE_OFFSET 0
#define TIM_UIE_DISABLE 0
#define TIM_UIE_ENABLE 1

void Timer2_Init();
void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_Reset(void);
uint32_t GetGameTime();

#endif /* INC_TIMER_DRIVER_H_ */
