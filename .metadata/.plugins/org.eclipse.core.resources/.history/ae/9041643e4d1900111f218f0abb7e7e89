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

//
//
//
void  HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	// 1. enable the clock for timer2
	if(htim->Instance == TIM2)
	{
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_TIM2_PARTIAL_2();  // CH3→PB10, CH4→PB11, CH1→PA0 ✅
	// 2.configure gpios to behave as timer2 channel 1,2,3 and 4
	// channel 1 pa0
	GPIO_InitTypeDef tim2ch1_gpio;
	tim2ch1_gpio.Pin = GPIO_PIN_0;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Pull = GPIO_NOPULL;
	tim2ch1_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);
	// channel 2 pa1
	GPIO_InitTypeDef tim2ch2_gpio;
	tim2ch2_gpio.Pin = GPIO_PIN_1;
	tim2ch2_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch2_gpio.Pull = GPIO_NOPULL;
	tim2ch2_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &tim2ch2_gpio);
	// channel 3 pb10
	GPIO_InitTypeDef tim2ch3_gpio;
	tim2ch3_gpio.Pin = GPIO_PIN_10;
	tim2ch3_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch3_gpio.Pull = GPIO_NOPULL;
	tim2ch3_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &tim2ch3_gpio);
	// channel 4 pb11
	GPIO_InitTypeDef tim2ch4_gpio;
	tim2ch4_gpio.Pin = GPIO_PIN_11;
	tim2ch4_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch4_gpio.Pull = GPIO_NOPULL;
	tim2ch4_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &tim2ch4_gpio);
	// nvic setting
	HAL_NVIC_SetPriority(TIM2_IRQn, 13, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
}
//
//
//
/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }

}
