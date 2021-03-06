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

// quadratic encoder with:
// PB6: TIM4 ch1
// PB7: TIM4 ch2
// PA14: TIM2 CH1
// PB3:  TIM2 CH2
// PB4: TIM3 CH1
// PB5: TIM3 CH2
QuadEncoder q_enc (GPIOB, 
		   GPIO_PIN_4,
		   GPIO_PIN_5,
		   GPIO_AF2_TIM3,		   
		   DMA1,
		   DMA1_Stream4,
		   DMA_CHANNEL_5,
		   DMA1_Stream4_IRQn,
		   TIM3,
		   0x10000,
		   84000000);

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
  lcd.Print ("Quad Encoder =");

  /* Infinite loop */
  while (1) { }
}	




#ifdef __cplusplus
extern "C" {
#endif 

    void init (void) {
	sys.init ();
	BSP_LED_Init (LED3); //orange
	BSP_LED_Init (LED4); //green
	BSP_LED_Init (LED5); //red
	BSP_LED_Init (LED6); //blue
	lcd.init ();
	q_enc.init ();
	BSP_LED_Toggle (LED3); //orange
    }



    void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef *htim) {
	uint32_t _pos;
	char str_tim_cnt[3];

	_pos = q_enc.getPosition ();
	sprintf (str_tim_cnt, "%03d", (uint16_t)_pos);
	lcd.PrintXY (str_tim_cnt, 0, 1);
    }


    void HAL_TIM_ErrorCallback (TIM_HandleTypeDef *htim) {
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

