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

const bool slave_mode = getMux(host_vs_slave);
Grid leftGrid;
unsigned long prev_time = millis();
unsigned long clock_until = millis();
unsigned long left_until = millis();
int prev_clock_in = 0;

const int steps = 16;
int step = 0;

bool prev_leftPressed = false;
bool this_leftPressed = false;

void loop()
{
  // local vars
  int this_clock_in = getMux(clock_div_cv);
  bool this_left = digitalRead(left_button);

  unsigned long time = millis();
  // unsigned int delta = time - prev_time;

  // set state
  if(this_left) this_leftPressed = true;

  // clock advancement
  if(prev_clock_in <= NOISE_FLOOR && this_clock_in > NOISE_FLOOR) // rising
  {

    // write true only on the current step.
    // hold the button to clear subsequent steps
    // full roll rate acts as original gate
    if(this_leftPressed){
      leftGrid.set_state(step, !prev_leftPressed);
    }
    prev_leftPressed = this_leftPressed;
    this_leftPressed = false; //reset

    //advance clock
    prev_time = time;
    clock_until = time + 25;

    //advance step
    step = (step+1) % steps;

    //advance outputs
    if(leftGrid.get_state(step, 1, 1)) {
      left_until = time + 25;
    }
  }
  prev_clock_in = this_clock_in;

  // cv outputs
  digitalWrite(left_out, (left_until > time));
  digitalWrite(top_out, this_leftPressed);
  digitalWrite(right_out, prev_leftPressed);
  digitalWrite(clock_out , (clock_until > time) );


  // visualization
  int tracker[4] = {16,32,64,128};
  byte state = 0
    + tracker[step%4]
    + B1000 * leftGrid.get_state(step, 1, 1)
    + B0100 * leftGrid.get_state(step+1, 1, 1)
    + B0010 * leftGrid.get_state(step+2, 1, 1)
    + B0001 * leftGrid.get_state(step+3, 1, 1);
    
  lights(0, state);
}
