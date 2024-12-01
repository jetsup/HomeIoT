#include <HomeAppliance.hpp>

const char *CONFIG_APPLIANCE_NAME = "name";
const char *CONFIG_APPLIANCE_IS_DIGITAL = "is_digital";
const char *CONFIG_APPLIANCE_PIN = "pin";
const char *CONFIG_APPLIANCE_VALUE = "value";
const char *CONFIG_APPLIANCE_IS_DELETED = "is_deleted";
const char *CONFIG_APPLIANCE_CREATED_AT = "created_at";

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

void HomeApplianceConfiguration::addAppliance(String name, bool isDigital,
                                              uint8_t pin, int value) {
  // JsonObject appliance = _config->createNestedObject("appliance");
  JsonObject appliance = _config->createNestedObject();
  appliance[CONFIG_APPLIANCE_NAME] = name;
  appliance[CONFIG_APPLIANCE_IS_DIGITAL] = isDigital;
  appliance[CONFIG_APPLIANCE_PIN] = pin;
  appliance[CONFIG_APPLIANCE_VALUE] = value;
  appliance[CONFIG_APPLIANCE_IS_DELETED] = 0;
  appliance[CONFIG_APPLIANCE_CREATED_AT] =
      _rtc->getDate() + " " + _rtc->getTime();

  saveConfiguration();

  // activate the appliance based on the value
  if (isDigital) {
    _appliances->push_back(new DigitalAppliance(pin, value));
  } else {
    _appliances->push_back(new AnalogAppliance(pin, value));
  }
}

void HomeApplianceConfiguration::deleteAppliance(uint8_t pin) {
  JsonArray appliances = _config->as<JsonArray>();
  for (JsonObject appliance : appliances) {
    if (appliance[CONFIG_APPLIANCE_PIN] == pin) {
      appliance[CONFIG_APPLIANCE_IS_DELETED] = 1;
      saveConfiguration();
      return;
    }
  }

  DEBUG_PRINTLN("Appliance not found");
}

std::vector<HomeAppliance *> HomeApplianceConfiguration::getAppliances() {
  std::vector<HomeAppliance *> appliances;
  JsonArray appliancesArray = _config->as<JsonArray>();

  for (JsonObject appliance : appliancesArray) {
    if (appliance[CONFIG_APPLIANCE_IS_DELETED] == 0) {
      if (appliance[CONFIG_APPLIANCE_IS_DIGITAL] == 1) {
        appliances.push_back(new DigitalAppliance(
            static_cast<uint8_t>(appliance[CONFIG_APPLIANCE_PIN]),
            static_cast<int>(appliance[CONFIG_APPLIANCE_VALUE])));
      } else {
        appliances.push_back(new AnalogAppliance(
            static_cast<uint8_t>(appliance[CONFIG_APPLIANCE_PIN]),
            static_cast<int>(appliance[CONFIG_APPLIANCE_VALUE])));
      }
    }
  }

  return appliances;
}

HomeAppliance *HomeApplianceConfiguration::getAppliance(uint8_t pin) {
  JsonArray appliances = _config->as<JsonArray>();

  for (JsonObject appliance : appliances) {
    serializeJsonPretty(appliance, Serial);

    if (appliance[CONFIG_APPLIANCE_PIN] == pin) {
      for (HomeAppliance *app : *_appliances) {
        if (app->getPin() == pin) {
          DEBUG_PRINTF("Found appliance with pin %d\n", pin);
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
    if (appliance[CONFIG_APPLIANCE_PIN] == pin) {
      appliance[CONFIG_APPLIANCE_VALUE] = value;
      saveConfiguration();
      DEBUG_PRINTF("Appliance[%d] value updated to %d\n", pin, value);
      return;
    }
  }

  DEBUG_PRINTLN("Appliance not found");
}

void HomeApplianceConfiguration::updateApplianceName(uint8_t pin, String name) {
  JsonArray appliances = _config->as<JsonArray>();
  for (JsonObject appliance : appliances) {
    if (appliance[CONFIG_APPLIANCE_PIN] == pin) {
      appliance[CONFIG_APPLIANCE_NAME] = name;
      saveConfiguration();
      return;
    }
  }

  DEBUG_PRINTLN("Appliance not found");
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

DynamicJsonDocument* HomeApplianceConfiguration::getJsonConfig(){
    return _config;
}
