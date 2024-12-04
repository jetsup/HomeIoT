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

  // post request to delete all the devices
  on(
      String(String(HOME_SERVER_API_PATH) + "/devices/reset/").c_str(),
      HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        DEBUG_PRINTLN("Reseting the system...");

        ArduinoJson::JsonDocument doc;
        ArduinoJson::DeserializationError error =
            deserializeJson(doc, data, len);

        DEBUG_PRINTF("Received JSON: ['%d']'%s'\n", len, data);

        if (error) {
          request->send(400, "application/json", "Invalid JSON Received");
          return;
        }

        if (doc.containsKey(CONFIG_APPLIANCE_RESET)) {
          _config->reset();

          request->send(200, "application/json", "System Reset Successful");
          DEBUG_PRINTLN("System reset successful...");
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to get the device with a specific pin in json
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/").c_str(), HTTP_GET,
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

        if (doc.containsKey(CONFIG_APPLIANCE_PIN)) {
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];
          HomeAppliance *appliance = _config->getAppliance(pin);

          if (appliance == nullptr) {
            request->send(400, "application/json",
                          "The appliance does not exist");
            DEBUG_PRINTF("Appliance with pin [%d] does not exist...\n", pin);
            return;
          }

          AsyncJsonResponse *response = new AsyncJsonResponse();
          JsonObject root = response->getRoot();
          //   root["name"] = appliance->getName();
          root["is_digital"] = appliance->isDigital();
          root["pin"] = appliance->getPin();
          root["value"] = appliance->getValue();
          response->setLength();
          request->send(response);
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
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

        if (doc.containsKey(CONFIG_APPLIANCE_NAME) &&
            doc.containsKey(CONFIG_APPLIANCE_IS_DIGITAL) &&
            doc.containsKey(CONFIG_APPLIANCE_PIN)) {
          String name = doc[CONFIG_APPLIANCE_NAME];
          String category = doc[CONFIG_APPLIANCE_CATEGORY];
          bool isDigital = doc[CONFIG_APPLIANCE_IS_DIGITAL];
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];

          if (_config->getAppliance(pin) != nullptr) {
            request->send(400, "application/json",
                          "The appliance already exists");
            return;
          }

          _config->addAppliance(name, category, isDigital, pin);
          request->send(200, "application/json", "Device added");
          DEBUG_PRINTF("%s connected to pin [%d]...\n", name, pin);
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to change the value of the device
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/value/").c_str(),
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

          if (appliance == nullptr) {
            request->send(400, "application/json",
                          "The appliance does not exist");
            DEBUG_PRINTF("Appliance with pin [%d] does not exist...\n", pin);
            return;
          }

          appliance->setValue(value);
          _config->updateApplianceValue(pin, value);
          request->send(200, "application/json", "Appliance Value Updated");
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to update the appliance
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/update/").c_str(),
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
            (doc.containsKey(CONFIG_APPLIANCE_NAME) &&
             doc.containsKey(CONFIG_APPLIANCE_IS_DIGITAL))) {
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];
          String name = doc[CONFIG_APPLIANCE_NAME];
          String category = doc[CONFIG_APPLIANCE_CATEGORY];
          int value = doc[CONFIG_APPLIANCE_VALUE];
          bool isDigital = doc[CONFIG_APPLIANCE_IS_DIGITAL];
          HomeAppliance *appliance = _config->getAppliance(pin);

          if (appliance == nullptr) {
            request->send(400, "application/json",
                          "The appliance does not exist");
            DEBUG_PRINTF("Appliance with pin [%d] does not exist...\n", pin);
            return;
          }

          _config->updateAppliance(pin, name, category, value, isDigital);

          request->send(200, "application/json", "Appliance Updated");
        } else {
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to flag an appliance as deleted
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/delete/").c_str(),
      HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        ArduinoJson::JsonDocument doc;
        ArduinoJson::DeserializationError error =
            deserializeJson(doc, data, len);

        DEBUG_PRINTF("Received JSON: ['%d']'%s'\n", len, data);

        if (error) {
          DEBUG_PRINTLN("Failed to deserialize JSON");
          request->send(400, "application/json", "Invalid JSON Received");
          return;
        }

        bool deletePermanent = false;
        if (doc.containsKey(CONFIG_APPLIANCE_DELETE_PERMANENT)) {
          deletePermanent = true;
        }

        if (doc.containsKey(CONFIG_APPLIANCE_PIN)) {
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];

          if (!deletePermanent) {
            HomeAppliance *appliance = _config->getAppliance(pin);

            if (appliance == nullptr) {
              request->send(400, "application/json",
                            "The appliance does not exist");
              DEBUG_PRINTF("Appliance with pin [%d] does not exist...\n", pin);
              return;
            }
          }

          _config->deleteAppliance(pin, deletePermanent);
          request->send(200, "application/json", "Appliance Deleted");
        } else {
          DEBUG_PRINTLN("There is no appliance with that pin");
          request->send(400, "application/json", "Invalid JSON");
        }
      });

  // post request to restore an appliance
  on(
      String(String(HOME_SERVER_API_PATH) + "/device/restore/").c_str(),
      HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        ArduinoJson::JsonDocument doc;
        ArduinoJson::DeserializationError error =
            deserializeJson(doc, data, len);

        DEBUG_PRINTF("Received JSON: ['%d']'%s'\n", len, data);

        if (error) {
          DEBUG_PRINTLN("Failed to deserialize JSON");
          request->send(400, "application/json", "Invalid JSON Received");
          return;
        }

        if (doc.containsKey(CONFIG_APPLIANCE_PIN)) {
          uint8_t pin = doc[CONFIG_APPLIANCE_PIN];

          _config->restoreAppliance(pin);
          request->send(200, "application/json", "Appliance Restored");
          DEBUG_PRINTF("Appliance with pin [%d] restored...\n", pin);
        } else {
          DEBUG_PRINTLN("There is no appliance with that pin");
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
