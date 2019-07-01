	
# Wifi Scan on ARM Cortex-M4 TM4C123G

Contains the implementation of the Wifi Scan using the
microntroller TM4C123G.

This project is done using Keil Micro Vision4 and is compiled using
the `--c99` flag.

## Goals
The objective of this project is to be able to transfer wifi scan data
from the microcontroller (MCU) to another device using the UART interface.

In order to use the interce, several modules have to be configured such as:

- Phase Lock Loop (PLL)
- Port F to enable UART serial communication

## Configuration

It configures the following modules:

- Systick
- Phase Lock Loop (PLL) 
- Configures the Port F to enable Input/Output
- Configures the UART 0
- Floating Point Unit (FPU) to enable float operations.

## Files provided by Keil IDE

- startup_TM4C123.S Contains the start up code
- tm4c123gh6pm.h Contains the addresses of the different ports

