#ifndef CLOCK_H
#define CLOCK_H

#include "peaks_pattern_predictor.h"
#include "DebouncedBoolean.h"

class Clock {
  private:
    uint32_t prev_time;
    DebouncedBoolean sync_debounce;

    PatternPredictor<32, 8> predictor;
    uint16_t period_prediction;
    uint16_t period_accumulation;
    uint8_t slot_duration;
    
    uint8_t pulse_counter = 0;

  public:
    Clock() {
      predictor.Init();
    }
    bool isHigh(uint16_t sync_voltage, uint16_t division_knob, uint32_t time);
    void reset();
};

#endif
