#include <HomeMain.hpp>

TaskHandle_t mainTaskHandle;
TaskHandle_t monitorTaskHandle;

HomeDHT dht(DHT_PIN);
HomeRTC *rtc;
HomeNetworking *networking;
HomeDisplay *display;
HomeServer *server;
HomeApplianceConfiguration *applianceConfig;
std::vector<HomeAppliance *> appliances;

bool SET_DATE_TIME = false;

void setup() {
  Serial.begin(115200);

  // Mount the file system
  initFileSystem();

  Wire.begin(I2C_SDA, I2C_SCL);

  rtc = new HomeRTC();

  display = new HomeDisplay(&Wire);
  display->begin();

  networking =
      new HomeNetworking(String(HOME_WIFI_SSID), String(HOME_WIFI_PASSWORD));

  applianceConfig = new HomeApplianceConfiguration(&appliances, rtc);

  DEBUG_PRINTF("Config Data: %d\n", applianceConfig->printConfiguration());

  server = new HomeServer(HOME_SERVER_PORT, &dht, rtc, applianceConfig);

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

  xTaskCreatePinnedToCore(mainTaskLooper, "mainTask", 10000, NULL, 1,
                          &mainTaskHandle, 1);
  xTaskCreatePinnedToCore(monitorTaskLooper, "monitorTask", 10000, NULL, 1,
                          &monitorTaskHandle, 0);
}

void loop() {}
