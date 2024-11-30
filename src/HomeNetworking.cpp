#include <HomeNetworking.hpp>

HomeNetworking::HomeNetworking(String ssid, String password) {
  this->ssid = ssid;
  this->password = password;
  WiFi.begin(ssid.c_str(), password.c_str());
  lastConnectionRetry = millis();
}

void HomeNetworking::connect() {
  if (millis() - lastConnectionRetry > HOME_NETWORK_CONNECTION_RETRY_DELAY_MS) {
    if (WiFi.status() != WL_CONNECTED) {
      DEBUG_PRINT(".");
      WiFi.begin(ssid, password);
      lastConnectionRetry = millis();
    } else {
      connected = true;
    }
  }
}

void HomeNetworking::disconnect() {
  WiFi.disconnect();
  connected = false;
}

bool HomeNetworking::checkConnection() {
  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
  } else {
    connected = false;
  }

  return connected;
}

bool HomeNetworking::isConnected() { return connected; }

// NTP
void HomeNetworking::ntpConnect() {
  if (!ntpConnected && connected) {
    ntpClient.begin();
    ntpClient.setUpdateInterval(HOME_NTP_UPDATE_INTERVAL);
    ntpConnected = true;
  }
}

void HomeNetworking::ntpDisconnect() {
  ntpClient.end();
  ntpConnected = false;
}

bool HomeNetworking::ntpCheckConnection() {
  if (ntpClient.update()) {
    ntpConnected = true;
  } else {
    ntpConnected = false;
  }

  return ntpConnected;
}

bool HomeNetworking::ntpIsConnected() { return ntpConnected; }

void HomeNetworking::ntpUpdate() { ntpClient.update(); }

String HomeNetworking::ntpGetFormattedTime() {
  return ntpClient.getFormattedTime();
}

unsigned long HomeNetworking::ntpGetEpoch() {
  ntpClient.forceUpdate();
  return ntpClient.getEpochTime();
}
