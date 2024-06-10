/*
 * IRremote: IRsendRawDemo - demonstrates sending IR codes with sendRaw
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * IRsendRawDemo - added by AnalysIR (via www.AnalysIR.com), 24 August 2015
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off. 
 * Hex Value: 0x20DF10EF, 32 bits
 * 
 * It is more efficient to use the sendNEC function to send NEC signals. 
 * Use of sendRaw here, serves only as an example of using the function.
 * 
 */


#include <IRremote.h>

IRsend irsend;

  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int samsungONOFF[] = {4500,4450, 600,1650, 550,1650, 550,1650, 600,550, 550,550, 550,550, 550,550, 600,550, 550,1650, 550,1650, 600,1650, 550,550, 550,550, 550,550, 600,550, 550,550, 550,550, 550,1650, 600,550, 550,550, 550,550, 550,550, 600,550, 550,550, 550,1650, 550,550, 600,1650, 550,1650, 550,1700, 550,1650, 550,1650, 600,1650, 550};
  //one
  unsigned int  one[] = {450,250, 100,350, 100,700, 100,500, 100,650, 100,350, 100,350, 100,350, 100,350, 100,650, 100,700, 100,500, 100,850, 100,350, 50,350, 100,350, 100,500, 100};
  unsigned int  oneone[] = {400,300, 100,350, 50,700, 100,500, 100,700, 100,350, 50,350, 100,350, 100,350, 100,350, 100,650, 100,550, 50,850, 100,350, 100,350, 100,350, 100,500, 100};
  unsigned int  oneoneone[] = {450,250, 100,350, 100,650, 100,500, 100,700, 100,350, 100,350, 100,300, 100,350, 100,700, 100,650, 100,500, 100,850, 100,350, 100,350, 100,350, 100,500, 100};
  
  //two
  unsigned int  two[] = {450,250, 100,350, 100,650, 100,550, 100,650, 100,350, 100,350, 100,350, 100,350, 100,300, 100,700, 100,500, 100,850, 100,350, 100,300, 100,350, 100,700, 100};  // UNKNOWN 5EDD6D4D
  unsigned int  twotwo[] = {400,300, 100,300, 100,700, 100,500, 100,700, 100,300, 100,350, 100,350, 100,350, 100,650, 100,700, 100,500, 100,850, 100,350, 100,350, 100,300, 100,700, 100};  // UNKNOWN 47991122
  unsigned int  twotwotwo[] = {400,300, 100,300, 100,700, 100,500, 100,700, 100,300, 100,350, 100,350, 100,350, 100,350, 100,650, 100,500, 100,850, 100,350, 100,350, 100,350, 100,650, 100};  // UNKNOWN CF6A91DA
  
  //three
  unsigned int  three[] = {450,250, 100,350, 100,650, 100,550, 100,650, 100,350, 100,350, 100,350, 100,300, 100,700, 100,650, 100,550, 100,800, 100,350, 100,350, 100,350, 100,850, 100};  // UNKNOWN 6FF21EA
  unsigned int  threethree[] = {400,300, 100,350, 100,650, 100,500, 100,700, 100,350, 100,300, 100,350, 100,350, 100,350, 100,650, 100,550, 100,800, 100,350, 100,350, 100,350, 100,850, 100};  // UNKNOWN E5E157ED
  unsigned int  threethreethree[] = {400,300, 100,350, 50,700, 100,500, 100,700, 100,350, 50,350, 100,350, 100,350, 100,650, 100,700, 100,500, 100,850, 100,350, 100,350, 100,300, 100,850, 100};  // UNKNOWN E8A3F736

  //eight
  unsigned int eight[35] = {450,250, 100,350, 100,650, 100,550, 50,700, 100,350, 100,350, 100,350, 100,300, 100,350, 100,700, 100,500, 100,850, 100,350, 50,350, 100,700, 100,350, 100};  // UNKNOWN 556F02B7
  unsigned int  eighteight[35] = {400,300, 100,300, 100,700, 100,500, 100,700, 50,350, 100,350, 100,350, 100,350, 100,650, 100,700, 100,500, 100,850, 100,350, 100,350, 50,700, 100,350, 100};  // UNKNOWN 84884841
  unsigned int  eighteighteight[35] = {450,250, 100,350, 100,700, 100,500, 100,650, 100,350, 100,350, 100,350, 100,350, 100,350, 50,700, 100,500, 100,850, 100,350, 100,350, 100,650, 100,350, 100};  // UNKNOWN 13590F3A



void setup()
{
Serial.begin(9600); 
}

void loop() {

  //irsend.sendRaw(samsungONOFF, sizeof(samsungONOFF) / sizeof(samsungONOFF[0]), khz); //Note the approach used to automatically calculate the size of the array.
   irsend.sendRaw( one, sizeof(one) / sizeof(one[0]), khz);
  //irsend.sendRaw(three, sizeof(three) / sizeof(three[0]), khz);
 // irsend.sendRaw(eight, sizeof(eight) / sizeof(eight[0]), khz);
Serial.println("Signal Sent");
  delay(15000); //In this example, the signal will be repeated every 5 seconds, approximately.
}
