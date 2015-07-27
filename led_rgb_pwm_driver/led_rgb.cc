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
#define TIMx_ARR 256 // PWM freq ~= 39kHz

#define LED_RGB_GPIOx GPIOC
#define LED_RGB_GPIOx_RED GPIO_PIN_6
#define LED_RGB_GPIOx_GREEN GPIO_PIN_8
#define LED_RGB_GPIOx_BLUE GPIO_PIN_9
#define LED_RGB_GPIOx_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE

namespace led_rgb {

void LedRgb::Init (void) {
	TIM_HandleTypeDef TIMx_Handle;
	TIM_OC_InitTypeDef TIMx_OC_InitStruct;

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

	TIMx_Handle.Instance = TIMx;
	TIMx_Handle.Init.Prescaler = uPrescaler;
	TIMx_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIMx_Handle.Init.Period = TIMx_ARR - 1; 
	TIMx_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_PWM_Init (&TIMx_Handle) != HAL_OK)
	{
		Error_Handler ();
	}

	TIMx_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIMx_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIMx_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	TIMx_OC_InitStruct.Pulse = 20; // CCR value for a TIMER channel
	if (HAL_TIM_PWM_ConfigChannel (&TIMx_Handle, &TIMx_OC_InitStruct, TIM_CHANNEL_1 | TIM_CHANNEL_3 | TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler ();
	}

  if (HAL_TIM_PWM_Start (&TIMx_Handle, TIM_CHANNEL_1 | TIM_CHANNEL_3 | TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler ();
	}

	/* Initialize state of the LCD pins */
	//+ Off ();

	/* Wait 100ms */
	HAL_Delay (100);
}

//+ void LedRgb::SetRed (uint8_t val) {
//+   HAL_GPIO_WritePin(LED_RGB_GPIOx, LED_RGB_GPIOx_RED, GPIO_PIN_RESET); 
//+ }

//+ void LedRgb::SetGreen (uint8_t val) {
//+   HAL_GPIO_WritePin(LED_RGB_GPIOx, LED_RGB_GPIOx_GREEN, GPIO_PIN_RESET); 
//+ }

//+ void LedRgb::SetBlue (uint8_t val) {
//+   HAL_GPIO_WritePin(LED_RGB_GPIOx, LED_RGB_GPIOx_BLUE, GPIO_PIN_RESET); 
//+ }

//+ void LedRgb::On (void) {
//+   HAL_GPIO_WritePin(LED_RGB_GPIOx, LED_RGB_GPIOx_RED | LED_RGB_GPIOx_GREEN | LED_RGB_GPIOx_BLUE, GPIO_PIN_RESET); 
//+ }

//+ void LedRgb::Off (void) {
//+   HAL_GPIO_WritePin(LED_RGB_GPIOx, LED_RGB_GPIOx_RED | LED_RGB_GPIOx_GREEN | LED_RGB_GPIOx_BLUE, GPIO_PIN_SET); 
//+ }


} // namespace led_rgb 

#ifdef __cplusplus
 extern "C" {
#endif 

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	TIMx_CLK_ENABLE ();
	LED_RGB_GPIOx_CLK_ENABLE ();
	
	GPIO_InitStruct.Pin = LED_RGB_GPIOx_RED | LED_RGB_GPIOx_GREEN | LED_RGB_GPIOx_BLUE;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(LED_RGB_GPIOx, &GPIO_InitStruct);
}

#ifdef __cplusplus
}
#endif
