#include "config.h"
#include "tb6612fng.h"
#include "encoder.h"
#include "FlySkyIBus.h"
#include "led.h"
//#include "limitSwitch.h"
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
constexpr byte pinB = 2;

//Encoder object
Encoder ch1(pinA, pinB);
unsigned long encoderCount = 0;
//long motorRpm = 0;

//Transmitter channel read and object
uint8_t CH5Val;
//uint16_t CH6Speed;
uint8_t CH7Kill;

//FlySky
FlySkyIBus IBus;

//LimitSwitch and object
//constexpr uint8_t limitSwitchPin = 7;
//limitSwitch limitSwitchObj(limitSwitchPin);

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
motorStates prevStatus = motorStatus;

//
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
