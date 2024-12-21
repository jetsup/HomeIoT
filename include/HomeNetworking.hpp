#pragma once

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <ESPmDNS.h>

#include <HomeConfig.hpp>
#include <HomeCredentials.hpp>
#include <HomeUtils.hpp>

class HomeNetworking {
 private:
  bool _connected = false;
  unsigned long _lastConnectionRetry = 0;
  String _ssid;
  String _password;
  String _hostname = HOME_DEVICE_DNS_NAME;
  // NTP
  WiFiUDP _ntpUDP;
  NTPClient _ntpClient = NTPClient(_ntpUDP, HOME_NTP_TIME_OFFSET);
  bool _ntpConnected = false;

 public:
  HomeNetworking() = delete;
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
