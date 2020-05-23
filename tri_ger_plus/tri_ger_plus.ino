/**
* MicroWrave Tri+ger
* Alternative firmware for the QU-Bit Tri-ger
* Written by Wray Bowling
* GPL3.0 (see LICENSE file for copyleft details)
* Use this code at your own risk! By using this code,
* you are responsible if you break your module
* Detailed instructions are in the Wiki
*/

#define DEBUG true

/*
ATMEGA328 AU pin configuration & assignment

pins on chip start at dot and go countner-clockwise

d pins: digital 0-7
b pins: digital 8-15
c pins: digital 16-23 analog 0-7
*/

#define top_out        3  //1 (pd3)
#define left_out       4  //2 (pd4)
//GND                     //3
//VCC                     //4
//GND                     //5
//VCC                     //6
//crystal 1            14 //7 (pb6)
//crystal 2            15 //8 (pb7)

#define right_out      5  //9 (pd5)
#define alt            6  //10 (pd6)
#define clock_out      7  //11 (pd7)
#define led_latch      8  //12 (pb0)
#define multiplex1     9  //13 (pb1) low for most of clock, then high maybe 20 clocks later, a single pulse low, then full low again 100 clocks later
#define multiplex2     10 //14 (pb2) a shape like this ---------|----|----|____________|--|__|--
#define led_data       11 //15 (pb3 MOSI) two bytes: grgrgrww, orange
#define led_clock      12 //16 (pb4)

#define multiplex3     13 //17 (pb5 SCK) yet another reset or something similar
//AVCC                    //18
#define knob_read      A6 //19 (pc6(22) adc6) - read from lots of knobs
//AREF                    //20
//GND                     //21
#define unknown7       23 //22 (pc7(23) adc7) - ??? 
#define retrigger      A0 //23 (pc0(16) adc0)
#define play_pause     A1 //24 (pc1(17) adc1)

#define unknown2       A2 //25 (pc2(18) adc2) - ??? reads high. a reference?
#define roll           19 //26 (pc3(19) adc3)
#define unknown4       A4 //27 (pc4(20) adc4) - ??? read roughly half voltage one time. otherwise matches unknown2 output
#define unknown5       21 //28 (pc5(21) adc5) - ??? always low. nothing?
//RESET                   //29 pc6(20)
#define top_button     0  //30 (pd0)
#define left_button    1  //31 (pd1)
#define right_button   2  //32 (pd2) 

#define tmpl4  {4,0,0,0, 0,0,0,0, 0,0,0,0}
#define tmpl2  {2,0,0,0, 0,0,0,0, 0,0,0,0}
#define tmpl0  {0,0,0,0, 0,0,0,0, 0,0,0,0}

//#include "led.h"

int seq_weights[16][12] = {
   tmpl4, tmpl0, tmpl0, tmpl0,
   tmpl0, tmpl0, tmpl0, tmpl0,
   tmpl4, tmpl0, tmpl0, tmpl0,
   tmpl2, tmpl0, tmpl0, tmpl0
};

void setup() {
//  pinMode(clock_in, INPUT_PULLUP);
  pinMode(clock_out, OUTPUT);

  pinMode(top_out, OUTPUT);
  pinMode(left_out, OUTPUT);
  pinMode(right_out, OUTPUT);
  
  pinMode(top_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);

//  pinMode(play_pause, INPUT);
//  pinMode(retrigger, INPUT);
//  pinMode(roll, INPUT);

  pinMode(unknown2, INPUT);


//pinMode(rec, INPUT);
  pinMode(alt, INPUT);

//pinMode(clock_division, INPUT);
//pinMode(tempo, INPUT);
  
  pinMode(led_latch, OUTPUT);
  pinMode(led_data, OUTPUT);
  pinMode(led_clock, OUTPUT);

  //unidentified
  pinMode(20, INPUT);

  //init
  digitalWrite(led_latch, HIGH);


  //multiplexer
  pinMode(multiplex1, OUTPUT); //no3 yes?
  pinMode(multiplex2, OUTPUT); // YES
  pinMode(multiplex3, OUTPUT); // YES

  digitalWrite(multiplex1, HIGH);
  digitalWrite(multiplex2, HIGH);
  digitalWrite(multiplex3, LOW);

  byte clock_division     = B000; // 0
  byte nothing2           = B001; // 1
  byte tempo              = B010; // 2
  byte record_button      = B011; // 3
  byte clock_division_cv  = B100; // 4
  byte host_or_slave      = B101; // 5
  byte roll_rate          = B110; // 6
  byte master_record      = B111; // 7 record button from master

  // the rabbit hole goes deeper! pin configurations are in the multiplex
  // using some sort of resistor ladder

  // 0 normal
  // >3/8ths slave mode
  // 1 host mode


  //multiplexer 2??
//  pinMode(unknown4, INPUT); // matches with #2's high and low


//  pinMode(unknown2, OUTPUT);
//  digitalWrite(unknown2, HIGH);
  
  pinMode(unknown5, OUTPUT);
  digitalWrite(unknown5, LOW);

  pinMode(unknown7, OUTPUT);
  digitalWrite(unknown7, LOW);
}



//byte counter = 1;

void loop() {

  digitalWrite(unknown5, HIGH);
  delay(10);
  digitalWrite(unknown5, LOW);
  delay(20);

  byte test_signal = byte( 1 << (analogRead(play_pause) / 128) );
//  byte test_signal = byte( 1 << digitalRead(unknown2) );
  
  lights(0, test_signal);
//  counter << 1;
//  if(counter >= 1000) counter = 1;
  
//  delay(100);
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
