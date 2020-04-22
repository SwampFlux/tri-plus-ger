/**
ATMEGA328 AU pin configuration & assignment

pins on chip start at dot and go coutner-clockwise

d pins: digital 0-7
c pins: analog 0-7
b pins: digital 8-13

  1  pd3 - top cv out
  2  pd4 - left cv out
  3  GND
  4  VCC
  5  GND
  6  VCC
  7  pb6 - crystal 1
  8  pb7 - crystal 2

  9  pd5 - right cv out
  10 pd6 - alt button
* 11 pd7
* 12 pb0 - 8
* 13 pb1 - 9
* 14 pb2 - 10
* 15 pb3 MOSI - 11 - serial data?
* 16 pb4 MISO - 12 

* 17 pb5 SCK - 13 - serial clock?
  18 AVCC
  19 adc6 - roll rate
  20 AREF -
  21 GND -
* 22 adc7 - ?
* 23 pc0 adc0
  24 pc1 adc1 - play/pause

  25 pc2 adc2 - retrigger
  26 pc3 adc3 - roll
* 27 pc4 adc4 - ?
* 28 pc5 adc5 - ?
* 29 pc6 RESET
  30 pd0 - top button
  31 pd1 - left button
  32 pd2 - right button
*/

#include <SPI.h>

#define clockOut_pin 7

#define buttonTop_pin   0
#define buttonLeft_pin  1
#define buttonRight_pin 2
#define ledTop   3
#define ledLeft  4
#define ledRight 5

#define alt 6

#define playPause_analog 1
#define retrigger_analog 2
#define roll_analog      3
//analog 4 not used?


int search_start = 7;
int search_end = 13;

int t = 100;

int checklist[7] = {7,8,9,10,11,12,13};

void setup(){
  for (int i=search_start; i<=search_end; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(clockOut_pin, OUTPUT);
  SPI.begin();
}

void digitalProbe(){
  for (int i=search_start; i<=search_end; i++) {
    digitalWrite(i, HIGH);
    delay(t/2);
    digitalWrite(i, LOW);
    delay(t/2);
  }
}

void analogBlink(){
  int a = analogRead(7);
  digitalWrite(clockOut_pin, HIGH);
  delay( a + 20 );
  digitalWrite(clockOut_pin, LOW);
  delay( a + 20 );
}

int tryLatch = 0;
int counter = 0;

void loop() {
//  digitalWrite(checklist[tryLatch], HIGH);
//  SPI.transfer(counter);
//  digitalWrite(checklist[tryLatch], LOW);
//  delay(t);
//  if(counter >= 120){
//    counter = 0;
//    tryLatch++;
//    if(tryLatch >=7) tryLatch = 0;
//  }

    for(int i=0; i<8; i++) {
      digitalWrite(checklist[i], random(1));
    }
    delay(t);
    
//  digitalProbe();
//  bool on = false;
//  for (int i=search_start; i<=search_end; i++) {
//    on |= digitalRead(i);
//  }
//  digitalWrite(clockOut_pin, on);

}
