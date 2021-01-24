#include "libpacemaker.h"
#include "stdio.h"
#include "RunningAverage.h"

extern "C" { 
  void SEND_PULSE(float);
  float CALC_AMPL(int);
}

/* Pin declarations */

const int PULSING_PIN = 6; // used for analog write
const int SENSING_PIN = A1;

/* Global variables */ 

volatile boolean firstHeartbeatFound = false;

volatile boolean inhibitPeek = false;
volatile boolean inhibitMeasurement = false;
volatile boolean beatReady = false;
volatile float lastAmplitude = 0;

volatile boolean pulseActive = false;
volatile int remainingPulseLength = 0;

volatile int freqCtr = 0;

RunningAverage absSampleDiff(5);
volatile int cyclesWaited = 0;
volatile int samplesCount = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PULSING_PIN, OUTPUT);
  TCCR2A = _BV(COM2A1)  | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22); 
  OCR2A = 180;
  
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
  mesureHeartbeatAmplitude();
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
 * Sensing is inhibited until amplitued drops under 5 again.
 */
inline void senseForHeartbeat() {
  int beatValue = analogRead(SENSING_PIN);
  if (beatValue >= 20 && !inhibitPeek) { // means that a new beat peek was found
    inhibitPeek = true;
    inhibitMeasurement = false;
    absSampleDiff.clear();
    if (!firstHeartbeatFound && lastAmplitude > 1){
      firstHeartbeatFound = true;
      freqCtr = 0;
      return;
    }
    beatReady = true;
  }
  if (beatValue < 20 && inhibitPeek) { // means that the current beat has ended
    inhibitPeek = false;
  } 
}

/**
 * Mesures the hearbeat by average of three samples.
 */
inline void mesureHeartbeatAmplitude() {
  if (inhibitMeasurement || cyclesWaited++ < 2) return;
  
  int beatValue = analogRead(SENSING_PIN);
  absSampleDiff.addValue((beatValue/1023.0)*5);
  
  if (++samplesCount >= 3) {
    lastAmplitude = absSampleDiff.getAverage();
    samplesCount = 0;
    cyclesWaited = 0;
    inhibitMeasurement = true;
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
  sendPulse(14, (ampl * 255) / 5);
}

void PACEMAKER_O_BPM(int bpm) {
  Serial.print("BPM: ");
  Serial.println(bpm);
}

void PACEMAKER_O_TIME_OUT() {
}

float CALC_AMPL(int freq) {
  int normal = freq * 0.0042 + 0.25;
  int sport = freq * 0.016 + 1;

  int localAmpl = lastAmplitude;
  int diffN = normal - localAmpl;
  int diffS = sport - localAmpl;
  
  return diffS > diffN ? normal : sport;
}

void loop() {
  if (!firstHeartbeatFound) return; 
  
  cli();
  
  PACEMAKER_I_INT(freqCtr);
  freqCtr = 0;
  bool lBeat = beatReady;
  
  sei();
  
  if (lBeat) {
    PACEMAKER_I_HEART_BEAT();
    Serial.print("Beat: ");
    Serial.println(lastAmplitude);
    beatReady = false;
  }

  // Maybe more carful with interrupts here
  PACEMAKER();
}
