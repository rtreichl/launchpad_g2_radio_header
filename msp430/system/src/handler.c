///////////////////////////////////////////////////////////////////////////////////////////
///
/// \file handler.c
///
/// \brief handler.c calls all listed function after a given time
///
/// \date 25.03.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///////////////////////////////////////////////////////////////////////////////////////////

#include <system/handler.h>

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Handler for menu, RDS, time, the encoders and rsq
///
/// Steps in the while loop include:\n
///	1. Get new encoder values\n
///	2. Update display\n
///	3. Actualize menu\n
///	4. Actualize encoders\n
///	5. Update time\n
///	6. Update rsq\n
/// 7. Update backlight\n
///	8. Update RDS
///
/// \param	void
///
/// \retval	void
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

void handler (void)
{
	BUTTON button1, button2;
	button1.int_number_button = HEADER_TAST_INT;
	button2.int_number_button = BOARD_TAST_INT;
	button_create(&button1, BUTTON_PULL_DOWN);
	button_create(&button2, BUTTON_PULL_UP);
	//ENCODER encoder_left = {0, 0}, encoder_right = {0, 0};
	while(1) {
		/*encoder_1_update(&encoder_left);
		encoder_2_update(&encoder_right);
		if(*encoder_left.button != BUTTON_FREE || encoder_left.count != 0 || *encoder_right.button != BUTTON_FREE || encoder_right.count != 0 || timer_count[RADIO_TIMER_DISPLAY] >= RADIO_COUNT_DISPLAY) {
			if(timer_count[RADIO_TIMER_DISPLAY] >= RADIO_COUNT_DISPLAY) {
				radio.status.scroll_text++;
				if(radio.status.scroll_text == 78) {
					radio.status.scroll_text = 0;
				}
			}
			timer_count[RADIO_TIMER_DISPLAY] = 0;
			menu_handler(&encoder_left, &encoder_right);
		}*/
		if(timer_count[RADIO_TIMER_ENCODER] >= RADIO_COUNT_ENCODER) {
			timer_count[RADIO_TIMER_ENCODER] -= RADIO_COUNT_ENCODER;
			//encoder_interrupt2();
		}
		if(timer_count[0] >= 100) {
			timer_count[0] -= 100;
			//button_get(HEADER_TAST_INT, &button1);
			//button_get(BOARD_TAST_INT, &button2);
			fsm(&button1, &button2);
		}
//		if(timer_count[1] >= 1000) {
//			timer_count[1] -= 1000;
//			if(button1.short_pressed >= 1) {
//				P1OUT ^= BIT0;
//				button1.short_pressed--;
//			}
//		}

		/*
		if(timer_count[RADIO_TIMER_MINUTE] >= RADIO_COUNT_MINUTE) {
			timer_count[RADIO_TIMER_MINUTE] -= RADIO_COUNT_MINUTE;
			time_update();
		}
		if(timer_count[RADIO_TIMER_RSQ] >= RADIO_COUNT_RSQ) {
			rsq_update(&radio);
			timer_count[RADIO_TIMER_RSQ] -= RADIO_COUNT_RSQ;
		}
		if(timer_count[RADIO_TIMER_BACKLIGHT] >= RADIO_COUNT_BACKLIGHT) {
			radio_brightness(0);
			timer_count[RADIO_TIMER_BACKLIGHT] -= RADIO_COUNT_BACKLIGHT;
		}
		if(timer_count[RADIO_TIMER_RDS] >= RADIO_COUNT_RDS) {
			rds_update(&radio);
			timer_count[RADIO_TIMER_RDS] -= RADIO_COUNT_RDS;
		}*/
	}
}
