#ifndef GRID_H
#define GRID_H

#define LAYERS        3
#define RESOLUTION    384 //24ppqn * 16 steps

class Grid
{
private:
  bool slots[LAYERS][RESOLUTION] = {{false}};

public:
  short get_weight(int index, unsigned short size);
  bool set_state(unsigned short layer, int index, bool value);
};

#endif
