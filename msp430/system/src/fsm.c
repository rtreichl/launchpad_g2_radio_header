///----------------------------------------------------------------------------------------
///
/// \file fsm.c
///
/// \brief 
///
/// \date 24.09.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------


#include <system/fsm.h>
#include <driver/driver.h>

void fsm(BUTTON *button_1, BUTTON *button_2)
{
	//button_1 = (uint16_t *) &encoder_1_count;
	//button_2 = (uint16_t *) &encoder_2_count;
	static uint8_t last_button_1 = 0, last_button_2 = 0, time_1 = 0, time_2 = 0;

	uint8_t test = 1;
	time_1++;
	time_2++;

	if(last_button_1 != 0 && time_1 >= 5/*ms*/) {
		time_1 = 0;
		switch(button_1->short_pressed) {
		case 1:
			while(test);
			break;
		case 2:
			while(test);
			break;
		case 3:
			while(test);
			break;
		default:
			button_1->short_pressed = 0;
		}
		last_button_1 = 0;
		button_1->short_pressed = 0;
	}
	if(last_button_2 != 0 && time_2 >= 5/*ms*/) {
		time_2 = 0;
		switch(button_2->short_pressed) {
		case 1:
			si4735_fm_seek_start(1);
			break;
		case 2:
			while(test);
			break;
		case 3:
			while(test);
			break;
		default:
			button_2->short_pressed = 0;
		}
		last_button_2 = 0;
		button_2->short_pressed = 0;
	}

	if(last_button_1 != button_1->short_pressed) {
		time_1 = 0;
		last_button_1 = button_1->short_pressed;
	}

	if(last_button_2 != button_2->short_pressed) {
		time_2 = 0;
		last_button_2 = button_2->short_pressed;
	}
}
