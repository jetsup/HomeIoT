#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <HomeDHT.hpp>
#include <HomeRTC.hpp>

// create a holder for all the appliances that can be passed to the server for
// data collection

void apiGetTemperature(HomeDHT *dht, TemperatureUnit unit, JsonObject &root);

void apiGetHumidity(HomeDHT *dht, JsonObject &root);

void apiGetTime(DateTime dateTime, JsonObject root);
