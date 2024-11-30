#include <HomeMain.hpp>

HomeDHT dht(DHT_PIN);
HomeRTC *rtc;
HomeNetworking *networking;
HomeDisplay *display;

bool SET_DATE_TIME = false;

void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);

  rtc = new HomeRTC();

  display = new HomeDisplay(&Wire);
  display->begin();

  networking =
      new HomeNetworking(String(HOME_WIFI_SSID), String(HOME_WIFI_PASSWORD));

  if (SET_DATE_TIME) {
    while (!networking->isConnected()) {
      DEBUG_PRINT("#");
      networking->connect();
      delay(1000);
    }

    DEBUG_PRINTLN("Connected to WiFi");

    networking->ntpConnect();
    rtc->setDateTime(DateTime(networking->ntpGetEpoch()));
  }
}

void loop() {
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

  delay(50);
}
