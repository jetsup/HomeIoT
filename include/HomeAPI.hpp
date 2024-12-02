#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <HomeDHT.hpp>
#include <HomeRTC.hpp>
#include <HomeAppliance.hpp>

// create a holder for all the appliances that can be passed to the server for
// data collection

void apiGetTemperature(HomeDHT *dht, TemperatureUnit unit, JsonObject &root);

void apiGetHumidity(HomeDHT *dht, JsonObject &root);

void apiGetTime(DateTime dateTime, JsonObject root);

void apiGetAppliances(HomeApplianceConfiguration *config, JsonObject root);

void apiAddApplianceData(HomeApplianceConfiguration *config, JsonObject root, bool addDeleted);
