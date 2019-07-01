/**
 * Configures the SysTick and defines the functions to wait
 * for a certain number of clock cycles.
 *
 * - Assumes a 50MHz bus, clock.
 * - Uses busy wait
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

/** Initialize SysTick with busy wait running at bus clock. */
void initSystick(void);

/**
 * Waits 20ns * {@code numberOf20ns}. It uses busy waiting.
 *
 * Note:
 * 		The CPU is running at 50MHz clock.
 * 		Every instruction takes 1/50MHz = 20ns to be executed.
 */
void wait20ns(uint32_t number_of_20_ns);

/** Waits 10ms * {@code numberOf10ms}. It uses busy waiting. */
void wait10ms(uint32_t number_of_10_ms);

#endif // SYSTICK_H_

