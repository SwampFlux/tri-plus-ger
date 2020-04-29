#define led_clock  12
#define led_data   11
#define led_latch  8

void lights() {
  digitalWrite(led_latch, LOW);
  shiftOut(led_data, led_clock, LSBFIRST, rgw);
  shiftOut(led_data, led_clock, LSBFIRST, orng);
  digitalWrite(led_latch, HIGH);
}
