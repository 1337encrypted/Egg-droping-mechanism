/*
 * BTS7960.h - Library for controlling a brushed DC motor using the BTS7960 43amp motor driver.
 * Created by Yash Herekar, August 31, 2022.
 * Released into the public domain.
 * Copyright [2022] [Yash Herekar]
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 */


#ifndef TB6612FNG_h
#define TB6612FNG_h

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255

class tb6612fng
{
    private:
    //variables for the 2 inputs, PWM input and the STDBY pin
    uint8_t IN1;
    uint8_t IN2;
    uint8_t PWM;
    uint8_t STDBY;
  
    //private functions that spin the motor front and back
    void begin();
    
    public:
    uint8_t speed;

    tb6612fng(uint8_t, uint8_t, uint8_t, uint8_t); // Default values set to -1
    inline void enable() __attribute__((always_inline));                       //The enable function takes it out of standby
    inline void front() __attribute__((always_inline));
    inline void back() __attribute__((always_inline));
    inline void brake() __attribute__((always_inline));                        //Stops motor by setting both input pins high
    inline void standby() __attribute__((always_inline));                      //set the chip to standby mode.
};

tb6612fng::tb6612fng(uint8_t IN1, uint8_t IN2, uint8_t PWM, uint8_t STDBY)
{
    this->IN1 = IN1;
    this->IN2 = IN2;
    this->PWM = PWM;
    this->STDBY = STDBY;
    this->speed = DEFAULTSPEED;
    begin();
    enable();
}

void tb6612fng::begin()
{
    pinMode(this->IN1, OUTPUT);
    pinMode(this->IN2, OUTPUT);
    pinMode(this->PWM, OUTPUT);
    pinMode(this->STDBY, OUTPUT);
}

void tb6612fng::enable()
{
  digitalWrite(this->STDBY, HIGH);
}

void tb6612fng::standby()
{
   digitalWrite(this->STDBY, LOW);
}

void tb6612fng::front()
{
   digitalWrite(this->IN1, HIGH);
   digitalWrite(this->IN2, LOW);
   analogWrite(this->PWM, this->speed);
}

void tb6612fng::back()
{
   digitalWrite(this->IN1, LOW);
   digitalWrite(this->IN2, HIGH);
   analogWrite(this->PWM, this->speed);
}

void tb6612fng::brake()
{
   digitalWrite(this->IN1, LOW);
   digitalWrite(this->IN2, LOW);
   analogWrite(this->PWM,0);
}

#endif //TB6612FNG_h
