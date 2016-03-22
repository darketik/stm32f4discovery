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
#define CHANGE_COLOR_DELAY 10

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
System sys;

// pot sensor with 5V supply
AdcPotTimTrig potsensor (3000.0f);

// Timer 3 tick base generator at 5kHz to trig ADC conversions on TRGO event
TimBase timer3 (TIM3, 84000000, 16800);

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
    void HAL_ADC_ErrorCallback (ADC_HandleTypeDef *hadc);
    void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* AdcHandle);
    void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim);
#ifdef __cplusplus
}
#endif

/* Private functions ---------------------------------------------------------*/
int main (void)
{
  char str_value_v[4];
  float32_t value_v;
  int value_i, value_q, value_r;
  //+ uint32_t value_adc;

  init ();
  BSP_LED_Toggle (LED3); //orange
  lcd.Print ("Pot voltage =");
  lcd.PrintXY ("V", 4, 1);


  /* Infinite loop */
  while (1) {
      value_v = potsensor.getVoltage ();
      //+ value_adc = potsensor.getAdcValue ();
      //+ sprintf (str_value_v, "%d", (int)value_adc);

      // convert float to int with 2 decimals
      value_i = (int)(value_v * 100.0f);
      value_q = value_i / 100;
      value_r = value_i % 100;
      sprintf (str_value_v, "%1d.%02d", value_q, value_r);
      lcd.PrintXY (str_value_v, 0, 1);
      HAL_Delay (100);
      //+ printf ("\033[A\033[2K\r");
      //+ printf ("\033[A\033[2K\r");
  }
}
#ifdef __cplusplus
extern "C" {
#endif 

    void init (void) {
	sys.init ();
	lcd.init ();
	timer3.init ();
	potsensor.init ();
	BSP_LED_Init (LED3); //orange
	BSP_LED_Init (LED4); //green
	BSP_LED_Init (LED5); //red
	BSP_LED_Init (LED6); //blue
    }

    void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* AdcHandle)
      {
	//+ BSP_LED_Toggle (LED4); //green
      }

    void HAL_ADC_ErrorCallback (ADC_HandleTypeDef *hadc)
      {
	BSP_LED_Toggle (LED5); //red
      }


    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
      {
	//+ BSP_LED_Toggle (LED6); //blue
      }

#ifdef  USE_FULL_ASSERT
    /**
     * @brief  Reports the name of the source file and the source line number
     *         where the assert_param error has occurred.
     * @param  file: pointer to the source file name
     * @param  line: assert_param error line source number
     * @retval None
     */
    void assert_failed (uint8_t* file, uint32_t line)
      {  
	/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	  {
	    Error_Handler ();
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
