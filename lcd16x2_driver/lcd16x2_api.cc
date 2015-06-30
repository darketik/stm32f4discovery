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

void Lcd::Init (void) {
	/* Init GPIO pins used for LCD interface */
	/* TODO find a way to make it generic to any GPIO bank */
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_InitStruct.Pin = RsPin | RwPin | EnPin | Db4Pin \
											| Db5Pin | Db6Pin | Db7Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	
  HAL_GPIO_Init(GpioBank, &GPIO_InitStruct);

	/* Initialize state of the LCD pins */
  HAL_GPIO_WritePin(GpioBank, RsPin	| RwPin	| EnPin \
														| Db4Pin | Db5Pin	| Db6Pin | Db7Pin
														, GPIO_PIN_RESET); 

	/* Wait 100ms for the internal initialisation of the display */
	HAL_Delay (100);

	/* Initialise display before busy flag is usable */
	WriteCmd4bits (0x03);
	HAL_Delay (5);

	WriteCmd4bits (0x03);
	/* TODO Shall be 100µs */
	HAL_Delay (5);

	WriteCmd4bits (0x03);
	HAL_Delay (5);

	/* Function set DL=0 - 4 bits */
	WriteCmd4bits (0x02);
	HAL_Delay (1);

	/* Function set DL=0 - 4 bits, N=1 - 2 lines, F=0 - 5*8 dots */
	WriteCmd (HD44780_FUNCTION_SET | HD44780_4_BIT | HD44780_TWO_LINE | HD44780_FONT5x7);

	/* Display Off */
	WriteCmd (HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF);

	/* Display Clear */
	Clear ();

	/* Entry mode set - Increment */
	WriteCmd (HD44780_ENTRY_MODE | HD44780_EM_INCREMENT);

	/* Display On */
	WriteCmd (HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON);
}

void Lcd::Clear (void) {
	WriteCmd (HD44780_CLEAR);
}

void Lcd::Print (const char * str) {
	while (*str) 
			WriteData (*str++);
}

void Lcd::RetHome () {
	WriteCmd (HD44780_HOME);
}

void Lcd::WriteCmd (uint8_t cmd) {
	HAL_GPIO_WritePin (GpioBank, RsPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, RwPin, GPIO_PIN_RESET);

	/* TODO replace by busy flag check */ 
	WriteCmd4bits (cmd >> 4);  	// high nibble
	WriteCmd4bits (cmd & 0x0F);	// low nibble
	while (ReadBusyFlag() & 0x80);
}

void Lcd::WriteData (uint8_t data) {
	HAL_GPIO_WritePin (GpioBank, RsPin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GpioBank, RwPin, GPIO_PIN_RESET);

	/* TODO replace by busy flag check */ 
	WriteCmd4bits (data >> 4);  	// high nibble
	WriteCmd4bits (data & 0x0F);	// low nibble
	while (ReadBusyFlag() & 0x80);
} 

/* Busy flag cannot be used */
void Lcd::WriteCmd4bits (uint8_t cmd) {
	HAL_GPIO_WritePin (GpioBank, EnPin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GpioBank, Db7Pin, (cmd & 0x08) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, Db6Pin, (cmd & 0x04) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, Db5Pin, (cmd & 0x02) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, Db4Pin, (cmd & 0x01) != 0 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, EnPin, GPIO_PIN_RESET);
}

uint8_t Lcd::ReadBusyFlag (void) {
	uint8_t status = 0;

	GPIO_InitStruct.Pin =  Db4Pin | Db5Pin | Db6Pin | Db7Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GpioBank, &GPIO_InitStruct);

	HAL_GPIO_WritePin (GpioBank, RsPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GpioBank, RwPin, GPIO_PIN_SET);
	status |= ReadNibble() << 4;
	status |= ReadNibble();

	HAL_GPIO_WritePin (GpioBank, RwPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin =  Db4Pin | Db5Pin | Db6Pin | Db7Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GpioBank, &GPIO_InitStruct);

	return status;
}

uint8_t Lcd::ReadNibble (void) {
	uint8_t val = 0;
	HAL_GPIO_WritePin (GpioBank, EnPin, GPIO_PIN_SET);
	val |= HAL_GPIO_ReadPin(GpioBank, Db4Pin);
	val |= HAL_GPIO_ReadPin(GpioBank, Db5Pin) << 1;
	val |= HAL_GPIO_ReadPin(GpioBank, Db6Pin) << 2;
	val |= HAL_GPIO_ReadPin(GpioBank, Db7Pin) << 3;
	HAL_GPIO_WritePin (GpioBank, EnPin, GPIO_PIN_RESET);
	return val;
}
