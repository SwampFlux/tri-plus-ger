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
#define mux_select_0   9  //13 (pb1)
#define mux_select_1   10 //14 (pb2)
#define led_data       11 //15 (pb3 MOSI) - 2 bytes: grgrgrww, orange
#define led_clock      12 //16 (pb4)

#define mux_select_2   13 //17 (pb5 SCK)
//AVCC                    //18
#define mux_voltage    A6 //19 (pc6(22) adc6) - read from lots of knobs
//AREF                    //20
//GND                     //21
#define findme_1       23 //22 (pc7(23) adc7) - likely unused
#define retrigger      A0 //23 (pc0(16) adc0)
#define play_pause     A1 //24 (pc1(17) adc1)

#define master_trig    18 //25 (pc2(18) adc2) - retrigger(1) play(2) from daisy chain
#define roll           19 //26 (pc3(19) adc3)
#define findme_3       20 //27 (pc4(20) adc4) - ??? read roughly half voltage one time. otherwise matches unknown2 output
#define findme_4       21 //28 (pc5(21) adc5) - ??? always low. nothing?
//RESET                   //29 pc6(20)
#define top_button     0  //30 (pd0)
#define left_button    1  //31 (pd1)
#define right_button   2  //32 (pd2)

/* multiplexed analog signals
 * all are read on A6 via the getMux() function
 */
#define clock_div_knob       B000 // 0
#define clock_div_cv         B001 // 1
#define tempo                B010 // 2 - from master via ribbon cable if jumper configured
#define roll_rate_knob       B011 // 3
#define roll_rate_cv         B100 // 4
#define host_vs_slave        B101 // 5 - high vs half voltage, respectively
#define record_button        B110 // 6
#define record_button_master B111 // 7

/*
 * TODO section
 * these things have not been found yet
 */




void setup() {
  pinMode(clock_out, OUTPUT);

  pinMode(top_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);

  pinMode(top_out, OUTPUT);
  pinMode(left_out, OUTPUT);
  pinMode(right_out, OUTPUT);
  
  pinMode(mux_select_0, OUTPUT);
  pinMode(mux_select_1, OUTPUT);
  pinMode(mux_select_2, OUTPUT);

  pinMode(alt, INPUT);
  
  pinMode(led_latch, OUTPUT);
  pinMode(led_data, OUTPUT);
  pinMode(led_clock, OUTPUT);
}

void loop() {
  int _tempo = getMux(tempo);
  lights(0, 1 << (analogRead(_tempo) / 128));
}

int getMux(char channels) {
  digitalWrite(mux_select_0, bitRead(channels, 0));
  digitalWrite(mux_select_1, bitRead(channels, 1));
  digitalWrite(mux_select_2, bitRead(channels, 2));
  return analogRead(mux_voltage);
}
