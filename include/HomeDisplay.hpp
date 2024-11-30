#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include <HomeConfig.hpp>
#include <HomeUtils.hpp>

class HomeDisplay {
 private:
  Adafruit_SSD1306 *screen;

 public:
  HomeDisplay(TwoWire *wire);
  ~HomeDisplay();
  void begin();
  void clear();
  void display();
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void drawText(int16_t x, int16_t y, const char *text);
  void drawText(int16_t x, int16_t y, const char *text, uint8_t size);
  void drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                uint16_t color);
  void drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                uint16_t color, uint16_t bg);
  void drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                uint16_t color, uint16_t bg, bool wrap);
};
