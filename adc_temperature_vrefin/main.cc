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

// STM32F407 temperature sensor 
AdcTemp tempsensor (ADC1, 
		    ADC_CHANNEL_TEMPSENSOR, 
		    ADC_SAMPLETIME_112CYCLES,
		    DMA2,
		    DMA2_Stream0,
		    DMA_CHANNEL_0,
		    DMA2_Stream0_IRQn);

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif 
    void init (void);
    void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* AdcHandle);
    void HAL_ADC_ErrorCallback (ADC_HandleTypeDef *hadc);
#ifdef __cplusplus
}
#endif

/* Private functions ---------------------------------------------------------*/
int main (void)
{
  float32_t temp_c;
  int temp_i, temp_q, temp_r;
  uint32_t temp_adc;

  init ();
  BSP_LED_Toggle (LED3); //orange
  printf ("Measure chip temperature:\n");

  /* Infinite loop */
  while (1) {
      temp_c = tempsensor.getTemp ();
      temp_adc = tempsensor.getAdcValue ();

      // convert float to int with 2 decimals
      temp_i = (int)(temp_c * 100.0f);
      temp_q = temp_i / 100;
      temp_r = temp_i % 100;
      printf ("%d.%02d\n", temp_q, temp_r);
      printf ("%d\n", (int)temp_adc);
      HAL_Delay(500);
      printf ("\033[A\033[2K\r\033[A\033[2K\r");
  }
}
#ifdef __cplusplus
extern "C" {
#endif 

    void init (void) {
	sys.init ();
	BSP_LED_Init (LED3); //orange
	BSP_LED_Init (LED5); //red
	BSP_LED_Init (LED4); //green
	tempsensor.init ();
    }

    void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* AdcHandle)
      {
	BSP_LED_Toggle (LED4); //green
      }


    void HAL_ADC_ErrorCallback (ADC_HandleTypeDef *hadc)
      {
	BSP_LED_Toggle (LED5); //red
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
