#include <HomeAppliance.hpp>

const char *CONFIG_APPLIANCE_NAME = "name";
const char *CONFIG_APPLIANCE_CATEGORY = "category";
const char *CONFIG_APPLIANCE_IS_DIGITAL = "is_digital";
const char *CONFIG_APPLIANCE_PIN = "pin";
const char *CONFIG_APPLIANCE_OLD_PIN = "old_pin";
const char *CONFIG_APPLIANCE_VALUE = "value";
const char *CONFIG_APPLIANCE_IS_DELETED = "is_deleted";
const char *CONFIG_APPLIANCE_CREATED_AT = "created_at";
const char *CONFIG_APPLIANCE_UPDATED_AT = "updated_at";
const char *CONFIG_APPLIANCE_RESET = "reset";
const char *CONFIG_APPLIANCE_DELETE_PERMANENT = "delete_permanent";

// ============================ HomeAppliance ============================
HomeAppliance::HomeAppliance(uint8_t pin, int value, bool isDigital)
    : _pin(pin), _value(value), _isDigital(isDigital) {}

uint8_t HomeAppliance::getPin() { return _pin; }

HomeApplianceError HomeAppliance::getError() { return _error; }

void HomeAppliance::setError(HomeApplianceError error) { _error = error; }

void HomeAppliance::clearError() { _error = HomeApplianceError::NO_ERROR; }

// Digital appliance
DigitalAppliance::DigitalAppliance(uint8_t pin, int value)
    : HomeAppliance(pin, value, true) {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _value);
}

void DigitalAppliance::updateCurrentValue(int val) {
  _currentValue = val;
  _currentValue = digitalRead(_pin);
}

int DigitalAppliance::getCurrentValue() { return _currentValue; }

void DigitalAppliance::setValue(int val) {
  if (val < 0 || val > 1) {
    setError(HomeApplianceError::INVALID_VALUE);
    return;
  }

  clearError();
  _value = val;
  digitalWrite(_pin, _value);
}

int DigitalAppliance::getValue() { return _value; }

bool DigitalAppliance::isDigital() { return _isDigital; }

// Analog appliance
AnalogAppliance::AnalogAppliance(uint8_t pin, int value)
    : HomeAppliance(pin, value, false) {
  pinMode(_pin, OUTPUT);
  analogWrite(_pin, _value);
}

void AnalogAppliance::updateCurrentValue(int val) {
  _currentValue = val;
  _currentValue = analogRead(_pin);
}

int AnalogAppliance::getCurrentValue() { return _currentValue; }

void AnalogAppliance::setValue(int val) {
  _value = val;
  analogWrite(_pin, _value);
}

int AnalogAppliance::getValue() { return _value; }

bool AnalogAppliance::isDigital() { return _isDigital; }

// ============================ Home Configuration ============================
HomeApplianceConfiguration::HomeApplianceConfiguration(
    std::vector<HomeAppliance *> *appliances, HomeRTC *rtc)
    : _appliances(appliances), _rtc(rtc) {
  _config = new DynamicJsonDocument(1024);
  readConfiguration();
  *_appliances = getAppliances();
}

HomeApplianceConfiguration::~HomeApplianceConfiguration() { delete _config; }

void HomeApplianceConfiguration::readConfiguration() {
  File file = LittleFS.open(HOME_APPLIANCES_FILE, "r");
  if (!file) {
    DEBUG_PRINTLN("Failed to open file for reading. Maybe it doesn't exist");
    return;
  }

  // Check if the file has data
  if (file.size() == 0) {
    DEBUG_PRINTLN("File is empty");
    return;
  }

  DeserializationError error = deserializeJson(*_config, file);
  file.close();

  if (error) {
    DEBUG_PRINTLN("Failed to read file");
    return;
  }
}

void HomeApplianceConfiguration::addAppliance(String name, String category,
                                              bool isDigital, uint8_t pin,
                                              int value) {
  // JsonObject appliance = _config->createNestedObject("appliance");
  JsonObject appliance = _config->createNestedObject();
  appliance[CONFIG_APPLIANCE_NAME] = name;
  appliance[CONFIG_APPLIANCE_CATEGORY] = category;
  appliance[CONFIG_APPLIANCE_IS_DIGITAL] = isDigital;
  appliance[CONFIG_APPLIANCE_PIN] = pin;
  appliance[CONFIG_APPLIANCE_VALUE] = value;
  appliance[CONFIG_APPLIANCE_IS_DELETED] = 0;
  appliance[CONFIG_APPLIANCE_CREATED_AT] =
      _rtc->getDate() + " " + _rtc->getTime();
  appliance[CONFIG_APPLIANCE_UPDATED_AT] =
      _rtc->getDate() + " " + _rtc->getTime();

  saveConfiguration();

  // activate the appliance based on the value
  if (isDigital) {
    _appliances->push_back(new DigitalAppliance(pin, value));
  } else {
    _appliances->push_back(new AnalogAppliance(pin, value));
  }
}

