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
//

#include "lcd16x2_api.h"

//+ /** LCD Cursor control */
//+ typedef enum  {
//+     CUROFF_BLKOFF = 0x00,  /**<  Cursor Off, Blinking Char Off */    
//+     CURON_BLKOFF  = 0x02,  /**<  Cursor On, Blinking Char Off */    
//+     CUROFF_BLKON  = 0x01,  /**<  Cursor Off, Blinking Char On */    
//+     CURON_BLKON   = 0x03   /**<  Cursor On, Blinking Char On */    
//+ } lcd_cursorstate_t;

//+ /** LCD Display control */
//+ typedef enum {
//+     DISPOFF = 0x00,  /**<  Display Off */    
//+     DISPON  = 0x04   /**<  Display On */            
//+ } lcd_displaystate_t;

//+ /** LCD Backlight control */
//+ typedef enum {
//+     LIGHTOFF,        /**<  Backlight Off */    
//+     LIGHTON          /**<  Backlight On */            
//+ } lcd_backlightstate_t;

//+ /** LCD Blink control (UDC), supported for some Controllers */
//+ typedef enum {
//+     BLINKOFF,        /**<  Blink Off */    
//+     BLINKON          /**<  Blink On  */            
//+ } lcd_blinkstate_t;

//+ typedef struct {
//+     uint8_t row;
//+     uint8_t column;
//+ } lcd_position_t;

template <GPIO_TypeDef *GpioBank, uint16_t RsPin, uint16_t RwPin, uint16_t EnPin, uint16_t Db4Pin, uint16_t Db5Pin, uint16_t Db6Pin, uint16_t Db7Pin, uint8_t Width, uint8_t Height>
void Lcd<GpioBank, RsPin, RwPin, EnPin, Db4Pin, Db5Pin, Db6Pin, Db7Pin, Width , Height>::Init (void) {
  GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* Wait 100ms for the internal initialisation of the display */
	HAL_Delay (100);

	/* Init GPIO pins used for LCD interface */
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.Pin = RsPin | RwPin | EnPin | Db4Pin \
											| Db5Pin | Db6Pin | Db7Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
  HAL_GPIO_Init(GpioBank, &GPIO_InitStruct);

	/* Initialize state of the LCD pins */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 

	/* Init Timer used to provide delay necessary for LCD control sequences
	 * Or SysTick and HAL_Delay can be used also 
	 * */
	HAL_Delay (1);

	/* Initialise display before busy flag is usable */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, Db4Pin | Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (5);

  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, Db4Pin | Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	/* TODO Shall be 100µs */
	HAL_Delay (1);

  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, Db4Pin | Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);

	/* Function set DL=0 - 4 bits */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);

	/* Function set DL=0 - 4 bits, N=1 - 2 lines, F=0 - 5*8 dots */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db7Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);

	/* Display Off */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db7Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);

	/* Display Clear */
	Clear ();

	/* Entry mode set - Increment - Display shift */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db6Pin	| Db4Pin | Db5Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);

	/* Display On - Cursor On */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db7Pin	| Db6Pin | Db5Pin | EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
}

template <GPIO_TypeDef *GpioBank, uint16_t RsPin, uint16_t RwPin, uint16_t EnPin, uint16_t Db4Pin, uint16_t Db5Pin, uint16_t Db6Pin, uint16_t Db7Pin, uint8_t Width, uint8_t Height>
void Lcd<GpioBank, RsPin, RwPin, EnPin, Db4Pin, Db5Pin, Db6Pin, Db7Pin, Width , Height>::Clear (void) {
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin \
														| Db7Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(GpioBank,  Db4Pin	| EnPin, GPIO_PIN_SET); 
	HAL_Delay (1);
  HAL_GPIO_WritePin(GpioBank, EnPin, GPIO_PIN_RESET); 
	HAL_Delay (1);
}
