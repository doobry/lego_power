#include <Arduino.h>
#include <LegoPower.h>

LegoPower legoPower;

void setup() {
}

void sendAndWait(uint8_t command) {
  legoPower.sendSinglePwm(LEGO_CHANNEL_1, LEGO_OUTPUT_A, command);
  delay(1000);
}

void loop() {
  sendAndWait(LEGO_PWM_FWD1);
  sendAndWait(LEGO_PWM_FWD2);
  sendAndWait(LEGO_PWM_FWD3);
  sendAndWait(LEGO_PWM_FWD4);
  sendAndWait(LEGO_PWM_FWD5);
  sendAndWait(LEGO_PWM_FWD6);
  sendAndWait(LEGO_PWM_FWD7);
  sendAndWait(LEGO_PWM_FWD6);
  sendAndWait(LEGO_PWM_FWD5);
  sendAndWait(LEGO_PWM_FWD4);
  sendAndWait(LEGO_PWM_FWD3);
  sendAndWait(LEGO_PWM_FWD2);
  sendAndWait(LEGO_PWM_FWD1);
  sendAndWait(LEGO_PWM_FLOAT);
  sendAndWait(LEGO_PWM_BWD1);
  sendAndWait(LEGO_PWM_BWD2);
  sendAndWait(LEGO_PWM_BWD3);
  sendAndWait(LEGO_PWM_BWD4);
  sendAndWait(LEGO_PWM_BWD5);
  sendAndWait(LEGO_PWM_BWD6);
  sendAndWait(LEGO_PWM_BWD7);
  sendAndWait(LEGO_PWM_BWD6);
  sendAndWait(LEGO_PWM_BWD5);
  sendAndWait(LEGO_PWM_BWD4);
  sendAndWait(LEGO_PWM_BWD3);
  sendAndWait(LEGO_PWM_BWD2);
  sendAndWait(LEGO_PWM_BWD1);
  sendAndWait(LEGO_PWM_BREAK);
}
