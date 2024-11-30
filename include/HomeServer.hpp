#pragma once

#include <ArduinoJson.h>
#include <AsyncJson.h>
// #include <AsyncMessagePack.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include <HomeConfig.hpp>
#include <Home.hpp>
#include <HomeDHT.hpp>
#include <HomeRTC.hpp>

class HomeServer : public AsyncWebServer {
 private:
  uint16_t _port;
  HomeDHT *_dht;
  HomeRTC *_rtc;

 public:
  HomeServer(uint16_t port /* = 80*/, HomeDHT *dht, HomeRTC *rtc);
};
