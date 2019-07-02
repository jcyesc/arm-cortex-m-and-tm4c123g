#ifndef WIFI_SCAN_H_
#define WIFI_SCAN_H_

#include <stdint.h>
#include <stdlib.h>

#define NETWORK_ID_SIZE 6
#define SSID_LENGTH 32

/**
 * Represents a Wifi Scan. The Wifi Scan has:
 *
 * - Network name (SSI), consisting of up to 32 ASCII characters.
 * - Network ID (BSSID), consisting of 6 bytes
 * - Signal Strength (RSSI), consists of a number ranging from 20 to -100 in increments of 0.5.
 *
 * Note:
 * Instead of storing RSSI as a float that usually takes 4 bytes (depending of architecture), the
 * RSSI is stored as a uint8_t. The reason of this is because there are 240 different numbers between
 * 20 and -100 that we are interested (20, 19.5, 19, 18.5, .... , -99, -99,5, -100) and we can represent
 * each number as an index. For example:
 *
 * - The index 0 represents 20
 * - The index 40 represents 0
 * - The index 240 represents 100
 *
 * Note:
 * Depending of the architecture and how the elements in the struct are padded,
 * the layout of the struct in memory my take less or more space.
 *
 * Note:
 * Instead of having an array of 32 chars to store the SSID, we could have use
 * just a pointer to an contiguous area of memory that will have this layout
 * for every wifi scan (can be done also with an array of structs):
 *
 * 6 bytes for BSSID 1 byte for RSSI and a variable number of bytes from 1 up to 32 bytes for the SSI, next wifi scan here.
 *
 * This encoding uses less memory, however it is a little bit complex to implement.
 *
 * The current WifiScan struct uses 39 bytes to store all the information. If we have
 * a maximum of 200 scans, we will be using 7,800 bytes or 7.8KB. Assuming that in
 * average the SSI is 10 bytes (including the `\0` at the end of the string),
 * the layout from above will use 3400 bytes or 3.4KB ((6 bytes + 1 byte + 10 bytes) * 200)
 * which is half the size of the memory used by an array of WifiScans.
 */
typedef struct WifiScan {
	char ssid[SSID_LENGTH];
	uint8_t bssid[NETWORK_ID_SIZE];
	uint8_t rssi_index;
} WifiScanContent;

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
		const uint8_t **bssid_list, const float *rssi_list);

#endif /* WIFI_SCAN_H_ */

