#pragma once

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>

#include <HomeConfig.hpp>
#include <HomeCredentials.hpp>
#include <HomeUtils.hpp>

class HomeNetworking {
 private:
  bool connected = false;
  unsigned long lastConnectionRetry = 0;
  String ssid;
  String password;
  HomeNetworking() = delete;
  // NTP
  WiFiUDP ntpUDP;
  NTPClient ntpClient = NTPClient(ntpUDP, HOME_NTP_TIME_OFFSET);
  bool ntpConnected = false;

 public:
  HomeNetworking(String ssid = HOME_WIFI_SSID,
                 String password = HOME_WIFI_PASSWORD);
  void connect();
  void disconnect();
  bool checkConnection();
  bool isConnected();

  // NTP
  void ntpConnect();
  void ntpDisconnect();
  bool ntpCheckConnection();
  bool ntpIsConnected();
  void ntpUpdate();
  String ntpGetFormattedTime();
  unsigned long ntpGetEpoch();
};
