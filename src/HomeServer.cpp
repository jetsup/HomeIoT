#include <HomeServer.hpp>

HomeServer::HomeServer(uint16_t port, HomeDHT *dht, HomeRTC *rtc,
                       HomeApplianceConfiguration *config)
    : AsyncWebServer(port), _port(port), _dht(dht), _rtc(rtc), _config(config) {
  // Serve the root page
  on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    // request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "Hello, world");
  });

  // ping request, returns 200
  on(String(String(HOME_SERVER_API_PATH) + "/ping/").c_str(), HTTP_GET,
     [](AsyncWebServerRequest *request) {
       AsyncJsonResponse *response = new AsyncJsonResponse();
       JsonObject root = response->getRoot();
       root["status"] = "ok";
       response->setLength();
       request->send(response);
     });

  // get the system devices being monitored
  on(String(String(HOME_SERVER_API_PATH) + "/stats/").c_str(), HTTP_GET,
     [this](AsyncWebServerRequest *request) {
       // send a JSON response
       AsyncJsonResponse *response = new AsyncJsonResponse();
       JsonObject root = response->getRoot();
       apiGetTemperature(_dht, CELSIUS, root);
       apiGetHumidity(_dht, root);
       apiGetTime(DateTime(_rtc->getEpoch()), root);
       apiAddApplianceData(_config, root, false);
       response->setLength();
       request->send(response);
     });

  // get all devices connected in the system
  on(String(String(HOME_SERVER_API_PATH) + "/devices/").c_str(), HTTP_GET,
     [this](AsyncWebServerRequest *request) {
       AsyncJsonResponse *response = new AsyncJsonResponse();
       JsonObject root = response->getRoot();

       apiAddApplianceData(_config, root, false);

       response->setLength();
       request->send(response);
     });

  // get all devices flagged as deleted
  on(String(String(HOME_SERVER_API_PATH) + "/devices/deleted/").c_str(),
     HTTP_GET, [this](AsyncWebServerRequest *request) {
       AsyncJsonResponse *response = new AsyncJsonResponse();
       JsonObject root = response->getRoot();

       apiAddApplianceData(_config, root, true);

       response->setLength();
       request->send(response);
     });

  //  post request to add a device
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/add/").c_str(), HTTP_POST,
      [](AsyncWebServerRequest *request) {}, NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        ArduinoJson::JsonDocument doc;
        ArduinoJson::DeserializationError error =
            deserializeJson(doc, data, len);

        DEBUG_PRINTF("Received JSON: ['%d']'%s'\n", len, data);

        if (error) {
          request->send(400, "application/json", "Invalid JSON Received");
          return;
        }

        DEBUG_PRINTF("KEY THERE: %d\n",
                     doc[CONFIG_APPLIANCE_NAME].is<String>());

        if (doc.containsKey(CONFIG_APPLIANCE_NAME) &&
            doc.containsKey(CONFIG_APPLIANCE_IS_DIGITAL) &&
            doc.containsKey(CONFIG_APPLIANCE_PIN)) {
          String name = doc[CONFIG_APPLIANCE_NAME];
          bool isDigital = doc[CONFIG_APPLIANCE_IS_DIGITAL];
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];

          _config->addAppliance(name, isDigital, pin);
          request->send(200, "application/json", "Device added");
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to change the value of the device
  on(
      String(String(HOME_SERVER_API_PATH) + "/devices/value/").c_str(),
      HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        ArduinoJson::JsonDocument doc;
        ArduinoJson::DeserializationError error =
            deserializeJson(doc, data, len);

        DEBUG_PRINTF("Received JSON: ['%d']'%s'\n", len, data);

        if (error) {
          request->send(400, "application/json", "Invalid JSON Received");
          return;
        }

        if (doc.containsKey(CONFIG_APPLIANCE_PIN) &&
            doc.containsKey(CONFIG_APPLIANCE_VALUE)) {
          int value = doc[CONFIG_APPLIANCE_VALUE];
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];

          DEBUG_PRINTF("Pin: '%d' -> '%d'\n", pin, value);

          HomeAppliance *appliance = _config->getAppliance(pin);
          DEBUG_PRINTF("Pin Key: %s\n", CONFIG_APPLIANCE_PIN);

          if (appliance == nullptr) {
            request->send(400, "application/json",
                          "The appliance does not exist");
          }

          appliance->setValue(value);
          _config->updateApplianceValue(pin, value);
          request->send(200, "application/json", "Appliance Value Updated");
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // Serve the CSS file
  //   on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
  //     request->send(LittleFS, "/style.css", "text/css");
  //   });

  // Serve the JavaScript file
  //   on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  //     request->send(LittleFS, "/script.js", "text/javascript");
  //   });

  AsyncWebServer::begin();
}
