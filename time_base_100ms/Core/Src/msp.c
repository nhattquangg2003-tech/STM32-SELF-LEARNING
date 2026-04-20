/*
 * msp.c
 *
 *  Created on: Mar 2, 2026
 *      Author: Owner
 */

#include "main.h"
/**
  * @brief  Initialize the MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
  //Here will do low level processor specific inits.
  //1. Set up the priority grouping of the arm cortex mx processor
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  //2. Enable the required system exceptions of the arm cortex mx processor
  SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exceptions

  //3. configure the priority for the system exceptions
  HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
  HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
  HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
  /* USER CODE BEGIN MspInit 0 */

    /* USER CODE END MspInit 0 */

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init*/

    /** DISABLE: JTAG-DP Disabled and SW-DP Disabled
    */
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); // giữ lại SWD, chỉ tắt JTAG

    /* USER CODE BEGIN MspInit 1 */

    /* USER CODE END MspInit 1 */
}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	// 1. enable the clock for the timer2 peripherals
	__HAL_RCC_TIM2_CLK_ENABLE();

	// 2. enable IRQ of timer2
	HAL_NVIC_EnableIRQ(TIM2_IRQn);


	//3. set up the priority off timer2
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
}
