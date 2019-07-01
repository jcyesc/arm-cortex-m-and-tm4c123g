

#ifndef FLOATING_POINT_UNIT_H_
#define FLOATING_POINT_UNIT_H_

/**
 * Enables the floating point unit (FPU). This allows to
 * perform the following operations:
 *
 * - Add floats
 * - Divid floats
 * - Multiply floats
 * - Cast a float to int
 *
 * If the FPU is not enabled, the previous operations won't
 * be performed by the microcontroller and then the program
 * will hang.
 */

#include "../uart_wifi_scan/tm4c123gh6pm.h"

inline void initFloatingPointUnit(void){
   	NVIC_CPAC_R = 0x00F00000;
}

#endif /* FLOATING_POINT_UNIT_H_ */


