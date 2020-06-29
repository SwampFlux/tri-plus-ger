/**
 * multiplexed analog signals
 * all are read on A6 via the getMux() function
 */
#define clock_div_knob B000       // 0
#define clock_div_cv B001         // 1
#define tempo B010                // 2 - from master via ribbon cable if jumper configured
#define roll_rate_knob B011       // 3
#define roll_rate_cv B100         // 4
#define host_vs_slave B101        // 5 - host=944, normal=0, slave=3
#define record_button B110        // 6
#define record_button_master B111 // 7

int getMux(char channels)
{
  digitalWrite(mux_select_0, bitRead(channels, 0));
  digitalWrite(mux_select_1, bitRead(channels, 1));
  digitalWrite(mux_select_2, bitRead(channels, 2));
  return analogRead(mux_voltage);
}

bool getHostMode()
{
  int mode = getMux(host_vs_slave);
  if (mode > 900)
    return 1; //host
  if (mode > 0)
    return 0; //slave
  return 1;   //normal
}