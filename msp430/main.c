///----------------------------------------------------------------------------------------
///
/// \file main.c
///
/// \brief main.c includes main and all not used interrupt vectors
///
/// \date 18.06.2013
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

#include <stdint.h>
#include <system/handler.h>


///----------------------------------------------------------------------------------------
///
/// \brief	Main function
///
/// Main function contains following steps:\n
///	(1)Init the WatchDog\n
///	(2)Init the radio\n
///	(3)Run the handler\n
///
/// \param void
///
/// \retval	int
///
/// \remarks	The while loop is running in the handler!
///
///----------------------------------------------------------------------------------------

int main (void)
{
	WDTCTL = WDTPW + WDTHOLD;
	handler();
}

///----------------------------------------------------------------------------------------
///
/// \brief	Watchdog timer interrupt
///
/// \param void
///
/// \retval	void
///
/// \remarks Not used interrupt vector!
///
///----------------------------------------------------------------------------------------

#pragma vector=WDT_VECTOR
__interrupt void wdt(void){}

///----------------------------------------------------------------------------------------
///
/// \brief	Nested mask interrupt
///
/// \param void
///
/// \retval	void
///
/// \remarks Not used interrupt vector!
///
///----------------------------------------------------------------------------------------

#pragma vector=NMI_VECTOR
__interrupt void nmi(void){}

///----------------------------------------------------------------------------------------
///
/// \brief	Timer A1 interrupt
///
/// \param void
///
/// \retval	void
///
/// \remarks Not used interrupt vector!
///
///----------------------------------------------------------------------------------------

#pragma vector=TIMER1_A1_VECTOR
__interrupt void tim1(void){}

///----------------------------------------------------------------------------------------
///
/// \brief	Analog to digital converter interrupt
///
/// \param void
///
/// \retval	void
///
/// \remarks Not used interrupt vector!
///
///----------------------------------------------------------------------------------------


///----------------------------------------------------------------------------------------
///
/// \brief	Comparator interrupt
///
/// \param void
///
/// \retval	void
///
/// \remarks Not used interrupt vector!
///
///----------------------------------------------------------------------------------------

#pragma vector=COMPARATORA_VECTOR
__interrupt void comp(void){}
