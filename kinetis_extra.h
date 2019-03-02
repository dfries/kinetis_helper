/* Copyright (c) 2015 David Fries <David@Fries.net>  all rights reserved
 */


/* C++ operator overloads to make it easier to use, more type safe, and
 * not hurt performance when doing so.  Keep the design such that everything
 * in here is a compile time constant so it will compile down to a constant
 * and a register write.
 *
 * Assuming this header is correct using one of these values makes it so
 * you can read the source code and know the setting rather than having
 * to look up every register in the datasheet.
 */

/* MCUs are added as needed and this may very well be incomplete for the ones
 * that have been added.  So far,
 * __MK20DX128__  Teensy3.0
 */

#ifndef __KINETIS_EXTRA_H__
#define __KINETIS_EXTRA_H__

// FlexTimer enumerations to combine individual bits
namespace FTM
{
enum FTM_ENUMs
{
	// clock driving the counter
	// FTMx_SC &= ~FTM_SC_CLKS_MASK;
	// FTMx_SC |= FTM_SC_CLKS(value); // applies mask and shift
	clk_none = 0, // disables FTM
	clk_system,
	clk_fixed_freq,
	clk_external,

	// clock prescaler (after clock selected)
	// FTMx_SC &= ~FTM_SC_PS_MASK;
	// FTMx_SC |= FTM_SC_PS(value); // offset is zero, just applies mask
	prescale_1=0,
	prescale_2,
	prescale_4,
	prescale_8,
	prescale_16,
	prescale_32,
	prescale_64,
	prescale_128,

	// FTMx_CnSC
	// for Center Aligned mode,
	// output is cleared match up, set match down
	Center_PWM_Clear = FTM_CSC_ELSB,
	Center_PWM_Set = FTM_CSC_ELSA,
};
} // FMT

namespace PORT
{
enum PORT_ENUMs
{
	// interrupt
	// PORTx_PCRn &= ~PORT_PCR_IRQC_MASK;
	// PORTx_PCRn |= PORT_PCR_IRQC(value);

	// select from alternative port options
	// PORTx_PCRn &= ~PORT_PCR_MUX_MASK;
	// PORTx_PCRn |= PORT_PCR_MUX(value);
	MUX_ALT_0 = 0,
	MUX_ALT_1,
	MUX_ALT_2,
	MUX_ALT_3,
	MUX_ALT_4,
	MUX_ALT_5,
	MUX_ALT_6,
	MUX_ALT_7,
	// known alternatives
	MUX_ALT_disabled = MUX_ALT_0,
	MUX_ALT_GPIO = MUX_ALT_1,
	MUX_ALT_FMT0_CH = MUX_ALT_4, // true for outside pins, not back
	MUX_ALT_FMT1_CH = MUX_ALT_3,
};
}

// SCB_SCR System Control Register
// set even disabled interrupts can wake from WFE
#ifndef SCB_SCR_SEVONPEND
#define SCB_SCR_SEVONPEND ((uint8_t)0x10) 
#endif
// set goes to deep sleep (stop) for low power mode, not set sleep (wait)
#ifndef SCB_SCR_SLEEPDEEP
#define SCB_SCR_SLEEPDEEP ((uint8_t)0x04)
#endif
// set returns to sleep after leaving an interrupt (for empty main loop)
#ifndef SCB_SCR_SLEEPONEXIT
#define SCB_SCR_SLEEPONEXIT ((uint8_t)0x02)
#endif

// SMC_PMSTAT Power Mode Status Register
// upper bit is reserved
#define SMC_PMSTAT_MASK 0x7f

// SMC_PMCTRL Poer Mode Control Register
#define SMC_PMCTRL_NORMAL_RUN 0x20
// Very Low Power Run
#define SMC_PMCTRL_VLPR 0x40

#endif // __KINETIS_EXTRA_H__
