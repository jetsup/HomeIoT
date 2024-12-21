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

// IR
#define HOME_CONFIGURE_IR true
#define HOME_HAS_IR_RECEIVER true  // requires HOME_CONFIGURE_IR to be true
#define HOME_HAS_IR_SENDER true    // requires HOME_CONFIGURE_IR to be true
#define HOME_IR_RECEIVER_PIN 14
#define HOME_IR_SENDER_PIN 12

// Display (OLED)
#define HOME_SCREEN_ADDRESS 0x3C
#define HOME_SCREEN_WIDTH 128
#define HOME_SCREEN_HEIGHT 64
#define HOME_OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)

// Server
#define HOME_SERVER_PORT 80
#define HOME_SERVER_API_PATH "/api/v1"

// File System
#define HOME_APPLIANCES_FILE "/config/appliances.json"
