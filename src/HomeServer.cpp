#include <HomeServer.hpp>

HomeServer::HomeServer(uint16_t port, HomeDHT *dht, HomeRTC *rtc) : AsyncWebServer(port) {
  _port = port;
  _dht = dht;
    _rtc = rtc;

  // Serve the root page
  on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    // request->send(LittleFS, "/index.html", "text/html");
    request->send(200, "text/plain", "Hello, world");
  });

  on(String(String(HOME_SERVER_API_PATH) + "/").c_str(), HTTP_GET,
     [this](AsyncWebServerRequest *request) {
       // send a JSON response
       AsyncJsonResponse *response = new AsyncJsonResponse();
       JsonObject root = response->getRoot();
       apiGetTemperature(_dht, CELSIUS, root);
       apiGetHumidity(_dht, root);
       apiGetTime(DateTime(_rtc->getEpoch()), root);
       response->setLength();
       request->send(response);
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
