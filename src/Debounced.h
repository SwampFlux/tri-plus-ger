/**
 * Debounced Boolean
 * Best used on continuously read logic inputs
 *
 * set() shifts truthiness into the past
 * isRising() only returns true if no past value is true
 */

#pragma once
#include <Arduino.h>

class DebouncedBoolean {
  public:
    DebouncedBoolean() {}

    bool state[2] = {false};

    void set(bool value) {
      state[0] = state[1];
      state[1] = value;
    }

    bool isRising() {
      return state[0] == false && state[1] == true;
    }
    void reset() {
      state[2] = {false};
    }
};

class DebouncedInt {
  public:
    DebouncedInt() {}
    uint16_t state[2] = {0};

    void set(uint16_t value) {
      state[0] = state[1];
      state[1] = value;
    }

    uint16_t get() {
      return state[1];
    }

    bool changed() {
      return state[0] != state[1];
    }
}
