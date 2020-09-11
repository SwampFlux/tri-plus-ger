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
#include "lights.h"
#include "clock.h"
#include "DebouncedBoolean.h"

//// global state
// clock out
// arcade buttons

// clock input multiplier (alt+clock division)
// beat quantizer (clock division)
int8_t knobStep (uint16_t v) {
  return (v * 5 + 512) >> 10;  // >>10 quick divides by 1023
}
// slip/bank (tempo mid-range)

// weight (roll rate)

// retrigger
// tap tempo (retrigger?)
// play/pause
// use step offset (roll button)
// record
// alt

uint16_t prev_clock_div_knob__val = 1;
uint16_t clock_input_multiplier = 1;
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
  pinMode(PIN_clock_out, OUTPUT);

  pinMode(PIN_top_button, INPUT);
  pinMode(PIN_left_button, INPUT);
  pinMode(PIN_right_button, INPUT);

  pinMode(PIN_top_out, OUTPUT);
  pinMode(PIN_left_out, OUTPUT);
  pinMode(PIN_right_out, OUTPUT);

  pinMode(PIN_mux_select_0, OUTPUT);
  pinMode(PIN_mux_select_1, OUTPUT);
  pinMode(PIN_mux_select_2, OUTPUT);

  pinMode(PIN_alt, INPUT);

  pinMode(PIN_led_latch, OUTPUT);
  pinMode(PIN_led_data, OUTPUT);
  pinMode(PIN_led_clock, OUTPUT);
  for(int i=0; i<RESOLUTION; i++){
    weight_ram[i] = random(B00111111);
  }
}

void loop() {
  // state updates
  topPressed |= digitalRead(PIN_top_button);
  leftPressed |= digitalRead(PIN_left_button);
  rightPressed |= digitalRead(PIN_right_button);

  record_button_value.set( getTrigerMux(MUX_record_button) > LOGIC_HIGH );
  if(record_button_value.isRising()){
    isRecording = !isRecording;
  }

  // local vars
  uint16_t clock_in_value = getTrigerMux(MUX_clock_div_cv);
  uint16_t tempo_value = getTrigerMux(MUX_tempo);
  uint16_t clock_div_knob__val = getTrigerMux(MUX_clock_div_knob);
  uint8_t rollup = 3 - (getTrigerMux(MUX_roll_rate_knob) * 3 / 1024);
  uint32_t time = millis();
  const bool BUTTONS[3] = {topPressed, leftPressed, rightPressed};
  bool isAltPressed = digitalRead(PIN_alt);

  if(isAltPressed && (clock_div_knob__val != prev_clock_div_knob__val)) {
    clock_input_multiplier = clock_div_knob__val;
  }
  prev_clock_div_knob__val = clock_div_knob__val;

  // clock advancement
  if( clock.isHigh(tempo_value, clock_input_multiplier, time) ) {

    // write state for previous step
    if(isRecording) {
      uint8_t new_weights = 0;
      for(int i=0; i<3; i++) {
        uint8_t limited_weight = constrain(int(weights[i]) + (BUTTONS[i]?2:0) - 1, 0, 4);
        // [2] [1] [0]
        new_weights += limited_weight << (i*2);
      }
      weight_ram[step] = new_weights;
    }

    // reset state for next step
    topPressed = leftPressed = rightPressed = false;

    // advance step
    step = (step+1) % RESOLUTION;

    // extract individual channel weights from memory
    // [2] [1] [0]
    uint8_t buffer = weight_ram[step];
    for(int i; i<3; i++) {
      weights[i] = buffer & B11;
      buffer = buffer >> 2;
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
  digitalWrite(PIN_left_out, (left_until > time));
  digitalWrite(PIN_top_out, (top_until > time));
  digitalWrite(PIN_right_out, (right_until > time));
  digitalWrite(PIN_clock_out , (clock_until > time) );

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
    + B00000010 * isAltPressed
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
