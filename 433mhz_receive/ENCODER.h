#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {

public:
//  static constexpr uint8_t ENC_COUNT_REV = 3;
//  long previousMillis = 0;
//  long currentMillis = 0;
//  int rpm;
//  int interval = 1000;

  static constexpr uint8_t PPR = 7;               //Number of pulses produced by the encoder within a revolution
  static constexpr uint8_t gearRatio = 30;       //Gear ratio 18000/600.
  static constexpr uint8_t decodeNumber = 0;

  volatile long int encoderCount = 0;

  uint8_t pinA;
  uint8_t pinB;
  
  inline Encoder(int, int) __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
};

// Constructor:
Encoder::Encoder(int pinA, int pinB)
{
  this->pinA = pinA;
  this->pinB = pinB;
  begin();
}

// Method to initialize the encoder:
void Encoder::begin() 
{
  pinMode(this->pinA, INPUT_PULLUP);
  pinMode(this->pinB, INPUT_PULLUP);
}
#endif  // ENCODER_H
