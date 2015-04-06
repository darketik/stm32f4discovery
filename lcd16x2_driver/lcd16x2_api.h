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

template <uint16_t RsPin, uint16_t RwPin, uint16_t EnPin, uint16_t Db4Pin, uint16_t Db5Pin, uint16_t Db6Pin, uint16_t Db7Pin, uint8_t Width = 16, uint8_t Height = 2 >
class Lcd {
	public:
		Lcd () {}
		~Lcd () {}

		void Init (void);
		void Print (const char *);

	private:
		char buffer[LCD_HEIGHT][LCD_WIDTH];
		lcd_position_t lcd_position;

	DISALLOW_COPY_AND_ASSIGN (Lcd);
}
#endif // LCD16x2_API_H_
