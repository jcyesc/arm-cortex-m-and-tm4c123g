#include <stdint.h>

#include "../uart_wifi_scan/tm4c123gh6pm.h"

/**
 * Configures the SysTick and defines the functions to wait
 * for a certain number of clock cycles.
 *
 * - Assumes a 50MHz bus, clock.
 * - Every instruction takes 1/50MHz = 20ns to be executed.
 * - Uses busy wait
 *
 * The registers to control the SysTick Timer are:
 *
 * Address     |  31-24  | 23-17 |   16    | 15-3 |    2     |    1   |   0     | Name
 * $E000E010   |    0    |    0  |  COUNT  |   0  | CLK_SRC  | INTEN  |  ENABLE | NVIC_ST_CTRL_R
 * $E000E014   |    0    |               24-bit RELOAD value                    | NVIC_ST_RELOAD_R
 * $E000E018   |    0    |      24-bit CURRENT value of SysTick counter         | NVIC_ST_CURRENT_R
 */

void initSystick(void) {
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
	NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
	NVIC_ST_CURRENT_R = 0;                // any write to current clears it
	// enable SysTick with core clock
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE + NVIC_ST_CTRL_CLK_SRC;
}

void wait20ns(uint32_t number_of_20_ns) {
	volatile uint32_t elapsed_time;
	uint32_t start_time = NVIC_ST_CURRENT_R;
	do {
		elapsed_time = (start_time - NVIC_ST_CURRENT_R) & NVIC_ST_RELOAD_M;
	} while (elapsed_time <= number_of_20_ns);
}

void wait10ms(uint32_t number_of_10_ms) {
	uint32_t i;
	for (i = 0; i < number_of_10_ms; i++) {
		// 10,000,000 ns = 10 ms
		// 10,000,000 ns/20 ns = 500,000
		wait20ns(500000);  // wait 10ms (assumes 50 MHz clock)
	}
}

