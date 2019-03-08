# nvro
Code for a multiple-sensor envrionmental monitoring system using arduino.

The Arduino is set up with:
 - DHT11 Temp/Humidity sensor
 - MQ137 Ammonia (NH3) gas sensor
 - Light Sensor
 - 128x64 OLED
 
Informational documents:
 - OLED: https://learn.adafruit.com/monochrome-oled-breakouts/wiring-128x64-oleds/
 - DHT11: http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
 - MQ137: https://www.sainsmart.com/products/mq-137-ammonia-detection-sensor-nh3-gas-sensor/
 - Light sensor: https://learn.adafruit.com/photocells/using-a-photocell

The OLED is connected to GND(POWER)[->GND], 5V(POWER)[->VCC], and D8[->RES], D9[->DC], D10[->CS], D11[->D1], & D13[->D0].
The DHT11 is connected to GND, 5V, & D7.
The light sensor is connected 5V, GND(POWER), & A0.
The MQ137 is connected D-GND, D4, & A5.

The program outputs to serial so a python program (coming soon) can read the values and then store in a database and plot it to a webpage.

*NOTE: The code I have so far for the MQ137 isn't nearly perfect or at all accurate. I did get it to respond and output something, which is an improvement from before.
