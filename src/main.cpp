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
#include "led.h"
#include "grid.h"
#include "clock.h"

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

// const bool slave_mode = getMux(host_vs_slave);
Grid leftGrid;
Clock clock;
unsigned long clock_until = 0;
unsigned long left_until = 0;
int prev_clock_in = 0;

// const int steps = RESOLUTION;
int step = 0;

bool prev_leftPressed = false;
bool this_leftPressed = false;

short pwm = 0;

void loop() {
  // local vars
  int this_clock_in = getTrigerMux(clock_div_cv);
  bool this_left = digitalRead(left_button);
  int clock_div_knob__val = getTrigerMux(clock_div_knob);

  unsigned long time = millis();

  // set state
  if(this_left) this_leftPressed = true;

  // clock advancement
  clock.clockIn(this_clock_in, time);

  if( clock.clockOut(clock_div_knob__val, time) ) {

    // write true only on the current step.
    // hold the button to clear subsequent steps
    // full roll rate acts as original gate
    if(this_leftPressed){
      leftGrid.set_state(0, step, !prev_leftPressed);
    }
    prev_leftPressed = this_leftPressed;
    this_leftPressed = false; //reset

    //advance clock
    clock_until = time + 25;

    //advance outputs
    if(leftGrid.get_weight(step, 1) > 0) {
      left_until = time + 25;
    }

    //advance step
    step = (step+1) % RESOLUTION;
  }
  prev_clock_in = this_clock_in;

  // cv outputs
  digitalWrite(left_out, (left_until > time));
  digitalWrite(top_out, this_leftPressed);
  digitalWrite(right_out, prev_leftPressed);
  digitalWrite(clock_out , (clock_until > time) );


  // visualization
  int tracker[4] = {128,16,32,64};
  int brightness[4] = {
    0,
    (pwm % 80) == 0,
    (pwm % 40) == 0,
    1
  };
  short viz = (step / 24) % 4;
  byte state = 0
    + tracker[viz] * (viz == 0 ? 1 : brightness[2])
    + B1000 * brightness[leftGrid.get_weight(step+0, 1)]
    + B0100 * brightness[leftGrid.get_weight(step+1, 1)]
    + B0010 * brightness[leftGrid.get_weight(step+2, 1)]
    + B0001 * brightness[leftGrid.get_weight(step+3, 1)];
    
  lights(0, state);

  pwm = (pwm+1) % 80;
}
