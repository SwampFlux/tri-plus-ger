/**
ATMEGA328 AU pin configuration & assignment

pins on chip start at dot and go countner-clockwise

d pins: digital 0-7
b pins: digital 8-13
c pins: analog 0-7

  pin# pinName(digital#) - what it does

  1  pd3(3) - top cv out
  2  pd4(4) - left cv out
  3  GND
  4  VCC
  5  GND
  6  VCC
  7  pb6(14) - crystal 1
  8  pb7(15) - crystal 2

  9  pd5(5) - right cv out
  10 pd6 - alt button
? 11 pd7 - some sort of reset or enable pin, normally high, triggers low
  12 pb0(8) - LED shift register latch
? 13 pb1(9) - low for most of clock, then high maybe 20 clocks later, a single pulse low, then full low again 100 clocks later
? 14 pb2(10) - a shape like this ---------|----|----|____________|--|__|--
  15 pb3(11) MOSI - LED shift register data as [white & red/green] first byte and [orange] second byte
  16 pb4(12) MISO - LED shift register clock

? 17 pb5(13) SCK - yet another reset or something similar
  18 AVCC
  19 adc6(6) - roll rate
  20 AREF -
  21 GND -
? 22 adc7(7) - ??? 
? 23 pc0(14) adc0 - ??? HIGH (pullup?)
  24 pc1(15) adc1 - play/pause

  25 pc2(16) adc2 - retrigger
  26 pc3(17) adc3 - roll
? 27 pc4(18) adc4 - ?
? 28 pc5(19) adc5 - ?
  29 pc6(20) RESET
  30 pd0(0) - top button
  31 pd1(1) - left button
  32 pd2(2) - right button
*/

#define clockOut_pin 7

#define buttonTop_pin   0
#define buttonLeft_pin  1
#define buttonRight_pin 2
#define ledTop   3
#define ledLeft  4
#define ledRight 5

#define alt 6

//analog 0 not used?
#define playPause_analog 1
#define retrigger_analog 2
#define roll_analog      3
//analog 4 not used?

#define led_clock  12
#define led_data   11
#define try_latch  8
// 10,9,8,7


void setup() {
  pinMode(led_clock, OUTPUT);
  pinMode(led_data, OUTPUT);
  pinMode(try_latch, OUTPUT);
  digitalWrite(try_latch, HIGH);
}

byte orng =  B00111110;
byte red =   B01010100;
byte green = B10101000;
byte white = B00000011;
byte rgw = green + white;

void loop() {

  delay(100);
  //if(counter++ > 100) counter = 0;
}


/*
int t = 100;

const int checkz = 11;
const int checklist[checkz] = {8,9,10,11,12,13};

void setup() {
  pinMode(14, PULLUP);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  for (int i=0; i<checkz; i++) {
    pinMode(checklist[i], OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(clockOut_pin, OUTPUT);
  SPI.begin();
}

void digitalProbe(int search_start=0, int search_end=7){
  for (int i=search_start; i<=search_end; i++) {
    digitalWrite(i, HIGH);
    delay(t/2);
    digitalWrite(i, LOW);
    delay(t/2);
  }
}

void analogBlink(){
  int a = analogRead(7);
  digitalWrite(clockOut_pin, LOW);
  delay( a + 20 );
  digitalWrite(clockOut_pin, HIGH);
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
  
    
//    for(int i=0; i<checkz; i++) {
//      digitalWrite(checklist[i], LOW);
//      SPI.transfer(B00100101);
//      delay(t);
//      digitalWrite(checklist[i], HIGH);
//      SPI.transfer(B00100101);
//      delay(t);
//      digitalWrite(checklist[i], LOW);
//      delay(t);
//    }
    
    
//  digitalProbe();
  bool on = false;
//  for (int i=14; i<=19; i++) {
   on |= analogRead(0) > 120;
    on |= digitalRead(14);
      on |= digitalRead(18);
        on |= digitalRead(19);
    
//  }
  digitalWrite(clockOut_pin, on);

}*/
