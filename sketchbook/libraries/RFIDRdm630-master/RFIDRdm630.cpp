/*
  RFIDRdm630.h - Library for use RFID tags with RDM630 module in UART usage.
  Created by Danilo Queiroz Barbosa, August 26, 2016.
  Member of electronicdrops.com
  Released into the public domain.
*/





#include <SoftwareSerial.h>
#include "RFIDRdm630.h"
#include "Arduino.h"
#include <stdio.h>


unsigned char charToHexDigit(char c)
{
  if (c >= 'A')
    return c - 'A' + 10;
  else
    return c - '0';
}

unsigned char stringToByte(char c[2])
{
  return charToHexDigit(c[0]) * 16 + charToHexDigit(c[1]);
}










RFIDRdm630::RFIDRdm630(int rxPin, int txPin) {

    _rfidSerial = new SoftwareSerial(rxPin, txPin);
    _rfidSerial->begin(9600);
    _isAvailable = false;
    //_RFIDtag = new RFIDtag();
}

boolean RFIDRdm630::isAvailable() {

    int bytesRead;
    char buff[_tagLength + 1];

    _isAvailable = false;

    if (_rfidSerial->available() >= _totalLength) {
        if (_rfidSerial->read() == _startTag) {
            bytesRead = 0;
            while (bytesRead < _tagLength) {
                int val = _rfidSerial->read();
                if ((val == _startTag) || (val == _endTag)) {
                    break;
                }
                buff[bytesRead] = val;
                bytesRead += 1;
            }

            if (_rfidSerial->read() == _endTag) {
                buff[bytesRead] = 0;

                _isAvailable  = true;
               _RFIDtag.setTag(buff);
            }
        }
    }
    return _isAvailable;
}




RFIDtag  RFIDRdm630::getTag() {

    return _RFIDtag;
}

void  RFIDRdm630::listen() {

    _rfidSerial->listen();
}



/*
 * Classe RFIDtag
 *
 */

RFIDtag::RFIDtag(){

  *_tag = NULL;
  _isValid = true;
  _cardNumber = 0;
}



char * RFIDtag::getTag(){

  return _isValid? _tag:NULL;

}
boolean RFIDtag::validateTag(){

char checksum[2] = {'0', '0'};
char checksumValue = '\0';
char piece[2] = {'0', '0'};
char hexValue = '\0';

 strncpy(checksum,_tag+10,2);
 checksumValue = stringToByte(checksum);

 for (int i = 0; i < _tagLength-2; i+=2){
   strncpy(piece,_tag+i,2);
   hexValue ^= stringToByte(piece);

   if ( i > 0 and  i < (_tagLength-2)){
    _cardNumber = _cardNumber << 8;
    _cardNumber += stringToByte(piece);

   }
 }

 return _isValid = (checksumValue == hexValue);


}

boolean RFIDtag::isValid(){
  return _isValid;
}

boolean RFIDtag::setTag(char tag[]){
  strcpy(_tag,tag);
  validateTag();

  if(_isValid){
    return true;
  }
  else{
    *_tag  = NULL;
    _cardNumber = 0;
    return false;
  }
}

long RFIDtag::getCardNumber(){

  return _isValid? _cardNumber:NULL;

}
