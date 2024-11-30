#include <Home.hpp>

void apiGetTemperature(HomeDHT *dht, TemperatureUnit unit, JsonObject &root) {
  root["temperature"] = dht->getTemperature(unit);
}

void apiGetHumidity(HomeDHT *dht, JsonObject &root) {
  root["humidity"] = dht->getHumidity();
}

void apiGetTime(DateTime dateTime, JsonObject root) {
  root["time"] = formatTime(dateTime);
  root["date"] = formatDate(dateTime);
}
