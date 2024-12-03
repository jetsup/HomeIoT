#pragma once
/**
 * @author George Ngigi (jetsup)
 * @file HomeAppliance.hpp
 * @date 2024-12-01
 * @version 1.0
 */
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include <HomeConfig.hpp>
#include <HomeRTC.hpp>
#include <HomeUtils.hpp>
#include <vector>

// ============================ HomeAppliance ============================
// error codes
enum class HomeApplianceError {
  NO_ERROR = 0,
  INVALID_PIN = 1,
  INVALID_VALUE = 2,
  INVALID_DIGITAL = 3,
  INVALID_ANALOG = 4,
  INVALID_CURRENT_VALUE = 5,
};

class HomeAppliance {
 public:
  uint8_t _pin = 0;
  bool _isDigital = false;
  int _currentValue = 0;
  int _value = 0;

  HomeAppliance() = delete;
  HomeAppliance(uint8_t pin, int value, bool isDigital);
  virtual ~HomeAppliance() {}

  uint8_t getPin();
  virtual void updateCurrentValue(int val) = 0;
  virtual int getCurrentValue() = 0;
  virtual void setValue(int val) = 0;
  virtual int getValue() = 0;
  virtual bool isDigital() = 0;

  // TODO: Implement Error handling
  HomeApplianceError _error = HomeApplianceError::NO_ERROR;
  HomeApplianceError getError();
  void setError(HomeApplianceError error);
  void clearError();
};

class DigitalAppliance : public HomeAppliance {
 public:
  DigitalAppliance() = delete;
  DigitalAppliance(uint8_t pin, int value);
  ~DigitalAppliance() {}

  void updateCurrentValue(int val) override;
  int getCurrentValue() override;
  void setValue(int val) override;
  int getValue() override;
  bool isDigital() override;
};

class AnalogAppliance : public HomeAppliance {
 public:
  AnalogAppliance() = delete;
  AnalogAppliance(uint8_t pin, int value);
  ~AnalogAppliance() {}

  void updateCurrentValue(int val) override;
  int getCurrentValue() override;
  void setValue(int val) override;
  int getValue() override;
  bool isDigital() override;
};

// ============================ Home Configuration ============================
extern const char* CONFIG_APPLIANCE_NAME;
extern const char* CONFIG_APPLIANCE_IS_DIGITAL;
extern const char* CONFIG_APPLIANCE_PIN;
extern const char* CONFIG_APPLIANCE_OLD_PIN;
extern const char* CONFIG_APPLIANCE_VALUE;
extern const char* CONFIG_APPLIANCE_IS_DELETED;
extern const char* CONFIG_APPLIANCE_CREATED_AT;
extern const char* CONFIG_APPLIANCE_UPDATED_AT;
extern const char* CONFIG_APPLIANCE_RESET;
extern const char* CONFIG_APPLIANCE_DELETE_PERMANENT;

class HomeApplianceConfiguration {
  // File format
  // {
  //     "appliances": [
  //         {
  //             "name": "light",
  //             "is_digital": 1,
  //             "pin": 2,
  //             "value": 1,
  //             "is_deleted": 0,
  //             "created_at": "2024-12-01 12:03:20"
  //         },
  //         {
  //             "name": "fan",
  //             "is_digital": 1,
  //             "pin": 3,
  //             "value": 0,
  //             "is_deleted": 1,
  //             "created_at": "2024-12-01 12:13:26"
  //         },
  //         {
  //             "name": "heater",
  //             "is_digital": 0,
  //             "pin": 4,
  //             "value": 100,
  //             "is_deleted": 0,
  //             "created_at": "2024-12-01 12:32:29"
  //         }
  //     ]
  // }
 private:
  DynamicJsonDocument* _config;
  std::vector<HomeAppliance*>* _appliances;
  HomeRTC* _rtc;

 public:
  HomeApplianceConfiguration(std::vector<HomeAppliance*>* appliances,
                             HomeRTC* rtc);
  ~HomeApplianceConfiguration();

  void readConfiguration();
  void addAppliance(String name, bool isDigital, uint8_t pin, int value = 0);
  void deleteAppliance(uint8_t pin, bool permanent = false);

  /**
   * @brief Delete all appliances
   * @note `This will delete all appliances from the configuration. Should be
   called with caution`

   */
  void reset();
  std::vector<HomeAppliance*> getAppliances();
  HomeAppliance* getAppliance(uint8_t pin);
  void updateAppliance(uint8_t pin, String name, int value, bool isDigital);
  void updateApplianceValue(uint8_t pin, int value);
  void saveConfiguration();
  unsigned int printConfiguration();
  DynamicJsonDocument* getJsonConfig();
};
