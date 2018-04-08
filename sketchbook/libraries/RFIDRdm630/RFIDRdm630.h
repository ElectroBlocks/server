/*
  RFIDRdm630.h - Library for use RFID tags with RDM630 module in UART usage.
  Created by Danilo Queiroz Barbosa, August 26, 2016.
  Member of electronicdrops.com
  Released into the public domain.


 The module is RDM630 and has two data formats. UART and Weigand. This library only works with UART data format.
 The frequency is 125Khz and compatible with EM4100 TK4100 EM/TK4102, EM4200

DATA FORMAT:

14bytes

STX(0x02) DATA(10ASCii) LRC(2ASCii) ETX(0x03)


PINOUT:

_____________________
|           P1 *****|
|                  1|
| 1                 |
|** P2        P3 ***|
|__________________1|


P1:
1 - TX
2 - RX
3 -
4 - GND
5 - +5V (DC)

P2:
1 - ANT1
2 - ANT2

P3:
1 - LED
2 - +5V (DC)
3 - GND






*/





#ifndef RFIDRdm630_H
#define RFIDRdm630_H

#include <SoftwareSerial.h>
#include "Arduino.h"


const int _startTag = 2;  //Value corresponding the init of the transmission
const int _endTag = 3;    // value corresponding the end of the transmission
const static int _tagLength = 12;  // number of ascii characters of the tag
const int _totalLength = _tagLength + 2; // total length of transmission.


/*
* This class represents the TAG itself.
* methods:
* - getTag() -- return TAG in ASCii format
* - getCardNumber() -- return the number of the card, according with the protocol.
* - isValid() -- check if the tag read is valid or not.
*/

class RFIDtag{

  private:
    boolean _isValid;
    long _cardNumber;
    char _tag[_tagLength + 1];
    boolean validateTag();
  public:
    RFIDtag();
    char * getTag();
    boolean isValid();
    long getCardNumber();
    boolean setTag(char tag[]);


};



/*
* This class represents the reader module
* METHODS:
*  - isAvailable() checks if any TAG was read.
*  - getTag() -- returns a pointer to a RFIDtag object.
*/

class RFIDRdm630{

private:
    SoftwareSerial * _rfidSerial;
    boolean _isAvailable;

    RFIDtag  _RFIDtag;

public:
    RFIDRdm630(int rxPin, int txPin);
    boolean isAvailable();
    RFIDtag  getTag();
    void listen();

};



#endif
