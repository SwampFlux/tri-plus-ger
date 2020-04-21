int[] outputs = {2,3,4,5,6,7,8,9,13};

void setup(){
  for (int i=0; i<outputs.length; i++) {
    pinMode(outputs[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  for (int i=0; i<outputs.length; i++) {
    digitalWrite(outputs[i], LOW);
  }
  delay(1000);
  for (int i=0; i<outputs.length; i++) {
    digitalWrite(outputs[i], HIGH);
  }
  delay(1000);
}


