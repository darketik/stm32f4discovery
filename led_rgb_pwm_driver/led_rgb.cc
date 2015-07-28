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
// API Driver for RGB LED.
//

#include "led_rgb.h"

#define TIMx TIM3 
#define TIMx_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE
#define TIMx_CLK 10000000
#define TIMx_PWM_PERIOD 256 // TIMER ARR - PWM freq ~= 39kHz (256)
#define TIMx_PWM_DEFAULT_DUTY_CYCLE 255 // CCR value for a TIMER channel - 50% 

#define LED_RGB_GPIOx GPIOC
#define LED_RGB_GPIOx_RED GPIO_PIN_6
#define LED_RGB_GPIOx_GREEN GPIO_PIN_8
#define LED_RGB_GPIOx_BLUE GPIO_PIN_9
#define LED_RGB_GPIOx_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE

namespace led_rgb {

void LedRgb::Init (void) {
	uint32_t uPrescaler = 0;

	// PWM config 
	// - freq is determined by ARR
	// - duty cycle is determined by CCRx
	//
	// To find prescaler value:
	// TIMx is on APB1 and APB1 clk_div = 4 
	// so TIMx CLK = 2 * APB1_CLK  (because apb1 clk_div not equal to 1)
	// or APB1_CLK = HCLK / 4
	// so TIMx_CLK = HCLK / 2 = SystemCoreClock / 2
	// Prescaler = (TIMx_CLK / TIMx counter clock) - 1
	//
	// PWM freq computation
	// PWM_Freq = TIMx_CLK / ARR
	SystemCoreClock = HAL_RCC_GetHCLKFreq ();
	uPrescaler = (uint32_t) ((SystemCoreClock / 2) / TIMx_CLK) - 1;

	// configure timer
	TIMx_Handle.Instance = TIMx;
	TIMx_Handle.Init.Prescaler = uPrescaler;
	TIMx_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIMx_Handle.Init.Period = TIMx_PWM_PERIOD - 1; 
	TIMx_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	// below function uses user definition of HAL_TIM_PWM_MspInit
	if (HAL_TIM_PWM_Init (&TIMx_Handle) != HAL_OK) {
		Error_Handler ();
	}

	// configure PWM channels
	TIMx_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIMx_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIMx_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	TIMx_OC_InitStruct.OCNPolarity = 0; // dummy to bypass assert_param check
	TIMx_OC_InitStruct.OCNIdleState = 0; // dummy to bypass assert_param check
	TIMx_OC_InitStruct.OCIdleState = 0; // dummy to bypass assert_param check
	TIMx_OC_InitStruct.Pulse = TIMx_PWM_DEFAULT_DUTY_CYCLE; 

	if (HAL_TIM_PWM_ConfigChannel (&TIMx_Handle, &TIMx_OC_InitStruct, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler ();
	}
	if (HAL_TIM_PWM_ConfigChannel (&TIMx_Handle, &TIMx_OC_InitStruct, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler ();
	}
	if (HAL_TIM_PWM_ConfigChannel (&TIMx_Handle, &TIMx_OC_InitStruct, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler ();
	}

	// start PWM channels generation
  if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler ();
	}
  if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler ();
	}
  if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler ();
	}
}

// TODO: find a way to change duty cycle at a precise end of PWM period
void LedRgb::SetColorIntensity (uint32_t color, uint8_t val) {
	switch (color) 
	{
		case (RED):
		{
			TIMx -> CCR1 = (uint32_t) val;
		}
		break;

		case (GREEN):
		{
			TIMx -> CCR3 = (uint32_t) val;
		}
		break;

		case (BLUE):
		{
			TIMx -> CCR4 = (uint32_t) val;
		}
		break;

		default: 
		break;
	}
}

void LedRgb::On (uint32_t color) {
	switch (color) 
	{
		case (RED):
		{
			if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_1) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		case (GREEN):
		{
			if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_3) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		case (BLUE):
		{
			if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_4) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		default: 
		break;
	}
}

void LedRgb::Off (uint32_t color) {
	switch (color) 
	{
		case (RED):
		{
			if (HAL_TIM_PWM_Stop (&TIMx_Handle, TIM_CHANNEL_1) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		case (GREEN):
		{
			if (HAL_TIM_PWM_Stop (&TIMx_Handle, TIM_CHANNEL_3) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		case (BLUE):
		{
			if (HAL_TIM_PWM_Stop (&TIMx_Handle, TIM_CHANNEL_4) != HAL_OK)
			{
				Error_Handler ();
			}
		}
		break;

		default: 
		break;
	}
}


} // namespace led_rgb 

#ifdef __cplusplus
 extern "C" {
#endif 

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	TIMx_CLK_ENABLE ();
	LED_RGB_GPIOx_CLK_ENABLE ();
	
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	GPIO_InitStruct.Pin = LED_RGB_GPIOx_RED | LED_RGB_GPIOx_GREEN | LED_RGB_GPIOx_BLUE;
	HAL_GPIO_Init(LED_RGB_GPIOx, &GPIO_InitStruct);
}

#ifdef __cplusplus
}
#endif
