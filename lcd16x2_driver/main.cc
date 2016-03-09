// Copyright 2015 Florent Rotenberg.
//
// Author: Florent Rotenberg (florent.rotenberg@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
System sys;

// LCD interface pin connection:
// 4 - RS 		GPIO_PIN_7
// 5 - R/W		GPIO_PIN_8
// 6 - EN 		GPIO_PIN_9
// 11 - DB4		GPIO_PIN_10
// 12 - DB5		GPIO_PIN_11
// 13 - DB6		GPIO_PIN_12
// 14 - DB7		GPIO_PIN_13
Lcd lcd (GPIOE, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13);

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif 
void init (void);

#ifdef __cplusplus
}
#endif

/* Private functions ---------------------------------------------------------*/
int main (void)
{
	init ();

  /* Infinite loop */
  while (1)
  {
		lcd.Clear ();
		lcd.Print("Bonjour !! ");
		lcd.PrintXY("Hello /-\\|", 0, 1);

		HAL_Delay (3000);

		lcd.Clear ();
		lcd.Locate (1, 0);
		lcd.Print("STM32F4 Tests");

		uint32_t i;
		for (i=0; i<1000; ++i) {
			lcd.Locate (1, 1);
			lcd.ProgressBar(i, 1000-1, 14);
			HAL_Delay (5);
		}
  }
}

#ifdef __cplusplus
 extern "C" {
#endif 

void init (void) {
	sys.init ();
	lcd.init ();
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
