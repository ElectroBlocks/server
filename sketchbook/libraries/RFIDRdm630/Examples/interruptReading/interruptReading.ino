/* interruptReading.ino
 *
 * Created by Danilo Queiroz Barbosa, August 26, 2016.
 * Member of electronicdrops.com
 *
 * This example shows how to use the RFIDRdm630 library.
 * using interrrupt to check if a card was read.
 *
 *
 *
 *   This example code is in the public domain.

 */



#include "RFIDRdm630.h"

const int irqPin = 0; // IRQ on pin 2.
void rfidAvailable(void);  // function that controls the reading;
volatile bool access = false; // check the access.

char validTAG[] = "A0721A7104BD"; // ACCESS GRANTED for this tag.

const int rxPin = 6;  // pin that will receive the data
const int txPin = 7;  // connection not necessary.


RFIDtag  tag;  // a RFIDtag object

RFIDRdm630 reader = RFIDRdm630(rxPin,txPin);    // the reader object.





void setup() {

  Serial.begin(9600);   // open the Serial for show data

  attachInterrupt(irqPin,rfidAvailable,FALLING);

}

void loop() {

  if(access)
    Serial.println("ACCESS GRANTED");
  else
    Serial.println("ACCESS DENIED");


  delay(2000);

}



void rfidAvailable(void)
{

  if (reader.isAvailable()){  // tests if a card was read by the module

    tag = reader.getTag();  // if true, then receives a pointer to an tag object


    if( strcmp(tag.getTag(),validTAG) == 0){
      access = true;
    }else{
      access = false;
    }

  }
}
