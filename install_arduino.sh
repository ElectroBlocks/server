
#!/bin/sh

## Install Libaries
npm install

## The folder for all the ardunio sketches
mkdir sketches

export PATH=$PATH:/var/www/html/bin

## Install The Arduino Library
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

## Installing boards
arduino-cli core install arduino:avr
arduino-cli core install arduino:megaavr

# Installing github library
arduino-cli lib install "Adafruit NeoPixel"
arduino-cli lib install "LiquidCrystal I2C"
arduino-cli lib install "Adafruit Motor Shield library"
arduino-cli lib install Servo
arduino-cli lib install IRremote
arduino-cli lib install "DHT sensor library"


# Installing a github library for now

## LED MATRIX
wget https://github.com/shaai/Arduino_LED_matrix_sketch/archive/master.zip
mkdir /root/Arduino/libraries/LedControlMS
mv master.zip  /root/Arduino/libraries/LedControlMS/LedControlMS.zip
cd /root/Arduino/libraries/LedControlMS 
unzip LedControlMS.zip
mv Arduino_LED_matrix_sketch-master/* ./
rm -rf Arduino_LED_matrix_sketch-master
rm -rf LedControlMS.zip
cd /var/www/html

## RFID Library

wget https://github.com/electronicdrops/RFIDRdm630/archive/master.zip
mkdir /root/Arduino/libraries/RFIDRdm630
mv master.zip  /root/Arduino/libraries/RFIDRdm630/RFIDRdm630.zip
cd /root/Arduino/libraries/RFIDRdm630 
unzip RFIDRdm630.zip
mv RFIDRdm630-master/* ./
rm -rf RFIDRdm630-master
rm -rf RFIDRdm630.zip
cd /var/www/html




