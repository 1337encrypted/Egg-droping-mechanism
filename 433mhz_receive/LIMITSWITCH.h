#ifndef LIMITSWITCH_h
#define LIMITSWITCH_h

class limitSwitch
{
  private:
    uint8_t limitSwitchPin;
  public:
    uint8_t switchState;
    
    inline limitSwitch(uint8_t) __attribute__((always_inline));
    inline void begin() __attribute__((always_inline));
    inline uint8_t limitSwitchRead() __attribute__((always_inline));
};

limitSwitch::limitSwitch(uint8_t limitSwitchPin)
{
  this->limitSwitchPin = limitSwitchPin;
  begin();
}

void limitSwitch::begin()
{
  pinMode(limitSwitchPin, INPUT_PULLUP);
  this->switchState=HIGH;
}

uint8_t limitSwitch::limitSwitchRead()
{
  switchState = digitalRead(limitSwitchPin);  // read the switch state
  
  if (switchState == LOW)            // check if the switch is closed
  { 
  //Serial.println("Switch is closed");  // print a message
    return 0;
  } 
  else 
  {
  //Serial.println("Switch is open");  // print a message
    return 1;
  }
}


#endif //LIMITSWITCH_h
