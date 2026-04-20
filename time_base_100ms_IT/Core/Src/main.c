/*
 * main.c
 *
 *  Created on: Mar 2, 2026
 *      Author: Owner
 */
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>


void SystemClockConfig(void);
void Error_handler(void);
void TIMER2_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer2;



int main (void)
{

	HAL_Init();
	SystemClockConfig();
	GPIO_Init();
	TIMER2_Init();

// lets start the timer2 In IT mode
	HAL_TIM_Base_Start_IT(&htimer2);

	while(1);
	return 0;




}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClockConfig(void)
{

}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_handler(void)
{
	while(1);
}
//
//
//
void TIMER2_Init(void)
{
	htimer2.Instance = TIM2;
	htimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer2.Init.Prescaler = 8000 - 1;
	htimer2.Init.Period = 100 -1;
	if (HAL_TIM_Base_Init(&htimer2) != HAL_OK)
	{
		Error_handler();
	}
}
//
//
//
void GPIO_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pin = GPIO_PIN_2;
	ledgpio.Pull = GPIO_NOPULL;
	ledgpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB,&ledgpio);
}
//
//
//
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
}
