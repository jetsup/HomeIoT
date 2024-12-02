#include <HomeMain.hpp>

const uint8_t _updateInterval = 1;
unsigned long lastDisplayUpdate = 0;

// ===================== Utility Functions Prototypes =====================
void updateDisplay(HomeDisplay *display, uint8_t updateInterval);

// ========================== Task Looper Functions ==========================
void monitorTaskLooper(void *parameter) {
  while (true) {
    delay(50);
  }
}

void mainTaskLooper(void *parameter) {
  while (true) {
    updateDisplay(display, _updateInterval);
  }
}

// ========================== Utility Functions ==========================
void updateDisplay(HomeDisplay *display, uint8_t updateInterval = 100) {
  if (millis() - lastDisplayUpdate < updateInterval) {
    return;
  }

  display->clear();
  display->drawText(0, 0, "Date: ", 1);
  display->drawText(40, 0, rtc->getDate().c_str(), 1);

  display->drawText(0, 10, "Time: ", 1);
  display->drawText(40, 10, rtc->getTime().c_str(), 1);

  display->drawLine(0, 20, 128, 20, WHITE);

  display->drawText(0, 25, "Temperature: ", 1);
  display->drawText(
      80, 25, String(String(dht.getTemperature(CELSIUS)) + "'").c_str(), 1);

  display->drawText(0, 35, "Humidity: ", 1);
  display->drawText(80, 35, String(String(dht.getHumidity()) + "%").c_str(), 1);

  if (WiFi.status() == WL_CONNECTED) {
    display->drawText(20, 55, String(WiFi.localIP().toString()).c_str(), 1);
  } else {
    display->drawText(30, 55, "WiFi Disconnected", 1);
  }

  display->display();

  lastDisplayUpdate = millis();
}

// ========================== Utility Functions ==========================
void initFileSystem() {
  if (!LittleFS.begin()) {
    DEBUG_PRINTLN("Failed to mount file system");
    return;
  }

  // Appliance Configuration File
  if (!LittleFS.exists(HOME_APPLIANCES_FILE)) {
    File file = LittleFS.open(HOME_APPLIANCES_FILE, "w", true);
    if (!file) {
      DEBUG_PRINTLN("Failed to create file");
      return;
    }
  }
}
