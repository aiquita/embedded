#define pulseOut1 6     //Erster Ausgangspuls von Herzschlag

void sendMeasurements();
void sendPulse(float voltage);

void setup() {
  Serial.begin(9600);
  
  //fast PWM einschalten auf den Ausgangspins
  //Evtl noch anschauen: http://arduino-projekte.webnode.at/registerprogrammierung/fast-pwm/
  //Pin 6 benutzt Timer0, Output A
  pinMode(pulseOut1, OUTPUT);
  TCCR2A = _BV(COM2A1)  | _BV(WGM21) | _BV(WGM20); //WGM = 011 aktiviert fast pwm
                                                   // COM = 10 aktiviert nichtinvertierende PWM
  TCCR2B = _BV(CS22);   //Prescaler = 
  OCR2A = 180;    //Output compare Wert
}

void sendMeasurements() {

  const float base = 0.4;
  const float multiplier = 0.2;

  for (int i = 0; i < 19; i++) {
      sendPulse(base + i * multiplier);
  }
  
}

const int vToI = 255 / 5;

void sendPulse(float voltage) {
  analogWrite(pulseOut1, voltage * vToI);
  delay(100);
  digitalWrite(pulseOut1, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
