/**
 * Clock class
 * 
 * Generates a 24ppqn signal from lower ppqn signals
 * Outputs true from isHigh when a new pulse is reached
 */

#include "clock.h"
#include "lights.h"

bool Clock::isHigh(uint16_t sync_voltage, uint16_t division_knob, uint32_t time) {

  // get multiplier from knob
  const int8_t KNOB_STEP = (division_knob * 5 + 512) >> 10; // >>10 quick divides by 1023

  // measure time between syncs
  const uint32_t PROGRESS = time - time_of_last_sync;

  // if sync is rising
  sync_debounce.set(sync_voltage > LOGIC_HIGH);
  if (sync_debounce.isRising()) {

    // repredict milliseconds of period
    period_prediction = predictor.Predict(PROGRESS);
    reset(time);

    // no further logic is necessary if no multiplier
    if (KNOB_STEP == 0) return true;
  }

  const uint8_t MULTIPLIER = pow(2, KNOB_STEP - 1) * 3;

  const uint16_t PULSE_NUMBER = PROGRESS * MULTIPLIER / period_prediction;
  lights(0, PULSE_NUMBER);
  
  if(PULSE_NUMBER != prev_pulse_number){
    prev_pulse_number = PULSE_NUMBER;
    return true;
  }

  return false;
}

void Clock::reset(uint32_t time) {
  time_of_last_sync = time;
}
