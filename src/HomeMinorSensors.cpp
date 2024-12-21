#include <HomeMinorSensors.hpp>

#ifdef HOME_HAS_IR_RECEIVER
HomeIRReceiver::HomeIRReceiver(uint8_t receivePin)
    : _receivePin(receivePin), IRrecv(receivePin) {
  enableIRIn();
}

HomeIRReceiver::~HomeIRReceiver() {
  //
  disableIRIn();
}
#endif  // HOME_HAS_IR_RECEIVER

// ---------------------------- IR Sender ----------------------------
#ifdef HOME_HAS_IR_SENDER
HomeIRSender::HomeIRSender(uint16_t IRsendPin) : IRsend(IRsendPin) {}

HomeIRSender::~HomeIRSender() {}
#endif  // HOME_HAS_IR_SENDER
