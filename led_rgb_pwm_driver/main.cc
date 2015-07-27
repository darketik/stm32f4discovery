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

using namespace std;
using namespace led_rgb;
using namespace system;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CHANGE_COLOR_DELAY 500

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
System sys;

// RGB LED interface pin connection:
// PWM mode
// RED - PC6
// GREEN - PC8
// BLUS - PC9
LedRgb led_rgb_pixel;

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif 
void Init (void);

#ifdef __cplusplus
}
#endif

/* Private functions ---------------------------------------------------------*/
int main (void)
{
	Init ();

  /* Infinite loop */
  while (1)
  {
		//+ led_rgb_pixel.SetRed (0xff);
		//+ HAL_Delay (CHANGE_COLOR_DELAY);
		//+ led_rgb_pixel.Off ();
		//+ led_rgb_pixel.SetGreen (0xff);
		//+ HAL_Delay (CHANGE_COLOR_DELAY);
		//+ led_rgb_pixel.Off ();
		//+ led_rgb_pixel.SetBlue (0xff);
		//+ HAL_Delay (CHANGE_COLOR_DELAY);
		//+ led_rgb_pixel.Off ();
		//+ HAL_Delay (CHANGE_COLOR_DELAY);
		//+ led_rgb_pixel.On ();
		//+ HAL_Delay (CHANGE_COLOR_DELAY);
		//+ led_rgb_pixel.Off ();
  }
}
#ifdef __cplusplus
 extern "C" {
#endif 

void Init (void) {
	sys.Init ();
	led_rgb_pixel.Init ();
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
