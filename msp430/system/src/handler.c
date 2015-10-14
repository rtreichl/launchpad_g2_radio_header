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
	BUTTON button_1, button_2;
	radio_init(&button_1, &button_2);
	while(1) {
		if(timer_count[RADIO_TIMER_MAIN] >= RADIO_COUNT_MAIN) {
			timer_count[RADIO_TIMER_MAIN] -= RADIO_COUNT_MAIN;
			radio_main(&button_1, &button_2);
		}
//		if(timer_count[1] >= 1000) {
//			timer_count[1] -= 1000;
//			if(button1.short_pressed >= 1) {
//				P1OUT ^= BIT0;
//				button1.short_pressed--;
//			}
//		}
	}
}
