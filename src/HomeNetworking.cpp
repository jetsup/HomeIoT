#include <HomeNetworking.hpp>

HomeNetworking::HomeNetworking(String ssid, String password) {
  _ssid = ssid;
  _password = password;
  WiFi.begin(_ssid.c_str(), _password.c_str());

  // setup mDNS
  mdns_init();
  mdns_hostname_set(_hostname.c_str());
  mdns_instance_name_set(_hostname.c_str());

  _lastConnectionRetry = millis();
}

void HomeNetworking::connect() {
  if (millis() - _lastConnectionRetry >
      HOME_NETWORK_CONNECTION_RETRY_DELAY_MS) {
    if (WiFi.status() != WL_CONNECTED) {
      DEBUG_PRINT(".");
      WiFi.begin(_ssid, _password);
      _lastConnectionRetry = millis();
    } else {
      _connected = true;
    }
  }
}

void HomeNetworking::disconnect() {
  WiFi.disconnect();
  _connected = false;
}

bool HomeNetworking::checkConnection() {
  if (WiFi.status() == WL_CONNECTED) {
    _connected = true;
  } else {
    _connected = false;
  }

  return _connected;
}

bool HomeNetworking::isConnected() { return _connected; }

// NTP
void HomeNetworking::ntpConnect() {
  if (!_ntpConnected && _connected) {
    _ntpClient.begin();
    _ntpClient.setUpdateInterval(HOME_NTP_UPDATE_INTERVAL);
    _ntpConnected = true;
  }
}

void HomeNetworking::ntpDisconnect() {
  _ntpClient.end();
  _ntpConnected = false;
}

bool HomeNetworking::ntpCheckConnection() {
  if (_ntpClient.update()) {
    _ntpConnected = true;
  } else {
    _ntpConnected = false;
  }

  return _ntpConnected;
}

bool HomeNetworking::ntpIsConnected() { return _ntpConnected; }

void HomeNetworking::ntpUpdate() { _ntpClient.update(); }

String HomeNetworking::ntpGetFormattedTime() {
  return _ntpClient.getFormattedTime();
}

unsigned long HomeNetworking::ntpGetEpoch() {
  _ntpClient.forceUpdate();
  return _ntpClient.getEpochTime();
}
