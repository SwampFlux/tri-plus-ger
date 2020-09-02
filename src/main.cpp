/**
 * MicroWrave Tri+ger
 * Alternative firmware for the QU-Bit Tri-ger
 * Written by Wray Bowling
 * GPL3.0 (see LICENSE file for copyleft details)
 * Use this code at your own risk! By using this code,
 * you are responsible if you break your module
 * Detailed instructions are in the Wiki
 * https://github.com/MicroWrave/tri-plus-ger/wiki
 */

#include <Arduino.h>
#define DEBUG true

#include "preferences.h"
#include "pins.h"
#include "multiplexer.h"
// #include "lights.h"
#include "grid.h"
#include "clock.h"
#include "DebouncedBoolean.h"

void setup()
{
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

Clock clock;
unsigned long clock_until = 0;

uint16_t step = 0;

DebouncedBoolean leftPressed;
unsigned long left_until = 0;
DebouncedBoolean topPressed;
unsigned long top_until = 0;
DebouncedBoolean rightPressed;
unsigned long right_until = 0;

uint8_t pwm = 0;

void loop() {
  // local vars
  uint16_t this_clock_in = getTrigerMux(clock_div_cv);
  topPressed.set(digitalRead(top_button));
  leftPressed.set(digitalRead(left_button));
  rightPressed.set(digitalRead(right_button));
  uint16_t clock_div_knob__val = getTrigerMux(clock_div_knob);
  uint8_t threshold = getTrigerMux(roll_rate_knob) * 4 / 1024;
  uint32_t time = millis();
  uint8_t weights[3];

  // clock advancement
  if( clock.isHigh(this_clock_in, clock_div_knob__val, time) ) {

    // write true only on the current step.
    // hold the button to clear subsequent steps
    // full roll rate acts as original gate
    setWeight(
      step,
      topPressed.isRising(),
      leftPressed.isRising(),
      rightPressed.isRising()
    );

    //advance clock
    clock_until = time + 25;

    //advance outputs
    uint8_t weight_byte = getWeight(step, threshold);
    weights[0] = ((weight_byte & B00110000) >> 4);
    weights[1] = ((weight_byte & B00001100) >> 2);
    weights[2] =  (weight_byte & B00000011);
    if(weights[0] > threshold) {
      top_until = time + 25;
    }
    if(weights[1] > threshold) {
      left_until = time + 25;
    }
    if(weights[2] > threshold) {
      right_until = time + 25;
    }

    //advance step
    step = (step+1) % RESOLUTION;
    
  }

  // cv outputs
  digitalWrite(left_out, (left_until > time));
  digitalWrite(top_out, (top_until > time));
  digitalWrite(right_out, (right_until > time));
  digitalWrite(clock_out , (clock_until > time) );

  // visualization
  int tracker[4] = {128,16,32,64};
  int brightness[4] = {
    0,
    (pwm % 80) == 0,
    (pwm % 40) == 0,
    1
  };
  short viz = 4 * step / RESOLUTION;

  uint8_t grw = 0
    // reds
    + B01000000 * brightness[weights[0]]
    + B00010000 * brightness[weights[1]]
    + B00000100 * brightness[weights[2]]
  ;

  uint8_t oranges = 0
    + tracker[viz] * (viz == 0 ? 1 : brightness[2])
    + (step & B1111)
    // + B1000 * brightness[leftGrid.get_weight(step+0, 1)]
    // + B0100 * brightness[leftGrid.get_weight(step+1, 1)]
    // + B0010 * brightness[leftGrid.get_weight(step+2, 1)]
    // + B0001 * brightness[leftGrid.get_weight(step+3, 1)]
  ;
    
  // lights(grw, (step & 255));


  pwm = (pwm+1) % 80;
  
}
