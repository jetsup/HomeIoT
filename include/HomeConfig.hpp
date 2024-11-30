#pragma once

// DHT sensor
#define DHTTYPE DHT11  // DHT22 // DHT21
#define DHT_PIN 15
#define DHT_DELAY_MS 500

// I2C
#define I2C_SDA 21
#define I2C_SCL 22
#define I2C_FREQUENCY 100000

// Networking
#define HOME_NETWORK_CONNECTION_RETRY_DELAY_MS 5000

// NTP TIME
#define HOME_NTP_TIME_OFFSET 3 * 3600   // 3 hours
#define HOME_NTP_UPDATE_INTERVAL 10000  // 10s

// Display (OLED)
#define HOME_SCREEN_ADDRESS 0x3C
#define HOME_SCREEN_WIDTH 128
#define HOME_SCREEN_HEIGHT 64
#define HOME_OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
