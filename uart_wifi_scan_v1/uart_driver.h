/**
 * Configures the UART port and define the functions
 * to send characters using the UART serial interface.
 *
 * - Assumes a 50MHz bus, clock.
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdlib.h>

/**
 *
 * Initializes the UART 0.
 *
 * Note:
 *
 * The TM4C LaunchPad sends UART0 channel through the USB cable.
 * On the PC side of the cable, the serial channel becomes a
 * virtual COM port.
 *
 * In order to see the port in a Windows machine, go to:
 *
 * Device Manager/Ports (COM & LPT) Stellaris Virtual Serial Port(COM5)
 */
void initUart(void);

/** Sends a char using the UART 0. */
void putChar(char data);

/** Sends {@code length} charactes to the UART 0.
 *
 * @param chars The chars to be sent to the UART 0
 * @param length The number of characters to be sent to the UART 0.
 */
void putChars(const char *chars, size_t length);

/** Sends {@code string} to the UART 0. */
void putString(const char *string);

#endif // UART_DRIVER_H_

