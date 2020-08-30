#ifndef CLOCK_H
#define CLOCK_H

#include "peaks_pattern_predictor.h"
#include "DebouncedBoolean.h"

class Clock {
  private:
    uint32_t prev_time;
    DebouncedBoolean sync_debounce;

    PatternPredictor<32, 8> predictor;
    uint16_t predicted_period;

    uint8_t time_accumulation;



    // uint32_t prev_modulo;
    // uint32_t next_modulo;
    uint32_t clock_skips;
    // uint8_t clock_counter;
    // //  uint32_t clock_slip;
    // //  byte clock_debounce = 0;

    // //  uint32_t millis_next_clock_on;
    // //  bool clock_is_on;
    uint32_t millis_next_clock_off;
    void predictNextQuarterNote();
    uint8_t convertVoltageToMultiplier();

  public:
    Clock() {
      predictor.Init();
    }
    bool isHigh(int sync_voltage, int division_knob, uint32_t time);
    void reset();
    // void doTimeStuff();
};

#endif
