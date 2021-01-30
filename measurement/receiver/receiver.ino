#include "RunningAverage.h"

const int SENSING_PIN = A1;
RunningAverage sampler(10);

void setup() {
  Serial.begin(9600);
}

float takeSample(){
  sampler.clear();
  for (int i = 0; i < 10; ++i) {
    const float val = analogRead(SENSING_PIN) * 0.0049;
    sampler.addValue(val);
    delay(5);
  }

  return sampler.getAverage();
}

long iterCycle = 0;
const float multiplier = 0.2;
const float base = 0.4;

void printCSV(float should, float is) {
    Serial.print(should);
    Serial.print(",");
    Serial.println(is);
}

volatile bool reset = true;

void loop() {
    if (analogRead(SENSING_PIN) < 20) {
      reset = false;
      return;
    }
    if (reset) return;
    
    // Incoming measurement
    delay(15);
    const float is = takeSample();
    const float should = base + (iterCycle++) * multiplier;
    printCSV(should, is);
    reset = true;
    
    // Idle when measurement is done
    while(should >= 4.0); 
}
