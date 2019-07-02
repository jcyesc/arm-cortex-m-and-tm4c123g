#include "../uart_wifi_scan_v1/phase_lock_loop.h"

#include <stdint.h>

#include "../uart_wifi_scan_v1/tm4c123gh6pm.h"

/**
 * Define the value of divisor to initialize the
 * Phase Lock Loop to the desired frequency of 50 MHz.
 *
 * Bus frequency is 400MHz / (SYSDIV2 + 1) = 400MHz / (7 + 1) = 50 MHz
 */
#define SYSDIV2 7

/** 
 * Initiates ritual to get the clock from the Phase Lock Loop (PLL)
 *
 * The registers to configure the Phase-Lock-Loop are:
 *
 * Address     |  26-23  | 22        |   13    | 11     |  10-6   |  5-4    | Name
 * $400FE060   | SYSDIV  | USESYSDIV |  PWRDN  | BYPASS | XTAL    | OSCSRC  | SYSCTL_RCC_R
 * $400FE050   |    -    |     -     |     -   |    -   | PLLRIS  |    -    | SYSCTL_RIS_R
 *
 * Address     |     31  |    30     |  28-22  |   13   |    11   |  6-4    | Name
 * $400FE070   | USERCC2 |  DIV400   | SYSDIV2 | PWRDN2 | BYPASS2 | OSCSRC2 | SYSCTL_RCC2_R
 */
void initPhaseLockLoop() {
	// 0) Configures the system to use RCC2 for advanced features
	// such as 400 MHz PLL and non-integer System Clock Divisor
	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;

	// 1) Bypasses PLL while initializing
	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

	// 2) Selects the crystal value and oscillator source
	SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;      // Clears XTAL field
	SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;   // Configures for 16 MHz crystal
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M; // Clears oscillator source field
	SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO; // Configures for main oscillator source

	// 3) Activates PLL by clearing PWRDN
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

	// 4) Sets the desired system divider and the system divider least significant bit
	SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;          // Uses 400 MHz PLL
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) // Clears system clock divider field
	+ (SYSDIV2 << 22);                            // Configures for 50 MHz clock

	// 5) Waits for the PLL to lock by polling PLLLRIS
	while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0) {
	};

	// 6) Enables use of PLL by clearing BYPASS
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

