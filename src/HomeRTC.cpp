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

unsigned long HomeRTC::getEpoch() {
  if (!rtcModulePresent) {
    retryDetect();
    return 0;
  }

  DateTime now = rtc.now();
  return now.unixtime();
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

bool HomeRTC::setAlarm1(DateTime &alarmTime, Ds3231Alarm1Mode alarmMode) {
  if (!rtcModulePresent) {
    retryDetect();
    return false;
  }

  return rtc.setAlarm1(alarmTime, alarmMode);
}

DateTime HomeRTC::getAlarm1() {
  if (!rtcModulePresent) {
    retryDetect();
    return DateTime();
  }

  return rtc.getAlarm1();
}

bool HomeRTC::setAlarm2(DateTime &alarmTime, Ds3231Alarm2Mode alarmMode) {
  if (!rtcModulePresent) {
    retryDetect();
    return false;
  }

  return rtc.setAlarm2(alarmTime, alarmMode);
}

DateTime HomeRTC::getAlarm2() {
  if (!rtcModulePresent) {
    retryDetect();
    return DateTime();
  }

  return rtc.getAlarm2();
}

void HomeRTC::clearAlarm(uint8_t alarmNum) {
  if (!rtcModulePresent) {
    retryDetect();
    return;
  }

  rtc.clearAlarm(alarmNum);
}

void HomeRTC::disableAlarm(uint8_t alarmNum) {
  if (!rtcModulePresent) {
    retryDetect();
    return;
  }

  rtc.disableAlarm(alarmNum);
}

bool HomeRTC::alarmFired(uint8_t alarmNum) {
  if (!rtcModulePresent) {
    retryDetect();
    return false;
  }

  return rtc.alarmFired(alarmNum);
}
