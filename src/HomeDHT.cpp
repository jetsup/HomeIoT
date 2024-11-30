#include <HomeDHT.hpp>

HomeDHT::HomeDHT(uint8_t pin) {
  dht = new DHT_Unified(pin, DHTTYPE);
  dht->begin();

  dht->temperature().getSensor(&sensor);
  dht->humidity().getSensor(&sensor);

  this->delayMS = sensor.min_delay / 1000;
  lastTempRead = 0;
  lastHumidityRead = 0;
}

float HomeDHT::getTemperature(TemperatureUnit unit) {
  if (millis() - lastTempRead >= delayMS) {
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      temperature = NAN;
    } else {
      temperature = event.temperature;
      if (unit == FAHRENHEIT) {
        temperature = temperature * 9 / 5 + 32;
      }
    }
    lastTempRead = millis();
  }
  return temperature;
}

float HomeDHT::getHumidity() {
  if (millis() - lastHumidityRead >= delayMS) {
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      humidity = NAN;
    } else {
      humidity = event.relative_humidity;
    }
    lastHumidityRead = millis();
  }
  return humidity;
}
