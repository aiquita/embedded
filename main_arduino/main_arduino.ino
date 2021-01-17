#include "libpacemaker.h"
#include "stdio.h"

extern "C" { 
  void SEND_PULSE(float);
}

/* Pin declarations */

const int PULSING_PIN = 6; // used for analog write
const int SENSING_PIN = A1;

/* Global variables */ 

volatile boolean inhibitPeek = false;
volatile boolean beatReady = false;
volatile int lastBeatAmpl = 0;

volatile boolean pulseActive = false;
volatile int remainingPulseLength = 0;

volatile int freqCtr = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PULSING_PIN, OUTPUT);
  
  setupInterrupts();  
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
  terminatePulseIfRequired();
  senseForHeartbeat();
  freqCtr++;
}

/**
 * Terminates a pulse if its time length exceeded.
 */
inline void terminatePulseIfRequired() {
  if (pulseActive) {
    remainingPulseLength--;
    
    if (remainingPulseLength == 0) {
      pulseActive = false;
      analogWrite(PULSING_PIN, 0);
    }
  }
}

/**
 * Senses for a heartbeat.
 * 
 * Sensing uses a threshold of 5 in order to ignore arbitrary fluctuations.
 * Sensing is inhibited until amplitued drops under 5. 
 */
inline void senseForHeartbeat() {
  int beatValue = analogRead(SENSING_PIN);
  if (beatValue >= 5 && !inhibitPeek) {
    inhibitPeek = true;
    beatReady = true;
    lastBeatAmpl = beatValue;
  }
  if (beatValue < 5 && inhibitPeek) {
    inhibitPeek = false;
  }
}

/**
 * Sends a pulse.
 * 
 * length: Duration in millis is calculated by 5 * length. 
 * scale: Between 0 and 255.
 */
void sendPulse(int length, int scale) {
  analogWrite(PULSING_PIN, scale);
  pulseActive = true;
  remainingPulseLength = length;
  Serial.println("Pulse triggered");
}

void SEND_PULSE(float ampl) {
  sendPulse(70, ampl * 255 / 5);
}

void PACEMAKER_O_TIME_OUT() {
  
}

void PACEMAKER_O_BPM(int bpm) {
  Serial.println(bpm);
}



void loop() {
  cli();
  
  PACEMAKER_I_INT(freqCtr);
  freqCtr = 0;

  if (beatReady) {
    PACEMAKER_I_HEART_BEAT();
    Serial.print("Beat: ");
    Serial.println(lastBeatAmpl);
    beatReady = false;
  }
  
  sei();

  // Maybe more carful with interrupts here
  PACEMAKER();
}
