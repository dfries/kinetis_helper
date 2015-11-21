/* Copyright (c) 2015 David Fries <David@Fries.net>  all rights reserved
 */

#ifndef __KINETIS_POWER_H__
#define __KINETIS_POWER_H__

inline void Disable_RTC()
{
	// disable 32.768 kHz oscillator
	RTC_CR &= ~RTC_CR_OSCE;
	// stop clocking RTC
	SIM_SCGC6 &= ~SIM_SCGC6_RTC;
}

inline void Disable_FTM1()
{
	// stop clocking FlexTimer1
	SIM_SCGC6 &= ~SIM_SCGC6_FTM1;
}

inline void Disable_Analog()
{
	// diasble voltage reference, (don't need to clear the entire register)
	VREF_SC &= ~(VREF_SC_VREFEN);
	SIM_SCGC6 &= ~SIM_SCGC6_ADC0;

	SIM_SCGC4 &= ~(SIM_SCGC4_VREF | SIM_SCGC4_CMP);
	// make sure it isn't calibrating,
	// DIABLE no response if executed
	// /* ADC0_SC3 &= ~ADC_SC3_CAL; */

	// TSI Toush Sense Input
	SIM_SCGC5 &= ~(SIM_SCGC5_TSI);
}

inline void Disable_Serial()
{
	// CMT Carrier Modulator Transmitter
	SIM_SCGC4 &= ~(SIM_SCGC4_UART2 | SIM_SCGC4_UART1 | SIM_SCGC4_UART0 |
		SIM_SCGC4_CMT);
}

inline void Disable_SysTick()
{
	// SysTick is documented in Cortex-M4 manual
	// Teensyduino sets it for 1Khz and irq systick_millis_count in irq
	SYST_CSR &= ~SYST_CSR_ENABLE;
}


#endif // __KINETIS_POWER_H__
