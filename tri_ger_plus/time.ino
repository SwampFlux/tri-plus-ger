
bool prevClockWasHigh = false;

uint32_t prevClockMillis;

uint32_t periodPrediction;

uint32_t nextClockOffAtMillis;
uint32_t prevClockOffAtMillis;

void doTimeStuff() {
  const uint32_t now = millis();
  
  bool clockIsHigh = getMux(clock_div_cv) > 512;

  if(clockIsHigh) {
    if(!prevClockWasHigh) { //new pulse
      uint32_t newPeriod = now - prevClockMillis;
      prevClockMillis = now;
      
      periodPrediction = bpm.Predict(newPeriod);
      lights(0, byte(periodPrediction)); //debug

      prevClockOffAtMillis = nextClockOffAtMillis;
      nextClockOffAtMillis = now + periodPrediction + 25;
    }
    prevClockWasHigh = true;
  } else {
    prevClockWasHigh = false;
  }

  int multiplier = getMux(clock_div_knob);
  

  if(now < prevClockOffAtMillis){
    digitalWrite(clock_out, HIGH);
  }else{
    digitalWrite(clock_out, LOW);
  }
}
