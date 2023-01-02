#include "CONFIG.h"
#include "tb6612fng.h"
#include "ENCODER.h"
#include "FlySkyIBus.h"
#include "LED.h"

//virtual Wire pins
constexpr byte transmitPin = 12;
constexpr byte receivePin = 11;
constexpr byte transmitEnPin = 3;
//const byte bitsPerSec = 2000; //Transmittion rate

//Led pin
constexpr byte ledPin = 13;
//LED object
LED led(ledPin);

//motor pins
constexpr byte IN1 = A0;
constexpr byte IN2 = A1;
constexpr byte PWM = 5;
constexpr byte STDBY = A2;

//Create motor object
tb6612fng motor(IN1,IN2,PWM,STDBY);

//Encoder switches
constexpr byte pinA = 3;
//constexpr byte pinB = 4;
volatile long encoderValue=0;

//Encoder object
Encoder encoder(pinA);


//Transmitter channel read
constexpr byte CH4 = 6;
bool CH4Value = false;

//Flysky object
FlySkyIBus IBus;


enum class motorStates : byte
{
  READCHANNEL,
  ROTATEUP,
  ROTATEDOWN,
  STOP,
  PASS
};
motorStates motorStatus = motorStates::READCHANNEL;


//
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
