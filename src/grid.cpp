/*
 * The grid collects beats and then can output
 * an on or off value from a wider grid and
 * weight threshold
 */

#include "grid.h"

// Grid::Grid(){}

int Grid::get_state(int index, int width, int minimum){
  int weight = 0;
  for(int i = index; i < index+width; i++) {
    weight += slots[i];
  }
  return weight >= minimum;
}

bool Grid::set_state(int index, bool value){
  slots[index] = value;
}