#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {

private:
  uint8_t pinA;
  uint8_t pinB;

public:
  constexpr uint8_t ENC_COUNT_REV = 3;
  long previousMillis = 0;
  long currentMillis = 0;
  int rpm;
  int interval = 1000;
  inline Encoder(int, int) __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
};

// Constructor:
Encoder::Encoder(int pinA = -1, int pinB = -1)
{
  this->pinA = pinA;
  this->pinB = pinB;
  begin();
}

// Method to initialize the encoder:
void Encoder::begin() {
  pinMode(this->pinA, INPUT_PULLUP);

  if(pinB != -1)
    pinMode(this->pinB, INPUT_PULLUP);

  this->position = 0;
  this->state = 0;
  this->lastA = digitalRead(this->pinA);

  if(pinB != -1)
    this->lastB = digitalRead(this->pinB);
}
#endif  // ENCODER_H
