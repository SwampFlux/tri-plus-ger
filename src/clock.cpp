/**
 * collect the knob value
 * then slice the range in half
 * then normalize that half range so that 512 is in the center
 * split the half range into five roughly equal parts 100 units apart
 * convert the value into an integer ranging from -5 to +5
 * use the sign of the integer to determine if we multiply or divide
 * take the absolute value to use a lookup. range from 0-4 will be 2^x
 * 5 will equal 24
 * therefore zero will map to -5 which will divide a 24ppqn signal to quarter notes
 * therefore 1023 will map to +5 which will accept quarter notes and output 24ppqn
 * therefore 512 will map to 2^0=1 which will neither multiply nor divide
 * 
 * Next an internal clock is maintained.
 * Each loop, we can recalculate div/mult based on the knob
 * If a new input signal comes in, recalculate period
 * Time since last pulse sent > period * multiplier = new pulse
 * 
 * count up each frame. then modulo over multiplier * period
 * when the new frame is lower than the previous, then we have a new pulse
 */

#include "clock.h"
#include "preferences.h"


bool Clock::isHigh(int sync_voltage, int division_knob, uint32_t time) {
  // measure time delta
  const uint32_t DELTA = time - prev_time;
  prev_time = time;

  // reset if sync is rising
  sync_debounce.set(sync_voltage > LOGIC_HIGH);
  if (sync_debounce.isFresh()) {

    // predict milliseconds of period
    // ignoring clock division
    period_prediction = predictor.Predict(DELTA);
    period_accumulation = 0;
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

  // which pulse are we on
  const uint8_t PULSE_NUMBER = period_accumulation / slot_duration;
  if(pulse_counter < 24 && PULSE_NUMBER > pulse_counter){
    return true;
    pulse_counter++;
  } else {
    return false;
  }

}

void Clock::reset() {
  pulse_counter = 0;
  period_accumulation = 0;
}
