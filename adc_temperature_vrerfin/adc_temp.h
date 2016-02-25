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
// PWM mode
// RED - PC6
// GREEN - PC8
// BLUS - PC9

//TODO:
// - provide generic value for PWM period and PWM max duty cycle value
// - provide a function to ramp color intensity with a logarithm speed

#ifndef LED_RGB_H_
#define LED_RGB_H_

#include "stm32f4xx_hal.h"
#include "libstm32f4.h"
#include "system.h"

namespace led_rgb {

// TODO: define a enum in place of defines 
#define RED 0
#define GREEN 1
#define BLUE 2

class LedRgb {
	public:
		//+ LedRgb (uint32_t pwm_period, uint32_t red_dc, uint32_t green_dc, uint32_t blue_dc) { }
		LedRgb () { }
		~LedRgb () { }

		void Init (void);
		void SetColorIntensity (uint32_t color, uint8_t val);
		void On (uint32_t color);
		void Off (uint32_t color);
		
	private:
		TIM_HandleTypeDef TIMx_Handle;
		TIM_OC_InitTypeDef TIMx_OC_InitStruct;
	
		uint32_t pwm_period;
		uint32_t red_pwm_duty_cycle;
		uint32_t green_pwm_duty_cycle;
		uint32_t blue_pwm_duty_cycle;

		DISALLOW_COPY_AND_ASSIGN (LedRgb);
};

} // namespace led_rgb 

#endif // LED_RGB_H_
