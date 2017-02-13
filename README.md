# longboardLight1
LED longboard light setup, by Thurstan

Repository is an Arduino project

### Concept
Lighting system for a longboard. Using sensors to control brake lights, indicator lights and ground tracking effects.

### Equipment
#### Hardware
- Arduino Mini Pro board
  * 5v
  * ATmega328
  * 16 MHz clock speed
  * 1K EEPROM
- WS2812B addressable LED strips
  * pixel order = GRB
- Movement sensors
  * ~~ADXL335~~
  * MPU6050 (GY-521 breakout board)
- Wheel tracking sensor
  * probably hall effect sensor and magnets
- 7.4V LiPo Battery
- >6V to 5V Convertor
  
#### Software
- Arduino
- FastLED library  https://github.com/FastLED/FastLED
- I2CdevLib  https://www.i2cdevlib.com  https://github.com/jrowberg/i2cdevlib
- VVVV

### Licence
- Written by MTS Standish (Thurstan|mattKsp) 2016
- Released under GNU GPLv3 (see LICENCE file)

This software is provided on an "AS-IS-BASIS"

#### Contains code based on:
- I2CdevLib by Jeff Rowberg Copyright (c) 2011
 * https://github.com/jrowberg/i2cdevlib/blob/master/Arduino/MPU6050/examples/MPU6050_raw/MPU6050_raw.ino
- Arduino MPU6050 auto-calibration script by Luis Ródenas  <luisrodenaslorda@gmail.com>
 * http://42bots.com/tutorials/arduino-script-for-mpu-6050-auto-calibration/ 
 * (also) Based on the I2Cdev library and previous work by Jeff Rowberg <jeff@rowberg.net>

### Reference
https://github.com/FastLED/FastLED/wiki/Pixel-reference <br> 
https://www.arduino.cc/en/Main/ArduinoBoardProMini <br> 
https://www.arduino.cc/en/Guide/Troubleshooting#upload <br> 
https://github.com/FastLED/FastLED/wiki/Pixel-reference <br> 
http://forum.arduino.cc/index.php?topic=140494.0 <br> 
http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/ <br> 
http://42bots.com/tutorials/arduino-script-for-mpu-6050-auto-calibration/ <br> 
https://www.i2cdevlib.com/devices/mpu6050#source <br> 
https://www.i2cdevlib.com/docs/html/class_m_p_u6050.html <br> 
http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/ <br> 
http://engineering.stackexchange.com/questions/3348/calculating-pitch-yaw-and-roll-from-mag-acc-and-gyro-data <br> 
http://www.nxp.com/assets/documents/data/en/application-notes/AN3461.pdf <br> 
http://theboredengineers.com/2012/09/the-quadcopter-get-its-orientation-from-sensors/ <br> 
