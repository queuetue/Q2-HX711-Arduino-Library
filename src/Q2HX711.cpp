#include <Arduino.h>
#include "Q2HX711.h"

Q2HX711::Q2HX711(byte output_pin, byte clock_pin) {
  CLOCK_PIN  = clock_pin;
  OUT_PIN  = output_pin;
  GAIN = 1;
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);
}

Q2HX711::~Q2HX711() {
}

/**
 * Puts the chip in power down mode by setting the clock signal high.
 *
 * The HX711 will enter power down when PD_SCK is high for more then 60μs.
 */
void Q2HX711::powerDown() {
    digitalWrite(CLOCK_PIN, HIGH);
}

/**
 * Wakes the chip from power down mode by setting the clock signal low.
 *
 * When PD_SCK returns to low, the HX711 will reset and enter normal operation mode.
 * After a reset or power-down event, input selection is default to Channel A with a gain of 128.
 */
void Q2HX711::powerUp() {
    digitalWrite(CLOCK_PIN, LOW);
}

bool Q2HX711::readyToSend() {
  return digitalRead(OUT_PIN) == LOW;
}

void Q2HX711::setGain(byte gain) {
  switch (gain) {
    case 128: // Input Channel A
      GAIN = 1;
      break;
    case 64: // Input Channel A
      GAIN = 3;
      break;
    case 32: // Input Channel B
      GAIN = 2;
      break;
  }

  powerUp();
  read();
}

/**
 * Reads a value from the chip and returns the raw value.
 */
long Q2HX711::read() {
   while (!readyToSend());

  // Read 24 bit data, most significant bit first.
  byte data[3];
  for (byte j = 3; j--;) {
      data[j] = shiftIn(OUT_PIN, CLOCK_PIN, MSBFIRST);
  }

  // Set gain and input for next conversion by pulsing the clock signal 1 to 3 times.
  for (int i = 0; i < GAIN; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }

  // Collect the bytes in a signed integer
  long value = ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
  // The value read from the HX711 is in two's complement.
  // Normally the most significant bit of a 24 bit number represents 2^23.
  // But for a 24 bit two's complement number, the bit represents -2^23 (a negative value).
  if (value & (1L << 23)) {
      value -= (1L << 24);
  }
  return value;
}
