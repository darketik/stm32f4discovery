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

// RGB LED interface pin connection:
// PWM mode
// RED - PC6
// GREEN - PC8
// BLUE - PC9
LedRgbPwm led_rgb_pixel(GPIOC, GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9,
						TIM3, GPIO_AF2_TIM3, 10000000,
						 256, 0, 0, 0);

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
	uint16_t red = 0;
	uint16_t green = 0;
	uint16_t blue = 0;

	init ();

  /* Infinite loop */
	// all the color panel
	//  fadin blue
	led_rgb_pixel.on (BLUE);
	for (blue = 0; blue < 256; blue++) {
		led_rgb_pixel.setColorDutyCycle (BLUE, 255 - blue);
		HAL_Delay (CHANGE_COLOR_DELAY);
		//+ if (blue > 128) blue++;
	}
	while (1) {
		//  fadin green --blue
		led_rgb_pixel.on (GREEN);
		for (green = 0; green < 256; green++) {
			led_rgb_pixel.setColorDutyCycle (GREEN, 255 - green);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (green > 128) green++;
		}
		//  fadout blue --green
		for (blue = 0; blue < 256; blue++) {
			led_rgb_pixel.setColorDutyCycle (BLUE, blue);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (blue < 128) blue++;
		}
		led_rgb_pixel.off (BLUE);
		//  fadin red --green
		led_rgb_pixel.on (RED);
		for (red = 0; red < 256; red++) {
			led_rgb_pixel.setColorDutyCycle (RED, 255 - red);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (red > 128) red++;
		}
		//  fadout green --red
		for (green = 0; green < 256; green++) {
			led_rgb_pixel.setColorDutyCycle (GREEN, green);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (green < 128) green++;
		}
		led_rgb_pixel.off (GREEN);
		//  fadin blue --red
		led_rgb_pixel.on (BLUE);
		for (blue = 0; blue < 256; blue++) {
			led_rgb_pixel.setColorDutyCycle (BLUE, 255 - blue);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (blue > 128) blue++;
		}
		//  fadin green --blue--red
		led_rgb_pixel.on (GREEN);
		for (green = 0; green < 256; green++) {
			led_rgb_pixel.setColorDutyCycle (GREEN, 255 - green);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (green > 128) green++;
		}
		// fadout red --blue
		for (red = 0; red < 256; red++) {
			led_rgb_pixel.setColorDutyCycle (RED, red);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (red < 128) red++;
		}
		led_rgb_pixel.off (RED);
		//  fadout green --blue
		for (green = 0; green < 256; green++) {
			led_rgb_pixel.setColorDutyCycle (GREEN, green);
			HAL_Delay (CHANGE_COLOR_DELAY);
			//+ if (green < 128) green++;
		}
		led_rgb_pixel.off (GREEN);
	}
}
#ifdef __cplusplus
 extern "C" {
#endif 

void init (void) {
	sys.init ();
  BSP_LED_Init(LED3); //orange
	led_rgb_pixel.init ();
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
