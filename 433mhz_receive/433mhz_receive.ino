#include <VirtualWire.h>
#include "GLOBALS.h"

void setup()
{
    delay(200);
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
    attachInterrupt(digitalPinToInterrupt(pinA), encoderInterrupt, RISING);
//    attachInterrupt(digitalPinToInterrupt(pinB), decrementEncoder, RISING);
//    encoder.previousMillis = millis();

    buzz.alarm();
    led.blink(2);
    buzz.off();
}
void loop()
{   
    IBus.loop();

    CH5Val = IBus.readSwitch(4);
    motor.speed = (IBus.readChannel(2)-1000)*0.255;
    CH7Kill = IBus.readSwitch(5);

//    Serial.print(motor.speed);
//    Serial.print(" : ");
    if(encoderCount < 0)
    {
      prevStatus = motorStates::PASS;
      motorStatus = motorStates::STOP;
    }

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
//      else if (vw_get_message(buf, &buflen)) // Non-blocking
//      {
//        if(CH5Val == 1)
//        {
//          led.on();                              // Flash a light to show received good message
//          motorStatus = motorStates::ROTATEDOWN;
//          led.off();
//        }
//      }
     
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
        if(buf[0] == 'D' && CH5Val == 0)
        {
          led.on();                              // Flash a light to show received good message
          motorStatus = motorStates::ROTATEUP;
          led.off();
        }
        else if(buf[0] == 'U')
        {
          motor.brake();
          delay(2000);
        }
      }
//      if(CH5Val == 0)
//      {
//        led.on();                              // Flash a light to show received good message
//        motorStatus = motorStates::ROTATEUP;
//        led.off();
//      }
      
      break;

      case motorStates::ROTATEUP:
      motor.back();
      debugln("Motor up");

      if(CH7Kill == 1)
      {
        prevStatus = motorStates::ROTATEUP;
        motorStatus = motorStates::STOP;
      }
//      else if (limitSwitchObj.limitSwitchRead() == 0)
//      {
//          led.on();                              // Flash a light to show received good message
//          prevStatus = motorStates::PASS;
//          motorStatus = motorStates::STOP;
//          led.off();
//      }

//      else if (vw_get_message(buf, &buflen)) // Non-blocking
//      {
//        if(buf[0] == 'D' && CH5Val == 1)
//        {
//          led.on();                              // Flash a light to show received good message
//          motorStatus = motorStates::ROTATEDOWN;
//          led.off();
//        }
//      }      
      else if(CH5Val == 1)
      {
        led.on();                              // Flash a light to show received good message
        motorStatus = motorStates::ROTATEDOWN;
        led.off();
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
//  if(digitalRead(ch1.pinA) != digitalRead(ch1.pinB))
//  {
//    encoderCounter++;
//  }
//  else
//  {
//    encoderCounter--;
//  }
//}
//
//void decrementEncoder()
//{
//  //Decrement value for each pulse of the encoder 
//  if(digitalRead(ch1.pinA) == digitalRead(ch1.pinB))
//  {
//    encoderCounter++;
//  }
//  else
//  {
//    encoderCounter--;
//  }
//}

void encoderInterrupt() 
{
  if (digitalRead(ch1.pinA) == LOW)
  { 
    if (digitalRead(ch1.pinB) == LOW)
    {
     encoderCount--;
     if(encoderCount <= 3000)
      {
        prevStatus = motorStates::PASS;
        motorStatus = motorStates::STOP;
      }
    }
    else 
    {
      encoderCount++;
    }
  }
  else 
  {
    if (digitalRead(ch1.pinB) == LOW) 
    {
      encoderCount++;
    }
    else 
    {
      encoderCount--;
      if(encoderCount <= 500)
      {
        prevStatus = motorStates::PASS;
        motorStatus = motorStates::STOP;
      }
    }
  }
}
