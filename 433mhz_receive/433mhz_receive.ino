#include <VirtualWire.h>
#include "GLOBALS.h"

void setup()
{
    delay(500);
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

    //Encoder 
//    attachInterrupt(digitalPinToInterrupt(pinA), incrementEncoder, RISING);
//    attachInterrupt(digitalPinToInterrupt(pinA), decrementEncoder, FALLING);
//    encoder.previousMillis = millis();

    buzz.alarm();
    led.blink(2);
    buzz.off();
}
void loop()
{   
    IBus.loop();

    CH5Val = IBus.readSwitch(4);
    CH6Speed = IBus.readChannel(2);
    CH7Kill = IBus.readSwitch(5);

    switch(motorStatus)
    {      
      case motorStates::PASS:
      debugln("PASS");
      
      if(CH7Kill == 1)
      {
        prevStatus = motorStates::PASS;
        motorStatus = motorStates::STOP;
      }
      else if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'D' && CH5Val == 1)
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

      if(CH7Kill == 1)
      {
        prevStatus = motorStates::ROTATEDOWN;
        motorStatus = motorStates::STOP;
      }
      else if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'U' || (buf[0] == 'D' && CH5Val == 0))
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

      if(CH7Kill == 1)
      {
        prevStatus = motorStates::ROTATEUP;
        motorStatus = motorStates::STOP;
      }
      else if (limitSwitchObj.limitSwitchRead() == 0)
      {
          led.on();                              // Flash a light to show received good message
          prevStatus = motorStates::PASS;
          motorStatus = motorStates::STOP;
          led.off();
      }
      else if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        if(buf[0] == 'D' && CH5Val == 1)
        {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::ROTATEDOWN;
          led.off();
        }
      }      
      break;

      case motorStates::STOP:
      motor.brake();
      debugln("Motor stop");

      if(CH7Kill == 0)
      {
        led.on();
        motorStatus = prevStatus;
        led.off();
      }
      break;
    }
}

//void incrementEncoder()
//{
//  //Increment value for each pulse of the encoder
//  ++encoderValue;
//}
//
//void decrementEncoder()
//{
//  //Decrement value for each pulse of the encoder 
//  --encoderValue;
//  if(encoderValue <= 0)
//  {
//    prevStatus = motorStates::PASS;
//    motorStatus = motorStates::STOP;
//  }
//}
