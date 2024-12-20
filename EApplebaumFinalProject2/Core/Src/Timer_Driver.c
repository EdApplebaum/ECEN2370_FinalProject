/*
 * Timer_Driver.c
 *
 *  Created on: Nov 19, 2024
 *      Author: 14408
 */
#include "Timer_Driver.h"
volatile uint32_t Game_Time = 0;

void Timer2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->CR1 &= ~(0x3 << CKD_OFFSET);
	TIM2->CR1 &= ~(0x1 << ARPE_OFFSET);
	TIM2->CR1 &= ~(0x3 << CMS_OFFSET);
	TIM2->CR1 &= ~(0x1 << DIR_OFFSET);
	TIM2->CR1 &= ~(0x1 << OPM_OFFSET);
	TIM2->CR1 &= ~(0x1 << UDIS_OFFSET);

	TIM2->CR1 |= TIM_CKD_1 << CKD_OFFSET;
	TIM2->CR1 |= TIM_ARPE_NO << ARPE_OFFSET;
	TIM2->CR1 |= TIM_CMS_UP << CMS_OFFSET;
	TIM2->CR1 |= TIM_CD_NO << DIR_OFFSET;
	TIM2->CR1 |= TIM_OPM_NO << OPM_OFFSET;
	TIM2->CR1 |= TIM_UDIS_ENABLE << UDIS_OFFSET;

	TIM2->CR2 &= ~(0x7 << MMS_OFFSET);
	TIM2->CR2 |= TIM_MMS_EN << MMS_OFFSET;

	TIM2-> DIER &= ~(0x1 << UIE_OFFSET);
	TIM2-> DIER |= TIM_UIE_ENABLE << UIE_OFFSET;

    TIM2->ARR = 82900000;

    TIM2->DIER |= TIM_DIER_UIE;
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

}
void Timer2_Start(void) {
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Timer2_Stop(void) {
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

void Timer2_Reset(void) {
    TIM2->CNT = 0;
}

uint32_t GetGameTime() {
	return Game_Time;
}
void TIM2_IRQHandler() {
	HAL_NVIC_DisableIRQ(TIM2_IRQn);
	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
    TIM2->SR &= ~(0x1);

    Game_Time++;
    TIM2->SR &= ~(0x1);
    TIM2->CNT =0;
    Timer2_Start();
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
