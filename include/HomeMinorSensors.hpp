#pragma once

#include <Arduino.h>

#include <HomeConfig.hpp>
#include <HomeUtils.hpp>

#ifdef HOME_CONFIGURE_IR
#include <IRremoteESP8266.h>
#ifdef HOME_HAS_IR_RECEIVER
#include <IRrecv.h>
#endif  // HOME_HAS_IR_RECEIVER
#ifdef HOME_HAS_IR_SENDER
#include <IRsend.h>
#endif  // HOME_HAS_IR_SENDER

#ifdef HOME_HAS_IR_RECEIVER
class HomeIRReceiver : public IRrecv {
 private:
  uint8_t _receivePin;
  decode_results _results;

 public:
  HomeIRReceiver() = delete;
  HomeIRReceiver(uint8_t receivePin);
  ~HomeIRReceiver();
};
#endif  // HOME_HAS_IR_RECEIVER

#ifdef HOME_HAS_IR_SENDER
class HomeIRSender : public IRsend {
 public:
  HomeIRSender() = delete;
  HomeIRSender(uint16_t IRsendPin);
  ~HomeIRSender();
};
#endif  // HOME_HAS_IR_SENDER
#endif  // HOME_CONFIGURE_IR
