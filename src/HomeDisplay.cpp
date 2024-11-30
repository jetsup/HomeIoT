#include <HomeDisplay.hpp>

HomeDisplay::HomeDisplay(TwoWire *wire) {
  screen = new Adafruit_SSD1306(HOME_SCREEN_WIDTH, HOME_SCREEN_HEIGHT, wire,
                                HOME_OLED_RESET);
}

HomeDisplay::~HomeDisplay() { delete screen; }

void HomeDisplay::begin() {
  if (!screen->begin(SSD1306_SWITCHCAPVCC, HOME_SCREEN_ADDRESS)) {
    DEBUG_PRINTLN(F("SSD1306 allocation failed"));
    for (;;);
  }
  // TODO: replace adafruit logo with custom logo
  screen->display();
  delay(200);  // Pause for 2 seconds
  screen->clearDisplay();
}

void HomeDisplay::clear() { screen->clearDisplay(); }

void HomeDisplay::display() { screen->display(); }

void HomeDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                           uint16_t color) {
  screen->drawLine(x0, y0, x1, y1, color);
}

void HomeDisplay::drawText(int16_t x, int16_t y, const char *text) {
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(x, y);
  screen->println(text);
}

void HomeDisplay::drawText(int16_t x, int16_t y, const char *text,
                           uint8_t size) {
  screen->setTextSize(size);
  screen->setTextColor(WHITE);
  screen->setCursor(x, y);
  screen->println(text);
}

void HomeDisplay::drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                           uint16_t color) {
  screen->setTextSize(size);
  screen->setTextColor(color);
  screen->setCursor(x, y);
  screen->println(text);
}

void HomeDisplay::drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                           uint16_t color, uint16_t bg) {
  screen->setTextSize(size);
  screen->setTextColor(color, bg);
  screen->setCursor(x, y);
  screen->println(text);
}

void HomeDisplay::drawText(int16_t x, int16_t y, const char *text, uint8_t size,
                           uint16_t color, uint16_t bg, bool wrap) {
  screen->setTextSize(size);
  screen->setTextColor(color, bg);
  screen->setCursor(x, y);
  screen->println(text);
  screen->setTextWrap(wrap);
}
