
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "math.h"

#ifdef __GNUC__
	/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
		 set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(uint8_t* ptr, int32_t len)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#define JPEG_START_ADDRESS       ((uint32_t)0xC0100000)
#define BUFFER_SIZE         ((uint32_t)0x0200)

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

__IO uint8_t UserButtonPressed = 0;

double circle_x = 0;
double circle_y = 0;
double angle = 0;
uint8_t color;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  HAL_UART_Transmit(&huart1, ptr, len, 20);
  return len;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t  status = LCD_OK;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	printf("Duvitech Systems\r\n");

  /* Configure LED1 and LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);

  /* Proceed to LTDC, DSI initialization and LCD screen initialization */
  status = BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	if(status != LCD_OK){
		Error_Handler();
	}

  /* Prepare using DMA2D the 800x480 LCD frame buffer to display background color black */
  /* and title of the example                                                           */
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font16);

  /* Print example description */
  BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Duvitech Demo Software", CENTER_MODE);

  /* QSPI device configuration */
  status = BSP_QSPI_Init();
  if (status == QSPI_NOT_SUPPORTED)
  {
    BSP_LCD_DisplayStringAt(0, 124, (uint8_t*)"QSPI NOT SUPPORTED", CENTER_MODE);
  }
  else if (status == QSPI_ERROR)
  {
    BSP_LCD_DisplayStringAt(0, 124, (uint8_t*)"QSPI Initialization : FAILED.", CENTER_MODE);
  }else{
		if(BSP_QSPI_EnableMemoryMappedMode() == QSPI_OK)
		{
			BSP_LCD_DisplayStringAt(0, 124, (uint8_t*)"UVC Playback Enabled", CENTER_MODE);
		}else{
			BSP_LCD_DisplayStringAt(0, 148, (uint8_t*)"Failed to read QSPI", CENTER_MODE);

		}
	}

  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

	BSP_LED_Off(LED1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		HAL_Delay(250);

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 7;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pins : PE4 PE3 PE2 PE1 
                           PE0 PE5 PE6 PE8 
                           PE9 PE11 PE14 PE7 
                           PE10 PE12 PE15 PE13 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1 
                          |GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8 
                          |GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_7 
                          |GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PG14 PG13 PG15 PG11 
                           PG12 PG10 PG9 PG8 
                           PG7 PG6 PG1 PG3 
                           PG2 PG0 PG5 PG4 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8 
                          |GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_3 
                          |GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PB8 PB4 PB3 PB9 
                           PB7 PB6 PB2 PB14 
                           PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_9 
                          |GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_2|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD7 PD6 PD0 PD5 
                           PD3 PD1 PD4 PD2 
                           PD15 PD10 PD14 PD9 
                           PD8 PD12 PD13 PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_5 
                          |GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_2 
                          |GPIO_PIN_15|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_9 
                          |GPIO_PIN_8|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PC12 PC11 PC10 PC13 
                           PC9 PC8 PC7 PC6 
                           PC3 PC1 PC2 PC4 
                           PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_13 
                          |GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6 
                          |GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4 
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA15 PA12 PA11 PA8 
                           PA1 PA0 PA4 PA2 
                           PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_8 
                          |GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_2 
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PJ13 PJ12 PJ14 PJ15 
                           PJ4 PJ5 PJ3 PJ2 
                           PJ0 PJ1 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2 
                          |GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

  /*Configure GPIO pins : PI8 PI4 PI3 PI2 
                           PI5 PI7 PI10 PI6 
                           PI1 PI12 PI9 PI0 
                           PI13 PI15 PI14 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2 
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_6 
                          |GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_9|GPIO_PIN_0 
                          |GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : PK7 PK6 PK5 PK4 
                           PK3 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4 
                          |GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

  /*Configure GPIO pins : PF0 PF1 PF2 PF3 
                           PF4 PF7 PF6 PF5 
                           PF10 PF9 PF8 PF12 
                           PF15 PF13 PF14 PF11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5 
                          |GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_12 
                          |GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PH15 PH13 PH14 PH5 
                           PH3 PH2 PH12 PH7 
                           PH9 PH11 PH6 PH8 
                           PH10 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_5 
                          |GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_7 
                          |GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_6|GPIO_PIN_8 
                          |GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void draw_circle(int Hcenter, int Vcenter, int radius,uint8_t color)
{

}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	BSP_LED_On(LED1);

  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
