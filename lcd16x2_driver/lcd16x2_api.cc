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
// API Driver for lcd 16x4 display.

/** LCD Cursor control */
typedef enum  {
		CUROFF_BLKOFF = 0x00,  /**<  Cursor Off, Blinking Char Off */    
		CURON_BLKOFF  = 0x02,  /**<  Cursor On, Blinking Char Off */    
		CUROFF_BLKON  = 0x01,  /**<  Cursor Off, Blinking Char On */    
		CURON_BLKON   = 0x03   /**<  Cursor On, Blinking Char On */    
} lcd_cursorstate_t;

/** LCD Display control */
typedef enum {
		DISPOFF = 0x00,  /**<  Display Off */    
		DISPON  = 0x04   /**<  Display On */            
} lcd_displaystate_t;

/** LCD Backlight control */
typedef enum {
		LIGHTOFF,        /**<  Backlight Off */    
		LIGHTON          /**<  Backlight On */            
} lcd_backlightstate_t;

/** LCD Blink control (UDC), supported for some Controllers */
typedef enum {
		BLINKOFF,        /**<  Blink Off */    
		BLINKON          /**<  Blink On  */            
} lcd_blinkstate_t;

typedef struct {
		uint8_t row;
		uint8_t column;
} lcd_position_t;

void Lcd::Init (void) {
  GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* Init GPIO pins used for LCD interface */
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.Pin = RsPin;
	GPIO_InitStruct.Pin |= RwPin;
	GPIO_InitStruct.Pin |= EnPin;
	GPIO_InitStruct.Pin |= Db4Pin;
	GPIO_InitStruct.Pin |= Db5Pin;
	GPIO_InitStruct.Pin |= Db6Pin;
	GPIO_InitStruct.Pin |= Db7Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* Initialize state of the LCD pins */
  HAL_GPIO_WritePin(GPIOD, RsPin
										| RwPin
										| EnPin
										| Db4Pin
										| Db5Pin
										| Db6Pin
										| Db7Pin
										, GPIO_PIN_RESET); 

	/* TODO: Init Timer used to provide delay necessary for LCD control sequences
	 * Or SysTick and HAL_Delay can be used also 
	 * */
}
