# Copyright 2015 Florent Rotenberg.
#
# Author: Florent Rotenberg (florent.rotenberg@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# See http://creativecommons.org/licenses/MIT/ for more information.

PROJECTS = \
			 quad_encoder \
			 adc_temperature_vrefin \
			 adc_temp_tim_trig \
			 adc_pot_tim_trig \
			 lcd16x2_driver \
			 led_rgb_driver \
			 led_rgb_pwm_driver \
			 ledtoggle_template \
			 project_template \
			 semihosting_template \
			 swo_itm_printf_template

.PHONY: all_prj
all_prj:
	@$(foreach prj, $(PROJECTS), make -f $(prj)/Makefile all;)

.PHONY: clean_prj
clean_prj:
	@rm -rf build
	@make clean clean_libs

PACKAGES						= dummy_for_libs
TARGET						  = dummy_for_libs
NEWLIB_NANO					= enable
SEMIHOST						= disable
F_CRYSTAL      			= 8000000L

include libstm32f4/makefile.inc

			 

