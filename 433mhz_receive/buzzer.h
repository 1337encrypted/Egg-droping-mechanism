/*Cannot create a .cpp file as inline prototypes need the function to be present in the same file as they are defined*/
#ifndef BUZZER_h
#define BUZZER_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class buzzer
{
  public: 
  uint8_t buzzpin;
    
  //Function prototype
  inline void begin() __attribute__((always_inline));
  inline buzzer(uint8_t) __attribute__((always_inline));
  inline ~buzzer() __attribute__((always_inline));
  inline void initBuzzer() __attribute__((always_inline));
  inline void deinitBuzzer() __attribute__((always_inline));
  inline void alarm() __attribute__((always_inline));
  inline void on() __attribute__((always_inline));
  inline void off() __attribute__((always_inline));
};

//Parametrized constructor
buzzer::buzzer(const uint8_t buzzpin = 10)
{
  //Initilize the buzzer
  this->buzzpin = buzzpin;

  //Begin and enable happens after object construction
  begin();
}

//Destructor
buzzer::~buzzer()
{
  Serial.println("buzzer object destroyed"); 
}

void buzzer::begin()
{
  //buzzer pin as output
  pinMode(this->buzzpin, OUTPUT);
}

void buzzer::initBuzzer()
{
  //InitBuzzer is for active buzzer
  tone(this->buzzpin, 2000, 100);
  delay(100);
  tone(this->buzzpin, 1000, 100);
  delay(200);
  noTone(this->buzzpin);
}

void buzzer::deinitBuzzer()
{
  //InitBuzzer is for active buzzer
  tone(this->buzzpin, 2000, 100);
  delay(150);
  tone(this->buzzpin, 1000, 100);
  delay(150);
  tone(this->buzzpin, 500, 100);
  delay(150);  
  noTone(this->buzzpin);
}

void buzzer::alarm()
{
  tone(this->buzzpin, 1000, 100);
}

void buzzer::off()
{
  noTone(this->buzzpin);
}

void buzzer::on()
{
  static unsigned long buzzMillis = millis();                   //Assigns the current snapshot of time only the first
                                                                //time this code executes
  if(millis() - buzzMillis > 10)
  {
    tone(this->buzzpin, 1000, 100);
    buzzMillis = millis();  
  }
}

#endif  //END BUZZER_h
