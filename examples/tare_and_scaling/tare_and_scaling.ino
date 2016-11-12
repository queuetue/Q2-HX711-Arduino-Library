// Example on how to use tare(), setScale() and readScaled() to get human readable values in eg gram.
// Please see the comments in Q2HX711.cpp for further details.
 
#include <Q2HX711.h>

const byte hx711_data_pin = A2;
const byte hx711_clock_pin = A3;

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  Serial.begin(9600);

  Serial.println("Waiting for chip to stabilize (1s)");
  delay(1000);
  Serial.println("Taking 10 samples to set tare...");
  hx711.tare(10);
  // Alternatively call setOffset();
  //hx711.setOffset(-31370);

  // Set scaling factor from raw values to wanted unit (eg gram)
  // You can use findScale() to see an average of the raw values.
  hx711.setScale(943.00);
}

void loop() {
  Serial.println(hx711.readScaled(), 2);
  delay(500);
}

void findScale() {
  hx711.setScale(1);
  Serial.println("Waiting for chip to stabilize (1s)");
  delay(1000);
  Serial.println("Place a known weight on the scale.");
  Serial.println("Now sampling 10x240 times...");
  for (byte count = 0; count < 10; count++) {
    float sum = 0;
    for (byte i = 0; i < 240; i++) {
      sum += hx711.readScaled();
    }
    sum /= 240;
    Serial.print("Value #");
    Serial.print(count);
    Serial.print(" is ");
    Serial.println(sum);
  }
  Serial.println("Now you can call setScale([found value] / [known weight]");
}
