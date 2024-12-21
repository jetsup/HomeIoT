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

#ifdef HOME_HAS_IR_RECEIVER
HomeIRReceiver *irReceiver;
#endif  // HOME_HAS_IR_RECEIVER
#ifdef HOME_HAS_IR_SENDER
HomeIRSender *irSender;
#endif  // HOME_HAS_IR_SENDER

bool SET_DATE_TIME = false;
bool FORMAT_FILE_SYSTEM = false;

void setup() {
  Serial.begin(115200);

  // Mount the file system
  initFileSystem(FORMAT_FILE_SYSTEM);

  Wire.begin(I2C_SDA, I2C_SCL);

  rtc = new HomeRTC();

#ifdef HOME_HAS_IR_RECEIVER
  irReceiver = new HomeIRReceiver(HOME_IR_RECEIVER_PIN);
#endif  // HOME_HAS_IR_RECEIVER
#ifdef HOME_HAS_IR_SENDER
  irSender = new HomeIRSender(HOME_IR_SENDER_PIN);
#endif  // HOME_HAS_IR_SENDER

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
