#define DEBUG

// INCLUDES
#include <VirtualWire.h>
#include "GLOBALS.h"

void setup()
{
    #ifdef DEBUG
      //Serial connection used for debugging only
      Serial.begin(9600);
      debugln(F("setup"));
    #endif
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmitPin);
    vw_set_rx_pin(receivePin);
    vw_set_ptt_pin(transmitEnPin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(buttonPin, INPUT_PULLUP); // initialize the button pin as an input
    // pinMode(buttonPin, INPUT); // initialize the button pin as an input

    //UNO/Nano
    // INT 0 = Pin2
    // INT 1 = Pin3

    //Attiny85
    //INT 0 = PB2 || Pin7(hardware)
    attachInterrupt(digitalPinToInterrupt(buttonPin), isr, CHANGE);
    buzz.initBuzzer();
    led.on();
    led.off();
}

void loop()
{
  
  debugln(buttonState);
  
  switch(txStatus)
  {
    case states::SENDDOWN:    
    vw_send((uint8_t *)msgDown, msgLen);
    vw_wait_tx(); // Wait until the whole message is gone
    led.on();
    debugln("DOWN");
    break;

    case states::SENDUP:
    vw_send((uint8_t *)msgUp, msgLen);
    vw_wait_tx(); // Wait until the whole message is gone
    led.off();
    debugln("UP");
    break;
  }
}

void isr()
{
  buttonState=digitalRead(buttonPin);
  buttonState == LOW ? txStatus = states::SENDDOWN : txStatus = states::SENDUP;
}
