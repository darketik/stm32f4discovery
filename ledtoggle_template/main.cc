/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define KEY_PRESSED     0x01
#define KEY_NOT_PRESSED 0x00
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
System sys;
__IO uint8_t UserButtonPressed = 0x00;

/* Private function prototypes -----------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  sys.init ();

  /* SysTick end of count event each ?? ms */
  SystemCoreClock = HAL_RCC_GetHCLKFreq();
  SysTick_Config(SystemCoreClock / 250);

  UserButtonPressed = 0x00;

  BSP_LED_Init(LED3);//orange
  BSP_LED_Init(LED4);//vert
  BSP_LED_Init(LED5);//rouge
  BSP_LED_Init(LED6);//bleu

  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);

  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  while (UserButtonPressed == KEY_NOT_PRESSED)
  {
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED3);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED4);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED6);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED5);
  }
  while (BSP_PB_GetState(BUTTON_KEY) != KEY_NOT_PRESSED) {}
  UserButtonPressed = 0x00;

  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
  while (UserButtonPressed == KEY_NOT_PRESSED)
  {
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED3);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED5);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED6);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED4);
  }
  while (BSP_PB_GetState(BUTTON_KEY) != KEY_NOT_PRESSED) {}
  UserButtonPressed = 0x00;

  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
  while (UserButtonPressed == KEY_NOT_PRESSED)
  {
	  BSP_LED_Toggle(LED3);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED6);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED4);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED5);
	  HAL_Delay(50);
  }
  while (BSP_PB_GetState(BUTTON_KEY) != KEY_NOT_PRESSED) {}
  UserButtonPressed = 0x00;

  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
  while (UserButtonPressed == KEY_NOT_PRESSED)
  {
	  BSP_LED_Toggle(LED3);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED3);
	  BSP_LED_Toggle(LED4);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED4);
	  BSP_LED_Toggle(LED6);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED6);
	  BSP_LED_Toggle(LED5);
	  HAL_Delay(50);
	  BSP_LED_Toggle(LED5);
  }
  while (BSP_PB_GetState(BUTTON_KEY) != KEY_NOT_PRESSED) {}
  UserButtonPressed = 0x00;
  BSP_LED_On(LED3);
  BSP_LED_On(LED5);
  BSP_LED_On(LED4);
  BSP_LED_On(LED6);

  /* Infinite loop */
  while (1)
  {
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == KEY_BUTTON_PIN) {
	    UserButtonPressed = 0x01;
	}
}

#ifdef __cplusplus
 extern "C" {
#endif 

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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
