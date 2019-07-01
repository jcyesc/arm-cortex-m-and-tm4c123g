#include <stdbool.h>

#include "switches_and_leds.h"
#include "tm4c123gh6pm.h"

/** Initializes the switches and leds in the Port F. */
void initSwitchesAndLeds(void) {
	SYSCTL_RCGC2_R |= 0x00000020;     // 1) EnableS F clock

	// 2) Test if the F clock is ready
	while ((SYSCTL_RCGC2_R & 0x00000020) == 0) {
	}

	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 3) Unlocks PortF PF0
	GPIO_PORTF_CR_R = 0x1F;           // 4) Allows changes to PF4-0
	GPIO_PORTF_AMSEL_R = 0x00;        // 5) Disables analog function
	GPIO_PORTF_PCTL_R = 0x00000000;   // 6) GPIO clear bit PCTL
	GPIO_PORTF_DIR_R = 0x0E;          // 7) PF4,PF0 input, PF3,PF2,PF1 output
	GPIO_PORTF_AFSEL_R = 0x00;        // 8) No alternate function
	GPIO_PORTF_PUR_R = 0x11;          // 9) Enables pullup resistors on PF4,PF0
	GPIO_PORTF_DEN_R = 0x1F;          // 10) Enables digital pins PF4-PF0
}

/** Returns true if the Switch 1 in port PF4 is pressed. */
bool isSwitch1Pressed(void) {
	// Switches use Negative logic.
	return GPIO_PORTF_DATA_R & 0x10 ? false : true;
}

/** Returns true if the Switch 1 in port PF0 is pressed. */
bool isSwitch2Pressed(void) {
	// Switches use Negative logic.
	return GPIO_PORTF_DATA_R & 0x01 ? false : true;
}

/** Toggle the RGB leds. */
void toggleLeds(Color color) {
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^ color;
}

/** Turn on the RGB leds and displays the given color. */
void turnOnLeds(Color color) {
	GPIO_PORTF_DATA_R = color;
}

/** Turn off the RGB leds. */
void turnOffLeds(void) {
	GPIO_PORTF_DATA_R = NONE;
}

