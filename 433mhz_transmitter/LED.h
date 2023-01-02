/*Cannot create a .cpp file as inline prototypes need the function to be present in the same file as they are defined*/
#ifndef LED_h
#define LED_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class LED
{
  public:
  //ledPin pins for function feedback
  uint8_t ledPin;

  //Function prototypes
  inline LED() __attribute__((always_inline));
  inline LED(uint8_t) __attribute__((always_inline));
  inline ~LED() __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
  inline void on() __attribute__((always_inline));
  inline void off() __attribute__((always_inline));
  inline void toggle() __attribute__((always_inline));
  inline void blink(uint8_t) __attribute__((always_inline));
};

void LED::begin()
{
  // LEDPin pins set as output
  pinMode(this->ledPin, OUTPUT);
}

//parametrized constructor
LED::LED(uint8_t ledPin = 13)
{
  //Initilize the ledPin pins
  this->ledPin = ledPin;
  
  //Begin and enable happens after object construction
  begin();
}

//Destructor
LED::~LED()
{
  Serial.println("led object destroyed");
}

void LED::on()
{
  digitalWrite(this->ledPin, HIGH); 
}

void LED::off()
{
  digitalWrite(this->ledPin, LOW);
}

void LED::toggle()
{
  static unsigned long ledMillis = millis();    //Assigns the current snapshot of time only the first
                                              //time this code executes
  if(millis() - ledMillis > 300)
  {
    digitalWrite(this->ledPin, !digitalRead(this->ledPin));
    ledMillis = millis();  
  }
}

void LED::blink(uint8_t n)
{
  for(int i=0;i<n*2;i++)
  {
    toggle();
    delay(350);
  }
}
#endif  //END led_h
