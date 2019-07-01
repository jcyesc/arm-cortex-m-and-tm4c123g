#include <string.h>
#include "phase_lock_loop.h"
#include "switches_and_leds.h"
#include "systick.h"
#include "tm4c123gh6pm.h"
#include "uart_driver.h"
#include "wifi_scan.h"

const size_t kAccessPointCount = 2;
const char *ssid_list[kAccessPointCount] = { "letsethe", "abcdd" };
const uint8_t bssid1[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
const uint8_t bssid2[6] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
const uint8_t *bssid_list[kAccessPointCount] = { bssid1, bssid2 };
const float rssi_list[kAccessPointCount] = { -48.0f, -50.5f };

int main(void);

void SystemInit(void) {
	main();
}

int main(void) {
	volatile unsigned long delay = 1;
	initPhaseLockLoop();
	initSystick();
	initUart();
	initSwitchesAndLeds();

	while (1) {
		if (isSwitch1Pressed()) {
			toggleLeds(PINK);
			delay = 50; // 500 ms second
			sendWifiScanResult(kAccessPointCount, ssid_list, bssid_list,
					rssi_list);
		} else {
			turnOnLeds(SKY_BLUE);
			delay = 1;
		}

		// It is necessary to wait a few micro seconds to avoid the bouncing.
		wait10ms(delay);
	}
}

