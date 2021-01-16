
#include "libpacemaker.h"
#include "stdio.h"

//TODO: Test with much slower heart rate
const int bpm = 60;
const int interval = 60000 / bpm;

volatile int lastBeat;
volatile int ctr = 0;

extern "C" void SEND_PULSE(float);

void SEND_PULSE(float ampl) {
  char buf[128];
  int ampr = (int) ampl;
  sprintf(buf, "Sending Pulse with %d\n", ampr);
  Serial.print(buf);
}

void pacemaker_O_BPM(int bmp){
  char buf[128];
  sprintf(buf, "BPM is %d\n", bpm);
  Serial.print(buf);
}

void pacemaker_O_TIME_OUT() {
  Serial.print("TIME OUT");
}

void setupInterrupts() {
  cli();

  TCCR1A = 0;               //TCCR1A-Register reset
  TCCR1B = 0;               //TCCR1B-Register reset
  TIMSK1 = 0;               //TIMSK1-Register reset
  TCNT1 = 0;                //Zaehler initialisieren
  TCCR1B |= (1 << CS12);    //256 als Prescale-Wert einstellen
  TCCR1B |= (1 << WGM12);   //CTC-Mode aktivieren
  TIMSK1 |= (1 << OCIE1A);  //Timer Compare Interrupt aktivieren
  OCR1A = 312;              //Compare-Wert einstellen (f=200Hz)

  sei();
}

ISR(TIMER1_COMPA_vect) {
  // TODO: Try passing the interrupts since last heart beat
  pacemaker_I_INT(1);
}

void setup() {
  Serial.begin(9600);
  lastBeat = millis();
  setupInterrupts();
}

void loop() {
  if (millis() > lastBeat + interval) {
    if (!(++ctr % 5)) {
      Serial.print("Skipping BEAT\n");
      lastBeat = millis();
    } else {
      Serial.print("REGULAR BEAT\n");
      pacemaker_I_HEART_BEAT();
      lastBeat = millis();
    }
  }
  // Maybe more carful with interrupts here
  pacemaker();
}
