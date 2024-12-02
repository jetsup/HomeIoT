#include <HomeDisplay.hpp>

const unsigned char gear_logo[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf8, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x01, 0xe0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00,
    0x01, 0xe0, 0x01, 0xe0, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xe0, 0x03, 0xe0, 0x00, 0xf0, 0x00, 0xff, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0xfc, 0x07, 0xc0, 0x00, 0xf8,
    0x07, 0xf1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x7f,
    0xff, 0xc0, 0x00, 0x7f, 0xff, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x1f, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00,
    0x60, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x0f, 0xfc, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00,
    0x01, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x0f, 0xf8, 0x07, 0xfe, 0x00, 0x03, 0xc0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x7f, 0x00, 0x00, 0x3f,
    0x80, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00,
    0x78, 0x00, 0x00, 0x07, 0xe0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x01, 0xf0, 0x01, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0x00,
    0x78, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x0e,
    0x00, 0xff, 0x3f, 0xc0, 0x3c, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x7f, 0xe0, 0x00, 0x1e, 0x01, 0xf0, 0x01, 0xf0, 0x1e, 0x00, 0x01, 0xff,
    0x80, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x1e, 0x03, 0xc0, 0x00, 0xf8,
    0x1e, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x1e,
    0x07, 0x80, 0x00, 0x78, 0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x3e, 0x07, 0x80, 0x00, 0x78, 0x0f, 0x00, 0x00, 0x03,
    0xc0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x1e, 0x07, 0x80, 0x00, 0x78,
    0x0f, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x1e,
    0x03, 0xc0, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00,
    0x7f, 0x80, 0x00, 0x1e, 0x03, 0xe0, 0x01, 0xf0, 0x1e, 0x00, 0x00, 0x7f,
    0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x0f, 0x00, 0xfe, 0x0f, 0xe0,
    0x3c, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x07,
    0x80, 0x3f, 0xff, 0x80, 0x3c, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xe0, 0x03, 0xe0, 0x03, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xe0, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00,
    0x7e, 0x00, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x7f, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x1f, 0xf0, 0x01, 0xfe, 0x00, 0x00, 0x00, 0xf0,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xf0,
    0x00, 0x18, 0x00, 0xf0, 0x3c, 0x00, 0xe0, 0x00, 0x00, 0x07, 0xc0, 0x00,
    0x00, 0x1f, 0xfe, 0x00, 0x00, 0xff, 0x81, 0xe0, 0x1e, 0x07, 0xfc, 0x00,
    0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0,
    0x1f, 0xff, 0xff, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xc0, 0xff, 0xc0, 0x0f, 0xfc, 0x0f, 0x80, 0x00, 0x1e, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x18, 0x00, 0x00, 0x60, 0x07, 0x80,
    0x00, 0x1e, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x07, 0x83, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x1f, 0x00, 0x00, 0x0f, 0x80, 0x3f, 0xff, 0x80, 0x00, 0x7f,
    0xc1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x07, 0xe1, 0xfc,
    0x0f, 0xc0, 0x00, 0xfc, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00,
    0x00, 0x01, 0xff, 0xe0, 0x03, 0xe0, 0x00, 0xf0, 0x00, 0x78, 0x00, 0x3f,
    0xf0, 0x00, 0x78, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x01, 0xe0, 0x01, 0xf0,
    0x00, 0xf0, 0x01, 0xff, 0xfe, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xe0, 0x01, 0xe0, 0xf1, 0xe0, 0x07, 0xe0, 0x1f, 0x80, 0x1f, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xe3, 0xf0, 0x00, 0x0f, 0x80,
    0x07, 0xc0, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xc3,
    0xc0, 0x00, 0x0f, 0x00, 0x03, 0xc0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7f, 0xff, 0xc3, 0xc0, 0x00, 0x0f, 0x00, 0x03, 0xc0, 0x00, 0x0f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x03, 0xc0, 0x00, 0x0f, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0xff, 0x80, 0x0f, 0x80, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x07, 0xe0, 0x1c, 0x00, 0x1f, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xff,
    0xfc, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x78, 0x00, 0x3f, 0xf0, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00,
    0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x18, 0x00, 0x00, 0x60, 0x07, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0xff, 0xc0,
    0x0f, 0xfc, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x81, 0xe0, 0x1e, 0x07, 0xfc, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xf0,
    0x3c, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
    0xf0, 0x00, 0x00, 0x00};

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
  // FIXME: remove adafruit logo from memory
  screen->clearDisplay();
  screen->drawBitmap(0, 0, gear_logo, 128, 64, WHITE);
  screen->display();
  delay(2000);  // Pause for 1 seconds
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
