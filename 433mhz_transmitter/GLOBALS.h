#include "CONFIG.h"
#include "LED.h"

//constexpr byte receivePin = 2;
//constexpr byte transmitEnPin = 3;
//const byte bitsPerSec = 2000; //Transmittion rate

//Actual connections
constexpr byte transmitPin = 12; //nano
// constexpr byte transmitPin = 0;    //attiny85
constexpr byte buttonPin = 2;  // pin number for the pushbutton
uint8_t buttonState = HIGH;  // variable to store the button state

//LED pin and object
constexpr byte ledPin = 13;
LED led(ledPin);

//Buzzer pin and object
constexpr byte buzzerPin = //not defined yet;
buzzer buzz(buzzerPin);

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
  SENDDOWN
};

volatile states txStatus = states::SENDDOWN;
