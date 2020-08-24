#ifndef GRID_H
#define GRID_H

#define RESOLUTION    384 //24ppqn * 16 steps

class Grid
{
private:
  bool slots[RESOLUTION] = {false};

public:
  int get_state(int index, int size, int minimum);
  bool set_state(int index, bool value);
};

#endif
