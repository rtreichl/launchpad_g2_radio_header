#ifndef RADIO_CONF_H_
#define RADIO_CONF_H_

#include <driver/external/include/si4735_cmd_prop.h>
#include <libs/time.h>

/* Define macros for version */

#define RADIO_VERSION_MAJOR	1
#define RADIO_VERSION_MINOR	00

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Radio Macros for gloabl configuration settings
///	@{
///
#define RADIO_VALID_SNR			15				///< Valid signal to noise ratio 10dB
#define RADIO_VALID_RSSI		20				///< Valid reseived signal strengh 25dBuV
#define RADIO_BOT_FREQ			0x222E 			///< Lowest possible freqency 87,50 MHz
#define RADIO_TOP_FREQ			0x2A30			///< Highest possible freqency 108,00 MHz
#define RADIO_SEEK_FREQ_SPACE	SKSPACE_10		///< Frequency step size 100 kHz
#define RADIO_CALBC1			CALBC1_16MHZ	///< MCU basis clock 16 MHz
#define RADIO_CALDCO			CALDCO_16MHZ	///< MCU basis clock 16 MHz
#define RADIO_DCO_FREQ			16				///< MCU basis clock 16 MHz
#define RADIO_MCLK				16				///< MCU basis clock 16 MHz
#define RADIO_SCLK				2				///< MCU slave clock 2 MHz
#define RADIO_I2C_FREQ			100				///< I2C clock 100 kHz
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Factory_State Macros for factory state
///	@{
///

#define RADIO_FACTORY_VOLUME		50			///< Normal volume 20%
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Factory_State Macros for factory state
///	@{
///
#define RADIO_VOLUME_UP				1
#define RADIO_VOLUME_DOWN			2
#define RADIO_VOLUME_MUTE			3
#define RADIO_SEEKING				4
#define RADIO_HEADER_BUTTON_ONE		RADIO_VOLUME_UP			///< Normal volume 20%
#define RADIO_HEADER_BUTTON_TWICE	RADIO_SEEKING			///< Normal volume 20%
#define RADIO_BOARD_BUTTON_ONE		RADIO_VOLUME_DOWN			///< Normal volume 20%
#define RADIO_BOARD_BUTTON_TWICE	RADIO_VOLUME_MUTE			///< Normal volume 20%
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Scroll Macros for scroll interfaces
///	@{
///

#define RADIO_VOLUME_MAX 		100				///< Volume max 100
#define RADIO_VOLUME_MIN 		0				///< Volume min 0
#define RADIO_VOLUME_STEP 		5				///< Volume step 2
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Button Macros for button states
///	@{
///
#define RADIO_BUTTON_INPUT_TIME	3				///< Value for time for doulbe tapping
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Timer Macros for timer use
///	@{
///
#define RADIO_TIMER_BUTTON		0				///< Timer for radio signal quality
#define RADIO_TIMER_MAIN		1				///< Timer for radio digital service
#define RADIO_TIMER_LED			2				///< Timer for minute counting
#define RADIO_TIMER_USED		3				///< Used counter
///
/// @}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Count Macros for time refresh rates
///	@{
///
#define RADIO_COUNT_MAIN		100				///< Count for encoder button execute underlying code every 10ms
#define	RADIO_COUNT_LED			60000			///< Count for minute counting execute underlying code every 60s
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////


///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///----------------------------------------------------------------------------------------
///
/// \defgroup States Macros for boolean values which are used for radio
///	@{
///
#define RADIO_TRUE 				1				///< Logical high or true is equal to a one
#define RADIO_FALSE 			0				///< Logical low or false is equal to a zero
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

#endif /* RADIO_CONF_H_ */
