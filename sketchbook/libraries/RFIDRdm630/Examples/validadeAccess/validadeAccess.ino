/* validadeAccess.ino
 *
 * Created by Danilo Queiroz Barbosa, August 26, 2016.
 * Member of electronicdrops.com
 *
 * This example shows how to use the RFIDRdm630 library.
 * When a card is read, The system will check if the access
 * is granted or denied;
 *
 *
 *   This example code is in the public domain.

 */



#include "RFIDRdm630.h"

const int rxPin = 6;  // pin that will receive the data
const int txPin = 7;  // connection not necessary.

char validTAG[] = "A0721A7104BD";

RFIDtag  tag;  // a  RFIDtag object

RFIDRdm630 reader = RFIDRdm630(rxPin,txPin);    // the reader object.



void setup() {

  Serial.begin(9600);   // open the Serial for show data

}

void loop() {

  if (reader.isAvailable()){  // tests if a card was read by the module

    tag = reader.getTag();  // if true, then receives a pointer to an tag object


    if( strcmp(tag.getTag(),validTAG) == 0){
      Serial.println("ACCESS GRANTED.");
    }else{
      Serial.println("ACCESS DENIED.");
    }
    
  }
}
