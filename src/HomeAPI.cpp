#include <HomeAPI.hpp>

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

void apiGetAppliances(HomeApplianceConfiguration *config, JsonObject root) {
  JsonArray appliances = root.createNestedArray("appliances");
  JsonArray storedAppliancesJson = config->getJsonConfig()->as<JsonArray>();

  for (JsonObject applianceJson : storedAppliancesJson) {
    appliances.add(applianceJson);
  }
}

void apiAddApplianceData(HomeApplianceConfiguration *config, JsonObject root,
                         bool addDeleted) {
  JsonArray appliances = root.createNestedArray("appliances");
  JsonArray storedAppliancesJson = config->getJsonConfig()->as<JsonArray>();

  for (JsonDocument applianceJson : storedAppliancesJson) {
    if (applianceJson[CONFIG_APPLIANCE_IS_DELETED].as<bool>() == addDeleted) {
      applianceJson.remove(CONFIG_APPLIANCE_IS_DELETED);
      applianceJson.remove(CONFIG_APPLIANCE_CREATED_AT);
      appliances.add(applianceJson);
    }
  }
}
