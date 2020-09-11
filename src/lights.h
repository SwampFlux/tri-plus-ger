/**
 * a function for lighting up
 *
 * red: the red polarity of the 3 status lights
 * green: the green polarity of the 3 status lights
 * white: alt and record button backlights (in that order)
 * orange: bar and beat display
 *
 * note that play/pause, retrigger, and roll lights only
 * light up when you press that button
 */

#pragma once
#include <Arduino.h>
#include "pins.h"

void lights(uint8_t grw, uint8_t orange)
{
  //  const byte green =  B10101000;
  //  const byte red =    B01010100;
  //  const byte white =  B00000011;
  //  const byte grw = green + red + white;
  //  const byte orange = B11111111;

  digitalWrite(PIN_led_latch, LOW);
  shiftOut(PIN_led_data, PIN_led_clock, LSBFIRST, grw);
  shiftOut(PIN_led_data, PIN_led_clock, LSBFIRST, orange);
  digitalWrite(PIN_led_latch, HIGH);
}
