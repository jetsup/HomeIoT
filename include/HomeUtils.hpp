#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <time.h>

#define DEBUG true
#define DEBUG_PRINT(x) \
  if (DEBUG) Serial.print(x)
#define DEBUG_PRINTLN(x) \
  if (DEBUG) Serial.println(x)
#define DEBUG_PRINTF(format, ...) \
  if (DEBUG) Serial.printf(format, __VA_ARGS__)

String formatDate(DateTime dateTime);
String formatTime(DateTime dateTime);

String formatNumber(int number);
