///----------------------------------------------------------------------------------------
///
/// \file radio.h
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

#ifndef SYSTEM_FSM_H_
#define SYSTEM_FSM_H_

#include <stdint.h>
#include <driver/driver.h>
#include <settings/radio_configuration.h>

uint16_t radio_init(BUTTON *button_1, BUTTON *button_2);
uint16_t radio_seeking();
uint16_t radio_volume(uint8_t *volume, int8_t up_down);
uint16_t radio_mute();
uint16_t radio_main(BUTTON *button_1, BUTTON *button_2);

#if RADIO_HEADER_BUTTON_ONE == RADIO_SEEKING
#define RADIO_HEADER_BUTTON_ONE_FUNC()	radio_seeking()
#elif RADIO_HEADER_BUTTON_ONE == RADIO_VOLUME_UP
#define RADIO_HEADER_BUTTON_ONE_FUNC()	radio_volume(&volume, RADIO_VOLUME_UP)
#elif RADIO_HEADER_BUTTON_ONE == RADIO_VOLUME_DOWN
#define RADIO_HEADER_BUTTON_ONE_FUNC()	radio_volume(volume, RADIO_VOLUME_DOWN)
#elif RADIO_HEADER_BUTTON_ONE == RADIO_VOLUME_MUTE
#define RADIO_HEADER_BUTTON_ONE_FUNC() 	radio_mute()
#else
#error	"No function for header board button choosen!!!"
#endif

#if RADIO_HEADER_BUTTON_TWICE == RADIO_SEEKING
#define RADIO_HEADER_BUTTON_TWICE_FUNC()	radio_seeking()
#elif RADIO_HEADER_BUTTON_TWICE == RADIO_VOLUME_UP
#define RADIO_HEADER_BUTTON_TWICE_FUNC()	radio_volume(&volume, RADIO_VOLUME_UP)
#elif RADIO_HEADER_BUTTON_TWICE == RADIO_VOLUME_DOWN
#define RADIO_HEADER_BUTTON_TWICE_FUNC()	radio_volume(&volume, RADIO_VOLUME_DOWN)
#elif RADIO_HEADER_BUTTON_TWICE == RADIO_VOLUME_MUTE
#define RADIO_HEADER_BUTTON_TWICE_FUNC() 	radio_mute()
#else
#error	"No function for header board button choosen!!!"
#endif

#if RADIO_BOARD_BUTTON_ONE == RADIO_SEEKING
#define RADIO_BOARD_BUTTON_ONE_FUNC()		radio_seeking()
#elif RADIO_BOARD_BUTTON_ONE == RADIO_VOLUME_UP
#define RADIO_BOARD_BUTTON_ONE_FUNC()		radio_volume(&volume, RADIO_VOLUME_UP)
#elif RADIO_BOARD_BUTTON_ONE == RADIO_VOLUME_DOWN
#define RADIO_BOARD_BUTTON_ONE_FUNC()		radio_volume(&volume, RADIO_VOLUME_DOWN)
#elif RADIO_BOARD_BUTTON_ONE == RADIO_VOLUME_MUTE
#define RADIO_BOARD_BUTTON_ONE_FUNC()	 	radio_mute()
#else
#error	"No function for header board button choosen!!!"
#endif

#if RADIO_BOARD_BUTTON_TWICE == RADIO_SEEKING
#define RADIO_BOARD_BUTTON_TWICE_FUNC()		radio_seeking()
#elif RADIO_BOARD_BUTTON_TWICE == RADIO_VOLUME_UP
#define RADIO_BOARD_BUTTON_TWICE_FUNC()		radio_volume(&volume, RADIO_VOLUME_UP)
#elif RADIO_BOARD_BUTTON_TWICE == RADIO_VOLUME_DOWN
#define RADIO_BOARD_BUTTON_TWICE_FUNC()		radio_volume(&volume, RADIO_VOLUME_DOWN)
#elif RADIO_BOARD_BUTTON_TWICE == RADIO_VOLUME_MUTE
#define RADIO_BOARD_BUTTON_TWICE_FUNC() 	radio_mute()
#else
#error	"No function for header board button choosen!!!"
#endif

#endif /* SYSTEM_FSM_H_ */
