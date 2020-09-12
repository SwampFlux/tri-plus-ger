#pragma once

#include "voltages.h"
#include "peaks_pattern_predictor.h"
#include "Debounce.h"

class Clock {
  private:
    
    DebouncedBoolean sync_debounce;

    PatternPredictor<32, 8> predictor;
    uint32_t time_of_last_sync;
    uint32_t period_prediction;
    uint16_t prev_pulse_number;

  public:
    Clock() {
      predictor.Init();
    }
    bool isHigh(uint16_t sync_voltage, uint16_t division_knob, uint32_t time);
    void reset(uint32_t time);
};
