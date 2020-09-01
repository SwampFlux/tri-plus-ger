/**
 * Clock class
 * 
 * Generates a 24ppqn signal from lower ppqn signals
 * Outputs true from isHigh when a new pulse is reached
 */

#include "clock.h"
#include "preferences.h"

bool Clock::isHigh(int sync_voltage, int division_knob, uint32_t time) {
  
  // measure time delta
  const uint8_t DELTA = time - prev_time;
  prev_time = time;

  // reset if sync is rising
  sync_debounce.set(sync_voltage > LOGIC_HIGH);
  if (sync_debounce.isFresh()) {

    // predict milliseconds of period
    // ignoring clock division
    period_prediction = predictor.Predict(DELTA);
    reset();
    return true;
  } else {
    period_accumulation += DELTA;
  }

  // get multiplier from knob
  const int8_t KNOB_STEP = (division_knob * 5 + 512) >> 10; // quick divide by 1023

  // if no division, duration of 1 pulse at 24ppqn is the same as period
  if(KNOB_STEP == 0){
    slot_duration = period_prediction;
  } else if (KNOB_STEP == 1) {
    // 16ppqn * 3/2 = 24ppqn
    slot_duration = period_prediction * 1.5;
  } else {
    // 8ppqn, 4ppqn, 2ppqn, 1ppqn
    const uint16_t MULTIPLIER = pow(2, KNOB_STEP - 2) * 3;
    slot_duration = period_prediction * MULTIPLIER;
  }

  // if pulse has advanced, return true
  const uint8_t PULSE_NUMBER = period_accumulation / slot_duration;
  if(pulse_counter < 24 && PULSE_NUMBER > pulse_counter){
    pulse_counter++;
    return true;
  }

  return false;
}

void Clock::reset() {
  pulse_counter = 0;
  period_accumulation = 0;
}
