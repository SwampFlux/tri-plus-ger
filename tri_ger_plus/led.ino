void lights() {
  digitalWrite(led_latch, LOW);
  shiftOut(led_data, led_clock, LSBFIRST, rgw);
  shiftOut(led_data, led_clock, LSBFIRST, orng);
  digitalWrite(led_latch, HIGH);
}

