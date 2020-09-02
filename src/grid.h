#pragma once
/*
 * Step grid
 * reads and writes from EEPROM a single step
 * weight for all channels at once in a single 8-bit byte
 */

uint8_t getWeight(uint16_t pulse, uint8_t width) {
  // all 3 channels' weights as expressed by:
  // 00110000 top
  // 00001100 left
  // 00000011 right
  // where the weight is stored as:
  // 00 off
  // 01 1
  // 10 2
  // 11 3

  // return uint8_t(B00010101);

  uint8_t weight_byte = 0;
  for(uint16_t i=pulse; i<width; i++){
    weight_byte = EEPROM.read(i % RESOLUTION);
  }
  return weight_byte;
  // static uint8_t weights[3];
  // weights[0] = ((weight_byte & B00110000) >> 4);
  // weights[1] = ((weight_byte & B00001100) >> 2);
  // weights[2] =  (weight_byte & B00000011);

  // return weights;
}

void setWeight(uint16_t pulse, uint8_t previous_memory, bool top, bool left, bool right) {
  uint8_t memory_byte = previous_memory
    - B00010101 // deminish weight
    + B00010000 * top
    + B00000100 * left
    + B00000001 * right;
  
  // perhaps could reduce how often the EEPROM is written
  if(memory_byte != previous_memory) {
    EEPROM.write(pulse, memory_byte);
  }
}
