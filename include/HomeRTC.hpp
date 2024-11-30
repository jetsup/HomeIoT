#pragma once

#include <Arduino.h>
#include <RTClib.h>

#include <HomeConfig.hpp>
#include <HomeUtils.hpp>

class HomeRTC {
 private:
  char daysOfTheWeek[7][12] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                               "Thursday", "Friday", "Saturday"};
  RTC_DS3231 rtc;
  bool rtcModulePresent = false;

 public:
  /**
   * @brief Construct a new HomeRTC object
   * @note Make sure to initialize the I2C bus before creating an object of this
   * class
   */
  HomeRTC();
  void retryDetect();
  void setDateTime(DateTime dateTime);
  String getDate();
  String getTime();
  unsigned long getEpoch();
  String getDayOfTheWeek();
  float getTemperature();
};
