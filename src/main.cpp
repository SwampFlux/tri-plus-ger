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
// #include <EEPROM.h>
#define DEBUG true

#include "preferences.h"
#include "pins.h"
#include "multiplexer.h"
#include "lights.h"
// #include "grid.h"
#include "clock.h"
#include "DebouncedBoolean.h"

// state
Clock clock;
unsigned long clock_until = 0;
uint16_t step = 0;
bool leftPressed, topPressed, rightPressed = false;
uint32_t left_until, top_until, right_until = 0;
DebouncedBoolean record_button_value;
bool isRecording = false;
uint8_t weight_ram[RESOLUTION] = {0};
uint8_t weights[3] = {0};
uint8_t pwm = 0;

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
  for(int i=0; i<RESOLUTION; i++){
    weight_ram[i] = random(B00111111);
  }
}

void loop() {
  // state updates
  topPressed |= digitalRead(top_button);
  leftPressed |= digitalRead(left_button);
  rightPressed |= digitalRead(right_button);
  record_button_value.set( getTrigerMux(record_button) > LOGIC_HIGH );
  if(record_button_value.isRising()){
    isRecording = !isRecording;
  }

  // local vars
  uint16_t this_clock_in = getTrigerMux(clock_div_cv);
  uint16_t clock_div_knob__val = getTrigerMux(clock_div_knob);
  uint8_t rollup = 3 - (getTrigerMux(roll_rate_knob) * 3 / 1024);
  uint32_t time = millis();
  const bool BUTTONS[3] = {topPressed, leftPressed, rightPressed};

  // clock advancement
  if( clock.isHigh(this_clock_in, clock_div_knob__val, time) ) {

    // write state for previous step
    if(isRecording) {
      uint8_t new_weight;
      for(int i; i<3; i++) {
        new_weight += constrain(weights[i] + (BUTTONS[i]?2:0) - 1, 0, 4) << (2*i);
      }
      weight_ram[step] = new_weight;
    }

    // reset state for next step
    topPressed = leftPressed = rightPressed = false;

    // advance step
    step = (step+1) % RESOLUTION;

    // extract individual channel weights from memory
    for(int i; i<3; i++){
      weights[i] = (weight_ram[step] >> (2*i)) & B11;
    }

    // advance outputs
    if((step % PPQN) == 0) {
      clock_until = time + 25;
    }
    if(weights[0] >= rollup) {
      top_until = time + 25;
    }
    if(weights[1] >= rollup) {
      left_until = time + 25;
    }
    if(weights[2] >= rollup) {
      right_until = time + 25;
    }
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
  uint8_t viz = 4 * step / RESOLUTION;

  uint8_t grw = 0
    // greens
    + B10000000 * brightness[weights[0]] * (rollup <= weights[0])
    + B00100000 * brightness[weights[1]] * (rollup <= weights[1])
    + B00001000 * brightness[weights[2]] * (rollup <= weights[2])
    // reds
    + B01000000 * brightness[weights[0]] * (rollup > weights[0])
    + B00010000 * brightness[weights[1]] * (rollup > weights[1])
    + B00000100 * brightness[weights[2]] * (rollup > weights[2])
    // alt
    + B00000010 * brightness[2]
    // record
    + B00000001 * isRecording
  ;

  uint8_t oranges = 0
    + tracker[viz] * (viz == 0 ? 1 : brightness[2])
    // + EEPROM.read(step)
    // + (B11111111 & step)
    // + weight_ram[step]
    // + rollup
    + B1000 * brightness[weight_ram[step] >> 4]
    + B0100 * brightness[weight_ram[(step+1)%RESOLUTION] >> 4]
    + B0010 * brightness[weight_ram[(step+2)%RESOLUTION] >> 4]
    + B0001 * brightness[weight_ram[(step+3)%RESOLUTION] >> 4]
  ;
    
  lights(grw, oranges);


  pwm = (pwm+1) % 80;
  
}


