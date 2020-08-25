#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include "peaks_pattern_predictor.h"

class Clock {
  private:
    PatternPredictor<32, 8> predictor;
    byte sync_debounce = 0;
    uint32_t millis_prev_sync = 0;
    uint32_t sync_period;
    uint32_t sync_counter;
    uint32_t prev_modulo;
    uint32_t next_modulo;
    uint32_t clock_skips;
    uint8_t clock_counter;
    //  uint32_t clock_slip;
    //  byte clock_debounce = 0;

    //  uint32_t millis_next_clock_on;
    //  bool clock_is_on;
    uint32_t millis_next_clock_off;

  public:
    Clock() {
      predictor.Init();
    }
    void clockIn(int sync_voltage);
    bool clockOut(int division_voltage);
    void reTrigger();
    // void doTimeStuff();
};

#endif
