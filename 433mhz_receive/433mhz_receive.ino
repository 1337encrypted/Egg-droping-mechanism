#include <VirtualWire.h>

const byte ledPin = 13;
const byte transmitPin = 12;
const byte receivePin = 11;
const byte transmitEnPin = 3;

int i;

//const byte bitsPerSec = 2000; //Transmittion rate

void setup()
{
    delay(1000);
    Serial.begin(9600);         // Debugging only
    
    Serial.println("setup");
    
    // Initialise the IO and ISR
    vw_set_tx_pin(transmitPin);
    vw_set_rx_pin(receivePin);
    vw_set_ptt_pin(transmitEnPin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);      // Bits per sec
    
    vw_rx_start();              // Start the receiver PLL running

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      digitalWrite(ledPin, HIGH); // Flash a light to show received good message
      //Message with a good checksum received, dump it.
              //Serial.print("Got: ");
              
              for (i = 0; i < buflen; i++)
              {
                  Serial.print(buf[i], DEC);
                  Serial.print(' ');
              }
              Serial.println();
      
      digitalWrite(ledPin, LOW);
    }
}
