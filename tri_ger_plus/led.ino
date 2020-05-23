// a function for lighting up
//
// red: the red polarity of the 3 status lights
// green: the green polarity of the 3 status lights
// white: record and alt button backlights (in that order)
// orange: bar and beat display
//
// note that play/pause, retrigger, and roll lights only light up when you press that button

void lights(byte rgw, byte orange) {

//  const byte red =    B01010100;
//  const byte green =  B10101000;
//  const byte white =  B00000011;
//  const byte rgw = green + white;
//  const byte orange = B00111110;
  
  digitalWrite(led_latch, LOW);
  shiftOut(led_data, led_clock, LSBFIRST, rgw);
  shiftOut(led_data, led_clock, LSBFIRST, orange);
  digitalWrite(led_latch, HIGH);
}
