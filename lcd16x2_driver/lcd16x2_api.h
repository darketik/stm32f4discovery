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


#ifndef LCD16x2_API_H_
#define LCD16x2_API_H_

#include "stm32f4xx_hal.h"
#include "libstm32f4.h"

#define HD44780_CLEAR                          0x01

#define HD44780_HOME                           0x02

#define HD44780_ENTRY_MODE                     0x04
        #define HD44780_EM_SHIFT_CURSOR        0x00
        #define HD44780_EM_SHIFT_DISPLAY       0x01
        #define HD44780_EM_DECREMENT           0x00
        #define HD44780_EM_INCREMENT           0x02

#define HD44780_DISPLAY_ONOFF                  0x08
        #define HD44780_DISPLAY_OFF            0x00
        #define HD44780_DISPLAY_ON             0x04
        #define HD44780_CURSOR_OFF             0x00
        #define HD44780_CURSOR_ON              0x02
        #define HD44780_CURSOR_NOBLINK     	   0x00
        #define HD44780_CURSOR_BLINK           0x01

#define HD44780_DISPLAY_CURSOR_SHIFT 					 0x10
        #define HD44780_SHIFT_CURSOR           0x00
        #define HD44780_SHIFT_DISPLAY          0x08
        #define HD44780_SHIFT_LEFT             0x00
        #define HD44780_SHIFT_RIGHT            0x04

#define HD44780_FUNCTION_SET                   0x20
        #define HD44780_FONT5x7                0x00
        #define HD44780_FONT5x10               0x04
        #define HD44780_ONE_LINE               0x00
        #define HD44780_TWO_LINE               0x08
        #define HD44780_4_BIT                  0x00
        #define HD44780_8_BIT                  0x10

#define HD44780_CGRAM_SET                      0x40
#define HD44780_DDRAM_SET                      0x80

class Lcd {
	public:
		Lcd (GPIO_TypeDef *GpioBank, uint16_t RsPin, uint16_t RwPin, uint16_t EnPin, uint16_t Db4Pin, uint16_t Db5Pin, uint16_t Db6Pin, uint16_t Db7Pin) {
				this->GpioBank = GpioBank;
				this->RsPin = RsPin;
				this->RwPin = RwPin;
				this->EnPin = EnPin;
				this->Db7Pin = Db7Pin;
				this->Db6Pin = Db6Pin;
				this->Db5Pin = Db5Pin;
				this->Db4Pin = Db4Pin;
			}
		~Lcd () {}

		void Init (void);
		void Clear (void);
		void Print (const char *);
		void RetHome (void);

	private:
		GPIO_InitTypeDef  GPIO_InitStruct;
		GPIO_TypeDef *GpioBank;
		uint16_t RsPin;
		uint16_t RwPin;
		uint16_t EnPin;
		uint16_t Db4Pin;
		uint16_t Db5Pin;
		uint16_t Db6Pin;
		uint16_t Db7Pin;

		void WriteCmd (uint8_t);
		void WriteData (uint8_t);
		void WriteCmd4bits (uint8_t);
		uint8_t ReadBusyFlag (void);
		uint8_t ReadNibble (void);

		DISALLOW_COPY_AND_ASSIGN (Lcd);
};
#endif // LCD16x2_API_H_
