#include <VirtualWire.h>
#include "GLOBALS.h"

void setup()
{
    delay(1000);
    Serial.begin(115200);
    
    Serial.println("setup");
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmitPin);
    vw_set_rx_pin(receivePin);
    vw_set_ptt_pin(transmitEnPin);
    vw_set_ptt_inverted(true);      // Required for DR3100
    vw_setup(2000);                 // Bits per sec
    
    vw_rx_start();                  // Start the receiver PLL running

    //Encoder 
    attachInterrupt(digitalPinToInterrupt(pinA), incrementEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(pinA), decrementEncoder, FALLING);
    encoder.previousMillis = millis();

    buzz.alarm();
    led.blink(2);
    buzz.off();
}
void loop()
{    
    switch(motorStatus)
    {      
      case motorStates::PASS:
      debugln("Pass");
      
      if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'D' && CH5.readSwitch() == true)
        {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::ROTATEDOWN;
          led.off();
        }
      }
      break;
      
      case motorStates::ROTATEDOWN:
      motor.front();
      debugln("Motor down");
      
      if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'U' || (buf[0] == 'D' && CH5.readSwitch() == false))
        {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::ROTATEUP;
          led.off();
        }
      }
      
      break;

      case motorStates::ROTATEUP:
      motor.back();
      debugln("Motor up");

      if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'D' && CH5.readSwitch() == true)
        {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::ROTATEDOWN;
          led.off();
        }
      }
      
      if (limitSwitchObj.limitSwitchRead() == 0)
      {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::STOP;
          led.off();
      }
      
      break;

      case motorStates::STOP:
      motor.brake();
      debugln("Motor stop");

      if(CH5.readSwitch() == false)
      {
        led.on();
        motorStatus = motorStates::PASS;
        led.off();
      }
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
