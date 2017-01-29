#include "LegoPower.h"

#define UART1_PIN 2

#define CYCLE_LENGTH 26
#define CYCLES_LOW 16
#define CYCLES_HIGH 27
#define CYCLES_START 45
#define SERIAL_MARK 0b1111111101010101

#define UINT16_MSB_MASK 0b1000000000000000

// Nibble 1 Internals
#define TOGGLE_LOW 0b0000
#define TOGGLE_HIGH 0b1000
#define ESCAPE_MODE 0b0000
#define ESCAPE_COMBO 0b0100

// Nibble 2 Internals
#define ADDRESS_DEFAULT 0b0000
#define ADDRESS_EXTENDED 0b1000
#define MODE_SINGLE_PWM 0b0100
#define MODE_SINGLE_CSTID 0b0110

LegoPower::LegoPower() {
  pinMode(UART1_PIN, OUTPUT);
  digitalWrite(UART1_PIN, HIGH);
  Serial1.begin(76000);
  _toggle = false;
}

void LegoPower::sendSinglePwm(uint8_t channel, uint8_t output, uint8_t command) {
  _sendSingleOutput(channel, output, MODE_SINGLE_PWM, command);
}

void LegoPower::_sendSingleOutput(uint8_t channel, uint8_t output, uint8_t mode, uint8_t command) {
  _message = _computeMessage(
    _getNextToggle() | ESCAPE_MODE | channel,
    ADDRESS_DEFAULT | mode | output,
    command
  );
  _sendMessage();
}

void LegoPower::_sendMessage() {
  for(uint8_t transmission = 0; transmission < 5; transmission++) {
    _sendDelay();
    _sendStartStopBit();
    _sendMessageBody();
    _sendStartStopBit();
  }
}

void LegoPower::_sendMessageBody() {
  _resetNextMessageBit();
  while(_hasNextMessageBit()) {
    _sendMessageBit();
  }
}

void LegoPower::_sendMessageBit() {
  if(_getNextMessageBit()) {
    _sendHighBit();
  } else {
    _sendLowBit();
  }
}

uint8_t LegoPower::_getNextToggle() {
  _toggle = !_toggle;
  return (_toggle ? TOGGLE_HIGH : TOGGLE_LOW);
}

uint16_t LegoPower::_computeMessage(
  uint8_t nibble1, uint8_t nibble2, uint8_t nibble3
) {
  return nibble1 << 12
      | nibble2 << 8
      | nibble3 << 4
      | _computeChecksum(nibble1, nibble2, nibble3);
}

uint8_t LegoPower::_computeChecksum(
  uint8_t nibble1, uint8_t nibble2, uint8_t nibble3
) {
  return 0xF ^ nibble1 ^ nibble2 ^ nibble3;
}

void LegoPower::_resetNextMessageBit() {
  _nextMessageBit = 0;
}

bool LegoPower::_hasNextMessageBit() {
  return _nextMessageBit < 16;
}

bool LegoPower::_getNextMessageBit() {
  return (UINT16_MSB_MASK & (_message << _nextMessageBit++)) == UINT16_MSB_MASK;
}

void LegoPower::_sendDelay() {
  delay(80);
}

void LegoPower::_sendStartStopBit() {
  _sendBit(CYCLES_START);
}

void LegoPower::_sendLowBit() {
  _sendBit(CYCLES_LOW);
}

void LegoPower::_sendHighBit() {
  _sendBit(CYCLES_HIGH);
}

void LegoPower::_sendBit(uint16_t cycles) {
  _sendMark();
  _sendPause(cycles);
}

void LegoPower::_sendMark() {
  Serial1.write(SERIAL_MARK);
}

void LegoPower::_sendPause(uint16_t cycles) {
  delayMicroseconds(CYCLE_LENGTH * cycles);
}
