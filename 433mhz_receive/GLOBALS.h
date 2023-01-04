#include "config.h"
#include "tb6612fng.h"
#include "encoder.h"
#include "flySky.h"
#include "led.h"
#include "limitSwitch.h"
#include "buzzer.h"

//virtual Wire pins
constexpr byte transmitPin = 12;
constexpr byte receivePin = 11;
//constexpr byte transmitEnPin = 3;
constexpr byte transmitEnPin = 10;
//const byte bitsPerSec = 2000; //Transmittion rate

//Led pin
constexpr byte ledPin = 13;
//LED object
LED led(ledPin);

//motor pins
constexpr byte IN1 = A1;
constexpr byte IN2 = A0;
constexpr byte STDBY = A2;
constexpr byte PWM = 5;

//Create motor object
tb6612fng motor(IN1,IN2,PWM,STDBY);

//Encoder switches
constexpr byte pinA = 3;
//constexpr byte pinB = 2;
volatile long encoderValue=0;

//Encoder object
Encoder encoder(pinA);


//Transmitter channel read and object
constexpr uint8_t CH5Pin = 6;
//constexpr uint8_t CH6Pin = 9;

FlySky CH5(CH5Pin);
//FlySky CH6(CH6Pin);


//LimitSwitch and object
constexpr uint8_t limitSwitchPin = 7;
limitSwitch limitSwitchObj(limitSwitchPin);

//Buzzer
constexpr uint8_t buzzPin = 10;
buzzer buzz(buzzPin);

enum class motorStates : byte
{
  PASS,
  ROTATEUP,
  ROTATEDOWN,
  STOP
};
motorStates motorStatus = motorStates::PASS;


//
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
