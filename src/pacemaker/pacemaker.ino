
#include "libpacemaker.h"
#include "stdio.h"

//TODO: Test with much slower heart rate
const int bpm = 60;
const int interval = 60000 / bpm;

volatile long long lastBeat;
volatile int ctr = 0;
volatile int freqCtr = 0;

extern "C" { 
  void SEND_PULSE(float);
  void EPRINT(int);
}

void SEND_PULSE(float ampl) {
  char buf[128];
  int ampr = (int) ampl;
  sprintf(buf, "Sending Pulse with %d\n", ampr);
  Serial.print(buf);
}

void EPRINT(int val) {
  Serial.print("PRINT: ");
  Serial.print(val);
}


void PACEMAKER_O_BPM(int bmp){
  char buf[128];
  sprintf(buf, "BPM is %d\n", bpm);
  Serial.print(buf);
}

void PACEMAKER_O_TIME_OUT() {
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
  freqCtr++;
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
      PACEMAKER_I_HEART_BEAT();
      lastBeat = millis();
    }
  }
  cli();
  PACEMAKER_I_INT(freqCtr);
  freqCtr = 0;
  sei();
  
  // Maybe more carful with interrupts here
  PACEMAKER();
}
