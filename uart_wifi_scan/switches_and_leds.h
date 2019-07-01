/**
 * Configures the switches and leds that are in the Port F and
 * defines and API to used them.
 *
 * This file defines the API to use
 *
 * - Switch 1 - INPUT (It is located in the port PF4)
 * - Switch 2 - INPUT (It is located in the in the port PF0)
 * - RGB Leds - OUTPUT (They are located in the ports PF3 (Green), PF2(Blue) and PF1(Red))
 */

#ifndef SWICHES_AND_LEDS_H_
#define SWICHES_AND_LEDS_H_

#include <stdbool.h>

/** Colors that are supported by the RGB leds */
typedef enum {
	BLUE = 0x04,
	GREEN = 0x07,
	PINK = 0x06,
	RED = 0x02,
	NONE = 0,
	SKY_BLUE = 0x0C,
	WHITE = 0x0E,
	YELLOW = 0x0A,
} Color;

/** Initializes the switches and leds in the Port F. */
void initSwitchesAndLeds(void);

/** Returns true if the Switch 1 in port PF4 is pressed. */
bool isSwitch1Pressed(void);

/** Returns true if the Switch 1 in port PF0 is pressed. */
bool isSwitch2Pressed(void);

/** Toggle the RGB leds. */
void toggleLeds(Color color);

/** Turn on the RGB leds and displays the given color. */
void turnOnLeds(Color color);

/** Turn off the RGB leds. */
void turnOffLeds(void);

#endif // SWICHES_AND_LEDS_H_

