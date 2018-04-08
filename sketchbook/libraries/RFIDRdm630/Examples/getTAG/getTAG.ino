/* getTAG.ino
 *
 * Created by Danilo Queiroz Barbosa, August 26, 2016.
 * Member of electronicdrops.com
 *
 * This example shows how to use the RFIDRdm630 library.
 * When a card is read, an ASCII TAG and a Card Number
 * will be show in the Serial.*
 *
 *
 *   This example code is in the public domain.

 */







#include "RFIDRdm630.h"

const int rxPin = 6;  // pin that will receive the data
const int txPin = 7;  // connection not necessary.

//char * tag;

RFIDtag  tag;  // RFIDtag object

RFIDRdm630 reader = RFIDRdm630(rxPin,txPin);    // the reader object.



void setup() {

  Serial.begin(9600);   // open the Serial for show data

}

void loop() {

  if (reader.isAvailable()){  // tests if a card was read by the module

    tag = reader.getTag();  // if true, then receives a tag object

    Serial.print("TAG: ");
    Serial.print(tag.getTag());   // get TAG in ascii format
    Serial.print(" Card Number: ");
    Serial.println(tag.getCardNumber());  // get cardNumber in long format
    Serial.println();

  }
}
