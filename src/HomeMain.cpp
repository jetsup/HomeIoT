#include <HomeMain.hpp>

const uint8_t _updateInterval = 50;
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

  display->display();

  lastDisplayUpdate = millis();
}
