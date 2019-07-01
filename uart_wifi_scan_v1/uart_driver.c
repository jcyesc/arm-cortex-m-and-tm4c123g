/**
 *
 * Configure and provide and API for the UART interface.
 *
 * - Assumes a 50MHz bus, clock.
 */

#include <stdint.h>
#include <stdlib.h>

#include "tm4c123gh6pm.h"
#include "uart_driver.h"

/**
 * Initiates the ritual to configure the UART 0 port.
 */
void initUart(void) {
	SYSCTL_RCGCUART_R |= 0x0001; // Activate UART0
	SYSCTL_RCGCGPIO_R |= 0x0001; // Activate port A

	// Configure BAUD rate
	UART0_CTL_R &= ~0x0001;    // disable UART
	UART0_IBRD_R = 27;   // IBRD = int(50,000,000 / (16*115,200)) = int(27.1267)
	UART0_FBRD_R = 8;    //  FBRD = round(0.1267 * 64) = 8

	UART0_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
	UART0_CTL_R |= 0x00000301;  // enable RXE, TXE and UART

	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011; // uart
	GPIO_PORTA_AMSEL_R &= ~0x03;   // disable analog on PA1-0
	GPIO_PORTA_AFSEL_R |= 0x03;    // enable alt funct on PA1-0
	GPIO_PORTA_DEN_R |= 0x03;      // enable digital I/0 on PA-0.
}

void putChar(char data) {
	// Waits for buffer to be not full, then output
	while ((UART0_FR_R & 0x0020) != 0) {
		// wait until TXFF is 0
	}

	// Writes the data in the UART register, after that, the UART device
	// will send it over the wire.
	UART0_DR_R = data;
}

void putChars(const char *chars, size_t length) {
	uint32_t i;
	for (i = 0; i < length; i++) {
		putChar(*chars++);
	}
}

void putString(const char *string) {
	uint32_t i;
	for (i = 0; string[i] != 0; i++) {
		putChar(string[i]);
	}
}

