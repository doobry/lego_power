#include <Arduino.h>

#define SERIAL_PIN 2
#define SERIAL_RATE 76000
#define SERIAL_MARK 0b1111111101010101

#define uS_LOW_BIT 421
#define uS_HIGH_BIT 711
#define uS_STARTSTOP_BIT 1184
#define uS_PAUSE 80000

#define bitValue(value, bit) ((value << bit) & 0x8000) == 0x8000

volatile uint32_t _nextInterupt;

volatile uint16_t _message = 0b0000010001001111;
volatile int8_t _message_index = -2;

ICACHE_RAM_ATTR void timer0_callback () {
  Serial1.write(SERIAL_MARK);
  uint32_t nextDelay;
  _message_index++;
  if(_message_index == -1 || _message_index == 16) {
    nextDelay = uS_STARTSTOP_BIT;
  } else
  if(_message_index == 17) {
    _message_index = -2;
    nextDelay = uS_PAUSE;
  } else
  if(bitValue(_message, _message_index)) {
    nextDelay = uS_HIGH_BIT;
  } else {
    nextDelay = uS_LOW_BIT;
  }
  _nextInterupt += microsecondsToClockCycles(nextDelay);
  timer0_write(_nextInterupt);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(SERIAL_RATE);
  timer0_isr_init();
  _nextInterupt = ESP.getCycleCount();
  timer0_callback();
  timer0_attachInterrupt(timer0_callback);
}

void loop() {
  /*Serial1.write(SERIAL_MARK);
  uint32_t nextDelay = getNextDelay();
  if(nextDelay == uS_PAUSE) {
    delay(80);
  } else {
    delayMicroseconds(nextDelay);
  }*/
}
