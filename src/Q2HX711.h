#ifndef Q2HX711_h
#define Q2HX711_h
#include "Arduino.h"

class Q2HX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
    bool pinsConfigured;

  public:
    Q2HX711(byte output_pin, byte clock_pin);
    virtual ~Q2HX711();
    bool readyToSend();
    void setGain(byte gain = 128);
    long read();
} // Semicolon removed due to the error :: multiple types in one declaration

#endif /* Q2HX711_h */
