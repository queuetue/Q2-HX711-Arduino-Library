#ifndef Q2HX711_h
#define Q2HX711_h
#include "Arduino.h"

class Q2HX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
    void setGain(byte gain = 128);
  public:
    Q2HX711(byte output_pin, byte clock_pin);
    virtual ~Q2HX711();
    bool readyToSend();
    long read();
};

#endif /* Q2HX711_h */
