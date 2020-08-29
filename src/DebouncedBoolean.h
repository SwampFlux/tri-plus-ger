/**
 * Debounced Boolean
 * Best used on continuously read logic inputs
 *
 * set() shifts truthiness into the past
 * isFresh() only returns true if no past value is true
 */

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

class DebouncedBoolean {
  public:
    DebouncedBoolean() {}

    bool state[2] = {false};
    void set(bool value);
    bool isFresh();
    void reset();
};

void DebouncedBoolean::set(bool value) {
  state[0] = state[1];
  state[1] = value;
}

bool DebouncedBoolean::isFresh() {
  return state[0] == false && state[1] == true;
}

void DebouncedBoolean::reset() {
  state[2] = {false};
}

#endif
