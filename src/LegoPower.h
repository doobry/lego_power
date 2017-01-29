#ifndef LegoPower_h
#define LegoPower_h

#include "Arduino.h"

#define LEGO_CHANNEL_1 0b0000
#define LEGO_CHANNEL_2 0b0001
#define LEGO_CHANNEL_3 0b0010
#define LEGO_CHANNEL_4 0b0010

#define LEGO_OUTPUT_A 0b0000
#define LEGO_OUTPUT_B 0b0001

#define LEGO_PWM_FLOAT 0b0000
#define LEGO_PWM_FWD1 0b0001
#define LEGO_PWM_FWD2 0b0010
#define LEGO_PWM_FWD3 0b0011
#define LEGO_PWM_FWD4 0b0100
#define LEGO_PWM_FWD5 0b0101
#define LEGO_PWM_FWD6 0b0110
#define LEGO_PWM_FWD7 0b0111
#define LEGO_PWM_BREAK 0b1000
#define LEGO_PWM_BWD7 0b1001
#define LEGO_PWM_BWD6 0b1010
#define LEGO_PWM_BWD5 0b1011
#define LEGO_PWM_BWD4 0b1100
#define LEGO_PWM_BWD3 0b1101
#define LEGO_PWM_BWD2 0b1110
#define LEGO_PWM_BWD1 0b1111


class LegoPower
{
  public:
    LegoPower();
    void sendSinglePwm(uint8_t channel, uint8_t output, uint8_t command);

  private:
    void _sendSingleOutput(uint8_t channel, uint8_t output, uint8_t mode, uint8_t command);
    void _sendRawMessage();
    uint8_t _getNextToggle();
    uint16_t _computeRawMessage(uint8_t nibble1, uint8_t nibble2, uint8_t nibble3);
    uint8_t _computeChecksum(uint8_t nibble1, uint8_t nibble2, uint8_t nibble3);
    bool _getMessageBit(uint8_t bitIndex);
    void _delayTransmission();
    void _sendStartBit();
    void _sendLowBit();
    void _sendHighBit();
    void _sendBit(uint16_t cycles);
    void _sendMark();
    void _sendPause(uint16_t cycles);
    bool _toggleBit;
    int16_t _rawMessage;
};

#endif
