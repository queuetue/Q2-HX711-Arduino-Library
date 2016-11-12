#include <Q2HX711.h>

// Simple example: Returns raw values from the HX711 chip.
// See the example tare_and_scaling for a more complete example.

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.read());
  delay(500);
}
