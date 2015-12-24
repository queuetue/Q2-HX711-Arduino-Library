# Queuetue HX711 Arduino Library

Copyright (c) 2015 Scott Russell (scott@queuetue.com), released under the MIT license.  
See the LICENSE file for licensing details.

A simple Arduino driver for the HX711 ADC.

The HX711 is a low-cost strain gauge amplifier produced by Avia Semiconductor.  Breakout boards are available for it by many producers, including the [Sparkfun 13230](https://www.sparkfun.com/products/13230).

The HX711 communicates with a non-i2c compliant two wire protocol and provides an all-in-one solution to load cell amplification with relatively low noise.

This library provides the code required to use an Arduino, the HX711 module and a strain gauge load cell to build a scale, force gauge or many other pressure or force sensitive projects.

The library has a single class, **Q2HX711** with two functions.  

## Class
The **Q2HX711** class takes two parameters on construction, the pin to use for data (output) and the pin to use to signal readiness (clock).

## Functions

Function  | Description
------------- | -------------
**read**  | Returns a long integer that is the current value of the HX711
**readyToSend**  | Returns a boolean indicating if the HX711 is prepared to send data.

## Example

Here is a simple example of using the HX711 on pins A2 and A3 to read a strain gauge and print it's current value:

```c++
#include <Q2HX711.h>
Q2HX711 hx711(A2, A3);
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.read());
  delay(500);
}
```
