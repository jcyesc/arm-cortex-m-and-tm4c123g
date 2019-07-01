#include "wifi_scan.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "uart_driver.h"

#define MAX_WIFI_SCANS 200 // Defines the Maximum number of wifi scans.

/** Reserve space to store 200 Wifi Scans */
WifiScanContent wifi_scans[MAX_WIFI_SCANS];

/**
 * Converts the RSSI value to a given index between 0 and 240.
 * See table below for examples
 *
 * RSSI value | index
 * -------------------
 * 20         |    0
 * 19.5       |    1
 * 19         |    2
 *   ...      |    ...
 * -99.5      | 239
 * -100       | 240
 *
 * The formula that is used is below:
 *
 * 	index = -(rssi - 20)/0.5
 *
 * @param rssi_value The RSSI value that will be converted into
 * 					 an index.
 */
static uint8_t getRssiIndex(const float rssi_value) {
	uint8_t rssi_index;
	assert(rssi_value <= 20.0f && rssi_value >= -100.0f);

	rssi_index = -(rssi_value - 20) / 0.5f;
	return rssi_index;
}

/**
 * Synchronously sends the supplied data buffer to the MCU as a single complete
 * packet of data.
 *
 * @param data Buffer to transmit
 * @param len Number of bytes to send
 */
static void transmitPacket(const void *data, size_t len) {
	putString("\n===================================");
	putString("\nTransmitting packet");
	putString("\n===================================");

	putChars(data, len);

	putString("\n\nEnd of the transmission .....\n");
}

/**
 * Encodes a WiFi scan result into the format sent over the wire. You should
 * implement this to call transmitPacket() to send the data to the MCU once
 * it's formatted appropriately.
 *
 * @param ap_count  Number of access points in the scan result, and the size of the
 * 				    following list.
 * @param ssid_list List of SSIDs, given as an array of pointers null-terminated
 * 					ASCII strings.
 * @param bssid_list List of BSSIDs, given as an array of 6-byte arrays.
 * @param rssi_list  List of RSSIs
 */
void sendWifiScanResult(size_t ap_count, const char **ssid_list,
		const uint8_t **bssid_list, const float *rssi_list) {
	size_t data_size;
	uint8_t j;
	uint8_t i;
	void *data;
	WifiScanContent *wifi_scan;
	putString("\n===================================");
	putString("\nProcessing Wifi Scan");
	putString("\n===================================");

	data_size = ap_count * sizeof(WifiScanContent);
	// Cleaning the memory that will be used.
	memset(wifi_scans, 0, data_size);

	data = (void *) wifi_scans;
	wifi_scan = wifi_scans;
	for (i = 0; i < ap_count; i++) {
		assert(strlen(ssid_list[i]) <= SSID_LENGTH);
		strcpy(wifi_scan->ssid, ssid_list[i]);
		wifi_scan->rssi_index = getRssiIndex(rssi_list[i]);

		for (j = 0; j < NETWORK_ID_SIZE; j++) {
			wifi_scan->bssid[j] = bssid_list[i][j];
		}

		wifi_scan++;
	}
	putString("\nFinish encoding...\n");

	transmitPacket(data, data_size);
}

