/*
 * The grid collects beats and then can output
 * an on or off value from a wider grid and
 * weight threshold
 */

#define RESOLUTION    384 //24ppqn * 16 steps

class Grid
{
private:
  bool slots[RESOLUTION] = {false};

public:
  bool get_state(int index, int size, int minimum);
};

bool Grid::get_state(int index, int width, int minimum){
  int weight = 0;
  for(int i = index; i < index+width; i++) {
    weight += slots[i];
  }
  return weight >= minimum;
}