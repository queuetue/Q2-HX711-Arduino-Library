#include <Arduino.h>
#include "Q2HX711.h"

Q2HX711::Q2HX711(byte output_pin, byte clock_pin) {
  CLOCK_PIN  = clock_pin;
  OUT_PIN  = output_pin;
  GAIN = 1;
  OFFSET = 0;
  SCALE = 1;
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);
}

Q2HX711::~Q2HX711() {
}

bool Q2HX711::readyToSend() {
  return digitalRead(OUT_PIN) == LOW;
}

void Q2HX711::setGain(byte gain) {
  switch (gain) {
    case 128:
      GAIN = 1;
      break;
    case 64:
      GAIN = 3;
      break;
    case 32:
      GAIN = 2;
      break;
  }

  digitalWrite(CLOCK_PIN, LOW);
  read();
}

long Q2HX711::read() {
   while (!readyToSend());

  byte data[3];

  for (byte j = 3; j--;) {
      data[j] = shiftIn(OUT_PIN,CLOCK_PIN, MSBFIRST);
  }

  // set gain
  for (int i = 0; i < GAIN; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }

  data[2] ^= 0x80;
  return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
}

/**
 * Reads a number of values from the chip and calculates the average.
 * The value is adjusted for offset and scale before it is returned.
 */
float Q2HX711::readScaled(byte samples) {
    long sum = 0;
    for (byte i = 0; i < samples; i++) {
        sum += read();
    }
    return (((long) sum / samples) - OFFSET) / SCALE;
}

/**
 * Sets the raw offset from the average of a number of current reading.
 */
void Q2HX711::tare(byte samples) {
    long sum = 0;
    for (byte i = 0; i < samples; i++) {
        sum += read();
    }
    OFFSET = sum / samples;
}

/**
 * Sets a new raw offset from 0.
 *
 * Example: If read() returns -43263 with no load on the scale, you should call setOffset(-43263).
 */
void Q2HX711::setOffset(const long offset) {
    OFFSET = offset;
}

/**
 * Sets a new scaling factor for readScaled.
 *
 * Example: If read() returns 6500123 (after offset correction) with a 100kg load on the scale,
 * you could call setScale(6500.123) to make readScaled() return the weight in kilograms.
 */
void Q2HX711::setScale(const float scale) {
    SCALE = scale;
}
