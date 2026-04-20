/*
 * it.c
 *
 *  Created on: Mar 2, 2026
 *      Author: Owner
 */
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

extern RTC_HandleTypeDef hrtc;
void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
void RTC_Alarm_IRQHandler(void)
{
	HAL_RTC_AlarmIRQHandler(&hrtc);
}
