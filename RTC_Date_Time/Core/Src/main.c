/*
 * main.c
 *
 *  Created on: Mar 2, 2026
 *      Author: Owner
 */
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>  // ← cho va_list, va_start, va_end
// declare function
void SystemClockConfig(uint8_t clock_freq);
void Error_handler(void);
void GPIO_Init(void);
void MX_USART2_UART_Init(void);
void RTC_Init(void);
void  RTC_CalendarConfig(void);
// private variable
RTC_HandleTypeDef hrtc;
UART_HandleTypeDef huart2;


/**
  * @brief  Print a string to console over UART.
  * @param  format: Format string as in printf.
  * @param  ...: Additional arguments providing the data to print.
  * @retval None
  */
void printmsg(char *format,...)
{
  char str[80];

  /*Extract the the argument list using VA apis */
  va_list args;
  va_start(args, format);
  vsprintf(str, format,args);
  HAL_UART_Transmit(&huart2,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
  va_end(args);
}
// main
int main (void)
{

	HAL_Init();

	SystemClockConfig(SYS_CLOCK_FREQ_56_MHZ);

	GPIO_Init();

	RTC_Init();
		   RTC_CalendarConfig();

	MX_USART2_UART_Init();

    printmsg("This is RTC calendar Test Program\n");

	while (1)
	{

	}
	return 0;
}


void SystemClockConfig(uint8_t clock_freq)
{
	RCC_OscInitTypeDef Osc_Init = {0};
	RCC_ClkInitTypeDef Clock_Init = {0};

	// F103 dùng HSI 8MHz làm nguồn PLL
	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
	Osc_Init.HSIState = RCC_HSI_ON;
	Osc_Init.HSEState = RCC_HSE_ON;
	Osc_Init.HSIState = RCC_HSI_ON;
	Osc_Init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	Osc_Init.PLL.PLLState = RCC_PLL_ON;
	Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2; // HSI/2 = 4MHz vào PLL

	switch(clock_freq)
	{
	case SYS_CLOCK_FREQ_36_MHZ:
		// 4MHz × 9 = 36MHz
		Osc_Init.PLL.PLLMUL = RCC_PLL_MUL9;
		Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		Clock_Init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
		Clock_Init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
		Clock_Init.APB1CLKDivider = RCC_HCLK_DIV1; // APB1 max 36MHz → OK
		Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
		break;

	case SYS_CLOCK_FREQ_56_MHZ:
		// 4MHz × 14 = 56MHz
		Osc_Init.PLL.PLLMUL = RCC_PLL_MUL14;
		Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
				RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		Clock_Init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
		Clock_Init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
		Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2; // APB1 max 36MHz → 56/2=28MHz OK
		Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
		break;

	case SYS_CLOCK_FREQ_72_MHZ:
		Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		Osc_Init.HSEState = RCC_HSE_ON;
		Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE; // HSE 8MHz
		Osc_Init.PLL.PLLMUL = RCC_PLL_MUL9;         // 8MHz × 9 = 72MHz ✅
		Clock_Init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
		Clock_Init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
		Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;  // 36MHz
		Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;  // 72MHz
		break;

	default:
		return;
	}


	HAL_RCC_OscConfig(&Osc_Init);
	HAL_RCC_ClockConfig(&Clock_Init, FLASH_LATENCY_2);

	/*Configure the systick timer interrupt frequency (for every 1 ms) */
	uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
	HAL_SYSTICK_Config(hclk_freq/1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

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
//
//
//
void GPIO_Init(void)
{
	// LED PB2
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio = {0};
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pin = GPIO_PIN_2;
	ledgpio.Pull = GPIO_NOPULL;
	ledgpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &ledgpio);

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio_toggle = {0};
	gpio_toggle.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_toggle.Pin = GPIO_PIN_5;
	gpio_toggle.Pull = GPIO_NOPULL;
	gpio_toggle.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio_toggle);

	GPIO_InitTypeDef GpioBtn = {0};
	GpioBtn.Mode = GPIO_MODE_IT_FALLING;
	GpioBtn.Pin = GPIO_PIN_0;
	GpioBtn.Pull = GPIO_PULLDOWN;
	GpioBtn.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GpioBtn);

	// IRQ CONFIGURATIONS
	HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
	 HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */
}
//
//
//
//
//
//
void RTC_Init(void)
{
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = 39999;  // LSI 40kHz → 1Hz
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;

  if( HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_handler();
  }
}
//
//
//
void  RTC_CalendarConfig(void)
{
	RTC_TimeTypeDef RTCc_TimeInit;
	RTC_DateTypeDef RTC_DateInit;
	RTCc_TimeInit.Hours = 9;
	RTCc_TimeInit.Minutes = 18;
	RTCc_TimeInit.Seconds = 10;

	HAL_RTC_SetTime(&hrtc,&RTCc_TimeInit, RTC_FORMAT_BIN);

	RTC_DateInit.Date = 13;
	RTC_DateInit.Month = RTC_MONTH_MAY;
	RTC_DateInit.Year = 26;
	RTC_DateInit.WeekDay = RTC_WEEKDAY_FRIDAY;

	HAL_RTC_SetDate(&hrtc, &RTC_DateInit, RTC_FORMAT_BIN);
}
//
//
//
char *getDayofweek(uint8_t number)
{
	char *weekday[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

	return weekday[number-1];
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0)
	{

	RTC_TimeTypeDef RTC_TimeRead;
	RTC_DateTypeDef RTC_DateRead;

	HAL_RTC_GetTime(&hrtc,&RTC_TimeRead, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&RTC_DateRead, RTC_FORMAT_BIN);

	printmsg("Current Time is: %02d:%02d:%02d\r\n",RTC_TimeRead.Hours,RTC_TimeRead.Minutes,RTC_TimeRead.Seconds);
	printmsg("Current Date is:  %02d-%02d-%02d  <%s>\r\n",RTC_DateRead.Month,RTC_DateRead.Date,RTC_DateRead.Year,getDayofweek(RTC_DateRead.WeekDay));
}
}
