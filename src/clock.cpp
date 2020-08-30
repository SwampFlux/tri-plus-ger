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
    predicted_period = predictor.Predict(DELTA);

    time_accumulation = 0;
    return true;
  } else {
    time_accumulation += DELTA;
  }

  // get multiplier from knob
  const int STEP = (division_knob * 10 + 512) / 1023 - 5;
  const unsigned int FACTOR = abs(STEP) == 5
                            ? 24
                            : 1 << abs(STEP);
  return false;
}

void Clock::reset() {
  clock_skips = 0;
}
