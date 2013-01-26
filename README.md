HArdalarm
=========

Haskell + Arduino alarm clock


Haskell
====
The Haskell module reads times and color values and sends serial commands to the Arduino.

Arduino
====

The Arduino code reads text commands to set the RGB LED color, or to play the alarm.

Commands are sent via the serial port, the sketch is derived from both Earthshine Electronics' [Arduino Starter Kit](http://www.earthshineelectronics.com/files/ASKManualRev5.pdf) and the original [Tone example](http://arduino.cc/en/Tutorial/Tone) on the Arduino website.

The RGB LED uses PWM pins 6,9 and 10, with pin 8 used for ground (power in my case).
The 8-ohm speaker is connected to pin 11 and GND on the Arduino, as seen below.

![arduinopins](https://raw.github.com/shapr/HArdalarm/master/arduinopins.png)
