#pragma once

#include <ArduinoJson.h>
#include <AsyncJson.h>
// #include <AsyncMessagePack.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include <Home.hpp>
#include <HomeAppliance.hpp>
#include <HomeConfig.hpp>
#include <HomeDHT.hpp>
#include <HomeRTC.hpp>

class HomeServer : public AsyncWebServer {
 private:
  uint16_t _port;
  HomeDHT *_dht;
  HomeRTC *_rtc;
  HomeApplianceConfiguration *_config;

 public:
  HomeServer(uint16_t port /* = 80*/, HomeDHT *dht, HomeRTC *rtc,
             HomeApplianceConfiguration *config);
};
