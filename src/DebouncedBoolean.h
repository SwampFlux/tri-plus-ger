/**
 * Debounced Boolean
 * Best used on continuously read logic inputs
 *
 * set() shifts truthiness into the past
 * isFresh() only returns true if no past value is true
 */

#pragma once

class DebouncedBoolean {
  public:
    DebouncedBoolean() {}

    bool state[2] = {false};

    void set(bool value){
      state[0] = state[1];
      state[1] = value;
    }

    bool isFresh(){
      return state[0] == false && state[1] == true;
    }
    void reset(){
      state[2] = {false};
    }
};
