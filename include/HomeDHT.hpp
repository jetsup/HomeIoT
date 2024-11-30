#pragma once

#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#include <HomeConfig.hpp>

enum TemperatureUnit { CELSIUS, FAHRENHEIT };

class HomeDHT {
 private:
  DHT_Unified *dht;
  uint32_t delayMS;
  uint32_t lastTempRead;
  uint32_t lastHumidityRead;
  sensors_event_t event;
  sensor_t sensor;
  float temperature;
  float humidity;

 public:
  HomeDHT(uint8_t pin /*, uint32_t delayMS*/);
  float getTemperature(TemperatureUnit unit);
  float getHumidity();
  void readSensor();
};
