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
b pins: digital 8-13
c pins: analog 0-7
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
//#define unknown1     7  //11 (pd7) ??? some sort of reset or enable pin, normally high, triggers low
#define led_latch      8  //12 (pb0)
//#define unknown2     9  //13 (pb1) low for most of clock, then high maybe 20 clocks later, a single pulse low, then full low again 100 clocks later
//#define unknown3     10 //14 (pb2) a shape like this ---------|----|----|____________|--|__|--
#define led_data       11 //15 (pb3 MOSI) two bytes: grgrgrww, orange
#define led_clock      12 //16 (pb4)

//#define unknown4     13 //17 (pb5 SCK) yet another reset or something similar
//AVCC                    //18
#define roll_rate      6  //19 (pc6 adc6) - roll rate
//AREF                    //20
//GND                     //21
//#define unknown5     7  //22 (pc7 adc7) - ??? 
//#define unknown6     14 //23 (pc0 adc0) - ??? a pullup because it's HIGH?
#define play_pause     15 //24 (pc1 adc1) - play/pause

#define retrigger      16 //25 (pc2)
#define roll           17 //26 (pc3)
//? 27 pc4(18) adc4 - ?
//? 28 pc5(19) adc5 - ?
//  29 pc6(20) RESET
#define top_button     0  //30 (pd0)
#define left_button    1  //31 (pd1)
#define right_button   2  //32 (pd2) 

void setup() {
  pinMode(top_out, OUTPUT);
  pinMode(left_out, OUTPUT);
  pinMode(right_out, OUTPUT);

  pinMode(play_pause, INPUT);
  pinMode(retrigger, INPUT);
  pinMode(roll, INPUT);

//pinMode(rec, INPUT);
  pinMode(alt, INPUT);

//pinMode(clock_division, INPUT);
//pinMode(tempo, INPUT);
  pinMode(roll_rate, INPUT);
  
  pinMode(led_latch, OUTPUT);
  pinMode(led_data, OUTPUT);
  pinMode(led_clock, OUTPUT);

  //init
  digitalWrite(led_latch, HIGH);
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
