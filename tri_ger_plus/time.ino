
bool prevClockWasHigh = false;

uint32_t prevClockMillis;

uint32_t periodPrediction;

uint32_t nextClockOffAtMillis;
uint32_t prevClockOffAtMillis;

void doTimeStuff() {

  // collect the knob value
  // then slice the range in half
  // then normalize that half range so that 512 is in the center
  // split the half range into five roughly equal parts 100 units apart
  // convert the value into an integer ranging from -5 to +5
  // use the sign of the integer to determine if we multiply or divide
  // take the absolute value to use a lookup. range from 0-4 will be 2^x
  // 5 will equal 24
  // therefore zero will map to -5 which will divide a 24ppqn signal to quarter notes
  // therefore 1023 will map to +5 which will accept quarter notes and output 24ppqn
  // therefore 512 will map to 2^0=1 which will neither multiply nor divide

  // y = floor((x10+512)/1023-5)+5
  const int multiplier_step = (getMux(clock_div_knob) * 10 + 512) / 1023 - 5;
  const int multiplier = abs(multiplier_step) == 5
    ? 24
    : 1 << abs(multiplier_step);
  

//  int multiplier = getMux(clock_div_knob) * 24 / 512 - 24;
  lights(0, multiplier);
  
  const uint32_t now = millis();
  
  bool clockIsHigh = getMux(clock_div_cv) > 512;


  if(clockIsHigh) {
    if(!prevClockWasHigh) { //new pulse
      uint32_t newPeriod = now - prevClockMillis;
      prevClockMillis = now;
      
      periodPrediction = bpm.Predict(newPeriod);
//      lights(0, byte(periodPrediction)); //debug

      prevClockOffAtMillis = nextClockOffAtMillis;
      
      if(multiplier_step <= 0) { // multiply period, go slower
        nextClockOffAtMillis = now + periodPrediction * multiplier + 25;
      } else { // divide period, go faster
        nextClockOffAtMillis = now + periodPrediction / multiplier + 25;
      }

    }
    prevClockWasHigh = true;
  } else {
    prevClockWasHigh = false;
  }


  

  if(now < prevClockOffAtMillis){
    digitalWrite(clock_out, HIGH);
  }else{
    digitalWrite(clock_out, LOW);
  }
}
