  Library to use RFID tags with RDM630 module in UART usage.  
  Created by Danilo Queiroz Barbosa, August 26, 2016.  
  Member of electronicdrops.com  
  Released into the public domain.  


 The module is RDM630 and has two data formats: UART and Weigand. This library only works with UART data format.  
 The frequency is 125Khz and compatible with EM4100, TK4100, EM/TK4102, EM4200.  


### DATA FORMAT:

14 bytes

STX(0x02) DATA(10ASCII) LRC(2ASCII) ETX(0x03)


### PINOUT:
```
_____________________
|           P1 *****|
|                  1|
| 1                 |
|** P2        P3 ***|
|__________________1|
```

#### P1:
 - 1 - TX
 - 2 - RX
 - 3 -
 - 4 - GND
 - 5 - +5V (DC)

#### P2:
 - 1 - ANT1
 - 2 - ANT2

#### P3:
 - 1 - LED
 - 2 - +5V (DC)
 - 3 - GND

### Connections:
 -  Connect VCC, GND to the respective pins.
 -  Connect P1:1 of RDM630 module to Arduino pin 6 TX-RX.
 -  If you want to use interrupt, connect P3:1 of RDM630 module (LED pin) to Arduino Pin 2.
