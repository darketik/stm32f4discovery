
PROJECTS = \
			 adc_temperature_vrefin \
			 lcd16x2_driver \
			 led_rgb_driver \
			 led_rgb_pwm_driver \
			 ledtoggle_template \
			 project_template \
			 semihosting_template \
			 swo_itm_printf_template

.PHONY: all
all:
	make -f project_template/Makefile clean_all libs
	$(foreach prj, $(PROJECTS), make -f $(prj)/Makefile all;)

			 

