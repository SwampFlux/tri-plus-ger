#include "grid.h"

/*
 * The grid collects beats and then can output
 * an on or off value from a wider grid and
 * weight threshold
 */



// Collects the weight of a step
// Each layer row only counts a maximum of 1 step
// Each slot column catches any step within the window
// Steps are added to gether for a maximum weight of 3
// index: starting point, negative numbers are supported
// width: how many steps to aggregate
short Grid::get_weight(int index, unsigned short width) {
  short weight = 0;
  for(int layer = 0; layer < LAYERS; layer++) {
    for(int col = index; col < index+width; col++) {
      if(slots[layer][(RESOLUTION + col) % RESOLUTION]) {
        weight++;
        break;
      }
    }
  }
  return weight;
}

bool Grid::set_state(unsigned short layer, int index, bool value) {
  slots[layer][index % RESOLUTION] = value;
}