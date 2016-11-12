#ifndef Q2HX711_h
#define Q2HX711_h
#include "Arduino.h"

class Q2HX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
    long OFFSET;
    float SCALE;
    void setGain(byte gain = 128);
  public:
    Q2HX711(byte output_pin, byte clock_pin);
    virtual ~Q2HX711();
    bool readyToSend();
    long read();
    float readScaled(byte samples = 1);
    void tare(byte samples = 1);
    void setOffset(const long offset);
    void setScale(const float scale);
};

#endif /* Q2HX711_h */
