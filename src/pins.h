#pragma once

/**
 * ATMEGA328 AU pin configuration & assignment
 * 
 * Pins on chip start at dot and go countner-clockwise
 * 
 * d pins: digital 0-7
 * b pins: digital 8-15
 * c pins: digital 16-23 analog 0-7
 */

//      name         arduino  pin  (atmega328)
#define PIN_top_out        3  //1  (pd3)
#define PIN_left_out       4  //2  (pd4)
//      GND                   //3
//      VCC                   //4
//      GND                   //5
//      VCC                   //6
//      crystal 1          14 //7  (pb6)
//      crystal 2          15 //8  (pb7)

#define PIN_right_out      5  //9  (pd5)
#define PIN_alt            6  //10 (pd6)
#define PIN_clock_out      7  //11 (pd7)
#define PIN_led_latch      8  //12 (pb0)
#define PIN_mux_select_0   9  //13 (pb1)
#define PIN_mux_select_1   10 //14 (pb2)
#define PIN_led_data       11 //15 (pb3 MOSI) - 2 bytes: grgrgrww, orange
#define PIN_led_clock      12 //16 (pb4)

#define PIN_mux_select_2   13 //17 (pb5 SCK)
//      AVCC                  //18
#define PIN_mux_voltage    A6 //19 (pc6(22) adc6) - read from lots of knobs
//      AREF                  //20
//      GND                   //21
//#define PIN_findme_1     23 //22 (pc7(23) adc7) - likely unused
#define PIN_retrigger      A0 //23 (pc0(16) adc0)
#define PIN_play_pause     A1 //24 (pc1(17) adc1)

#define PIN_master_trig    18 //25 (pc2(18) adc2) - retrigger(1) play(2) from daisy chain
#define PIN_roll           A3 //26 (pc3(19) adc3)
// #define PIN_findme_3    20 //27 (pc4(20) adc4) - ??? read roughly half voltage one time. otherwise matches unknown2 output
// #define PIN_findme_4    21 //28 (pc5(21) adc5) - ??? always low. nothing?
//RESET                       //29 (pc6(20)
#define PIN_top_button     0  //30 (pd0)
#define PIN_left_button    1  //31 (pd1)
#define PIN_right_button   2  //32 (pd2)


/**
 * multiplexed analog signals
 * all are read on A6 via the getMux() function
 */
#define MUX_clock_div_knob       B000 // 0
#define MUX_clock_div_cv         B001 // 1
#define MUX_tempo                B010 // 2 - from master via ribbon cable if jumper configured
#define MUX_roll_rate_knob       B011 // 3
#define MUX_roll_rate_cv         B100 // 4
#define MUX_host_vs_slave        B101 // 5 - host=944, normal=0, slave=3
#define MUX_record_button        B110 // 6
#define MUX_master_record_button B111 // 7

uint16_t getTrigerMux(char channels) {
  digitalWrite(PIN_mux_select_0, bitRead(channels, 0));
  digitalWrite(PIN_mux_select_1, bitRead(channels, 1));
  digitalWrite(PIN_mux_select_2, bitRead(channels, 2));
  return analogRead(PIN_mux_voltage);
}