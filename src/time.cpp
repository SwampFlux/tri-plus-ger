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

#include "pins.h"
#include "clock.h"

Clock::Clock(void) {
  predictor.Init();
}

void Clock::clockIn(int sync_voltage) {
  sync_debounce = sync_debounce << 1 + sync_voltage > 900;
  syncCounter++;
  if (sync_debounce == 1) {
    const uint32_t NEW_PERIOD = millis() - millis_prev_sync;
    sync_period = predictor.Predict(NEW_PERIOD);
    syncCounter = 0;
  }
}

bool Clock::clockOut() {
  const int MULTIPLIER_STEP = (getMux(clock_div_knob) * 10 + 512) / 1023 - 5;
  const int MULTIPLIER = abs(MULTIPLIER_STEP) == 5
                              ? 24
                              : 1 << abs(MULTIPLIER_STEP);

  if (MULTIPLIER_STEP <= 0) {
    // less knob = multiply period (slower)
    //= this.sync_period * MULTIPLIER;
    // actually just skip

    // if (something) {
    //   this.clock_skips++;
    //   if (this.clock_skips >= MULTIPLIER)
    //   {
    //     this.clock_skips = 0;
    //   }
    // }
  } else { // divide period (faster)
    const NEXT_MODULO =
    //prev_modulo

    //millis_next_clock_on = now + periodPrediction / multiplier;
  }
  millis_next_clock_off = millis_next_clock_on + 25;
}

void Clock::reTrigger()
{
  this.skips = 0;
}


// void
// doTimeStuff()
// {

//   // y = floor((x10+512)/1023-5)+5

//   //  int multiplier = getMux(clock_div_knob) * 24 / 512 - 24;
//   lights(0, multiplier);

//   const uint32_t now = millis();

//   bool clockIsHigh = getMux(clock_div_cv) > 512;

//   if (clockIsHigh)
//   {
//     if (!prevClockWasHigh)
//     { //new pulse
//       uint32_t newPeriod = now - prevClockMillis;
//       prevClockMillis = now;

//       periodPrediction = bpm.Predict(newPeriod);
//       //      lights(0, byte(periodPrediction)); //debug

//       prevClockOffAtMillis = nextClockOffAtMillis;

//       if (multiplier_step <= 0)
//       { // multiply period, go slower
//         nextClockOffAtMillis = now + periodPrediction * multiplier + 25;
//       }
//       else
//       { // divide period, go faster
//         nextClockOffAtMillis = now + periodPrediction / multiplier + 25;
//       }
//     }
//     prevClockWasHigh = true;
//   }
//   else
//   {
//     prevClockWasHigh = false;
//   }

//   if (now < prevClockOffAtMillis)
//   {
//     digitalWrite(clock_out, HIGH);
//   }
//   else
//   {
//     digitalWrite(clock_out, LOW);
//   }
// }
