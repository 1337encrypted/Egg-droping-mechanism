#include "CONFIG.h"
#include "LED.h"

const byte receivePin = 2;
const byte transmitEnPin = 3;
//const byte bitsPerSec = 2000; //Transmittion rate

//Actual connections
const byte transmitPin = 12; //nano
// const byte transmitPin = 0;    //attiny85
const byte ledPin = 13;
const byte buttonPin = 3;  // pin number for the pushbutton
//volatile bool buttonState = HIGH;  // variable to store the button state

//LED object
LED led(ledPin);

//For long array transmittion
//byte count = 1;
//char msg[] = {'1'};
//const int msglen = sizeof(msg)/sizeof(msg[0]);

char msgDown[] = {'D'};
char msgUp[] = {'U'};
const uint8_t msgLen = 1;

enum class states : byte
{
  SENDUP,
  SENDDOWN,
  SENDNTHG
};

volatile states txStatus = states::SENDDOWN;
