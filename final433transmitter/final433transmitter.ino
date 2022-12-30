#define DEBUG

// INCLUDES
#include <VirtualWire.h>

const byte receivePin = 2;
const byte transmitEnPin = 3;
//const byte bitsPerSec = 2000; //Transmittion rate

//Actual connections
const byte transmitPin = 12;
const byte ledPin = 13;
const byte buttonPin = 4;  // pin number for the pushbutton
bool buttonState = HIGH;  // variable to store the button state

//For long array transmittion
//byte count = 1;
//char msg[0] = {'1'};
//const int msglen = sizeof(msg)/sizeof(msg[0]);

char msg = '1';
const int msglen = 1;

void setup()
{
    #ifdef DEBUG
      //Serial connection used for debugging only
      Serial.begin(9600);
      Serial.println(F("setup"));
    #endif
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmitPin);
    vw_set_rx_pin(receivePin);
    vw_set_ptt_pin(transmitEnPin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); // initialize the button pin as an input:
}

void loop()
{
  buttonState = digitalRead(buttonPin);         // read the button state:
  if (buttonState == LOW) 
  {
    //msg[0] = count;
    digitalWrite(ledPin, HIGH); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, msglen);
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(ledPin, LOW);
    //count = count + 1;
  }
  delay(10);
}