void HomeApplianceConfiguration::deleteAppliance(uint8_t pin, bool permanent) {
  JsonArray appliances = _config->as<JsonArray>();

  // turn off the appliance first
  for (HomeAppliance *app : *_appliances) {
    if (app->getPin() == pin) {
      app->setValue(0);
    }
  }

  for (int i = 0; i < appliances.size(); i++) {
    if (permanent) {
      if (appliances[i][CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin &&
          appliances[i][CONFIG_APPLIANCE_IS_DELETED].as<bool>()) {
        appliances.remove(i);
        saveConfiguration();
        return;
      }
    } else {
      if (appliances[i][CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin &&
          !appliances[i][CONFIG_APPLIANCE_IS_DELETED].as<bool>()) {
        appliances[i][CONFIG_APPLIANCE_IS_DELETED] = 1;
        appliances[i][CONFIG_APPLIANCE_VALUE] = 0;
        saveConfiguration();
        return;
      }
    }
  }

  DEBUG_PRINTLN("Appliance not found");
}

void HomeApplianceConfiguration::restoreAppliance(uint8_t pin) {
  JsonArray appliances = _config->as<JsonArray>();

  for (int i = 0; i < appliances.size(); i++) {
    if (appliances[i][CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin &&
        appliances[i][CONFIG_APPLIANCE_IS_DELETED].as<bool>()) {
      appliances[i][CONFIG_APPLIANCE_IS_DELETED] = 0;
      saveConfiguration();
      return;
    }
  }

  DEBUG_PRINTLN("Appliance not found");
}

void HomeApplianceConfiguration::reset() {
  // turnoff all appliances first
  for (HomeAppliance *app : *_appliances) {
    app->setValue(0);
  }

  // delete the config json file and recreate it
  if (LittleFS.exists(HOME_APPLIANCES_FILE)) {
    LittleFS.remove(HOME_APPLIANCES_FILE);
  }

  File file = LittleFS.open(HOME_APPLIANCES_FILE, "w", true);
  if (!file) {
    DEBUG_PRINTLN("Failed to create file");
    return;
  }

  _config = new DynamicJsonDocument(1024);
  saveConfiguration();
  _appliances->clear();
}

std::vector<HomeAppliance *> HomeApplianceConfiguration::getAppliances() {
  std::vector<HomeAppliance *> appliances;
  JsonArray appliancesArray = _config->as<JsonArray>();

  for (JsonObject appliance : appliancesArray) {
    if (!appliance[CONFIG_APPLIANCE_IS_DELETED].as<bool>()) {
      if (appliance[CONFIG_APPLIANCE_IS_DIGITAL].as<bool>()) {
        appliances.push_back(
            new DigitalAppliance(appliance[CONFIG_APPLIANCE_PIN].as<uint8_t>(),
                                 appliance[CONFIG_APPLIANCE_VALUE].as<int>()));
      } else {
        appliances.push_back(
            new AnalogAppliance(appliance[CONFIG_APPLIANCE_PIN].as<uint8_t>(),
                                appliance[CONFIG_APPLIANCE_VALUE].as<int>()));
      }
    }
  }

  return appliances;
}

HomeAppliance *HomeApplianceConfiguration::getAppliance(uint8_t pin) {
  JsonArray appliances = _config->as<JsonArray>();

  for (JsonObject appliance : appliances) {
    if (appliance[CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin) {
      for (HomeAppliance *app : *_appliances) {
        if (app->getPin() == pin) {
          return app;
        }
      }
    }
  }

  DEBUG_PRINTF("Appliance with pin [%d] not found\n", pin);

  return nullptr;
}

void HomeApplianceConfiguration::updateApplianceValue(uint8_t pin, int value) {
  JsonArray appliances = _config->as<JsonArray>();
  for (JsonObject appliance : appliances) {
    if (appliance[CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin) {
      appliance[CONFIG_APPLIANCE_VALUE] = value;
      saveConfiguration();
      DEBUG_PRINTF("Appliance[%d] value updated to %d\n", pin, value);
      return;
    }
  }

  DEBUG_PRINTLN("Appliance not found");
}

void HomeApplianceConfiguration::updateAppliance(uint8_t pin, String name,
                                                 String category, int value,
                                                 bool isDigital) {
  JsonArray appliances = _config->as<JsonArray>();

  for (JsonObject appliance : appliances) {
    if (appliance[CONFIG_APPLIANCE_PIN].as<uint8_t>() == pin) {
      appliance[CONFIG_APPLIANCE_NAME] = name;
      appliance[CONFIG_APPLIANCE_CATEGORY] = category;
      appliance[CONFIG_APPLIANCE_VALUE] = value;
      appliance[CONFIG_APPLIANCE_IS_DIGITAL] = isDigital;
      saveConfiguration();

      DEBUG_PRINTLN("Appliance updated!");
      return;
    }
  }

  DEBUG_PRINTLN("Appliance Not Found");
}

void HomeApplianceConfiguration::saveConfiguration() {
  File file = LittleFS.open(HOME_APPLIANCES_FILE, "w");
  if (!file) {
    DEBUG_PRINTLN("Failed to open file for writing");
    return;
  }

  serializeJson(*_config, file);
  file.close();
}

unsigned int HomeApplianceConfiguration::printConfiguration() {
  if (DEBUG) {
    return serializeJsonPretty(*_config, Serial);
  }

  return 0;
}

DynamicJsonDocument *HomeApplianceConfiguration::getJsonConfig() {
  return _config;
}
