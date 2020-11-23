#include <unity.h>
#include "../src/preferences.h"
#include "../src/grid.h";

// tests

// is RESOLUTION under 1KiB? (limit of EEPROM)
// does reading an address larger than RESOLUTION wrap around?
// does writing to an address larger than RESOLUTION wrap around?

// does EEPROM read work?
// does 1 byte unpack into 4 weights?
// do 4 weights pack into 1 byte?
// does EEPROM write work?

// does 1 weight with a value of 1 resolve to true againt a threshold of 1?
// do 2 weights with values of 1 resolve to false with a threshold of 2?
// do 2 weights across 2 bytes resolve the same as 2 weights in the same byte?

// run

int main(int argc, char **argv)
{
  UNITY_BEGIN();

  UNITY_END();
  return 0;
}