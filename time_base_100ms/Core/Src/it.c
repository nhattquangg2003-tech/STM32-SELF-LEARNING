/*
 * it.c
 *
 *  Created on: Mar 2, 2026
 *      Author: Owner
 */
#include "main.h"

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

