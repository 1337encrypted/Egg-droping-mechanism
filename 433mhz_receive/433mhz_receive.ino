#include <VirtualWire.h>
#include "GLOBALS.h"

void setup()
{
    delay(1000);
    Serial.begin(115200);
    IBus.begin(Serial);
    
    Serial.println("setup");
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmitPin);
    vw_set_rx_pin(receivePin);
    vw_set_ptt_pin(transmitEnPin);
    vw_set_ptt_inverted(true);      // Required for DR3100
    vw_setup(2000);                 // Bits per sec
    
    vw_rx_start();                  // Start the receiver PLL running

    led.blink(2);

    //Encoder 
    attachInterrupt(digitalPinToInterrupt(pinA), incrementEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(pinA), decrementEncoder, FALLING);
    encoder.previousMillis = millis();
}
void loop()
{    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      if(buf[0] == 'U')
      {
        led.on();                              // Flash a light to show received good message
        motorStatus = motorStates::ROTATEUP;
        led.off();
      }
    }

    switch(motorStatus)
    {
      case motorStates::READCHANNEL:
      IBus.loop();
      CH4Value = IBus.readSwitch(4);
      debugln(CH4Value);
      //CH6 = IBus.readSwitch(6);
      
      if(CH4Value == true)
      {
        motorStatus = motorStates::ROTATEDOWN;
        break;
      }
      break;
      
      case motorStates::ROTATEDOWN:
      motor.front();
      debugln("Motor down");
      break;

      case motorStates::ROTATEUP:
      motor.back();
      debugln("Motor up");
      break;

      case motorStates::STOP:
      motor.brake();
      debugln("Motor stop");
      motorStatus = motorStates::PASS;
      break;

      case motorStates::PASS:
      //Do nothing
      break;
    }
}

void incrementEncoder()
{
  //Increment value for each pulse of the encoder
  ++encoderValue;
}

void decrementEncoder()
{
  //Decrement value for each pulse of the encoder 
  --encoderValue;
  if(encoderValue <= 0)
  {
    motorStatus = motorStates::STOP;
  }
}
