#include <HomeRTC.hpp>

HomeRTC::HomeRTC() {
  rtcModulePresent = rtc.begin();
  delay(1000);
}

void HomeRTC::retryDetect() { rtcModulePresent = rtc.begin(); }

void HomeRTC::setDateTime(DateTime dateTime) {
  if (!rtcModulePresent) {
    retryDetect();
    return;
  }

  rtc.adjust(dateTime);
}

String HomeRTC::getDate() {
  if (!rtcModulePresent) {
    retryDetect();
    return "Unknown";
  }

  DateTime now = rtc.now();
  return formatDate(now);
}

String HomeRTC::getTime() {
  if (!rtcModulePresent) {
    retryDetect();
    return "Unknown";
  }

  DateTime now = rtc.now();
  return formatTime(now);
}

String HomeRTC::getDayOfTheWeek() {
  if (!rtcModulePresent) {
    retryDetect();
    return "Unknown";
  }

  DateTime now = rtc.now();
  return daysOfTheWeek[now.dayOfTheWeek()];
}

float HomeRTC::getTemperature() {
  if (!rtcModulePresent) {
    retryDetect();
    return 0.0;
  }

  return rtc.getTemperature();
}
