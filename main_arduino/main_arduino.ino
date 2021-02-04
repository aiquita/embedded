#include "libpacemaker.h"
#include "stdio.h"
#include "RunningAverage.h"

extern "C" { 
  void SEND_PULSE(float);
  float CALC_AMPL();
  int CALC_BPM();
  int BPM_TO_FREQ(int);
}

/* Pin declarations */

const int PULSING_PIN = 6; // used for analog write
const int SENSING_PIN = A1;

/* Global variables */ 

volatile boolean firstHeartbeatFound = false;

volatile boolean insideSignal = false;
volatile boolean inhibitMeasurement = false;
volatile boolean beatReady = false;
volatile float lastAmplitude = 0;

volatile boolean pulseActive = false;
volatile int remainingPulseLength = 0;
volatile boolean triggerHappened = false;

volatile int freqCtr = 0;

// Heartbeat Variables
volatile long lastHeartbeatTime = 0;
volatile unsigned int currentBPM = 70;

RunningAverage absSampleDiff(20);
volatile int cyclesWaited = 0;
volatile int samplesCount = 0;

/* used to manage debugging */

volatile bool pulseTriggered = false;

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

volatile long intCount = 0;
volatile long lastCount = 0;

ISR(TIMER1_COMPA_vect) {
  terminatePulseIfDurationExceeded();
  senseForHeartbeat();
  mesureHeartbeatAmplitude();
  freqCtr++;
  intCount++;
}

/**
 * Terminates a pulse if its time length exceeded.
 */
inline void terminatePulseIfDurationExceeded() {
  if (pulseActive) {
    remainingPulseLength--;
    
    if (remainingPulseLength == 0) {
      pulseActive = false;
      analogWrite(PULSING_PIN, 0);
    }
  }
}

/**
 * Update the BPM
 */
inline void updateBPM() {
  currentBPM = (12000 / intCount);
  intCount = 0;
}

/**
 * Senses for a heartbeat.
 * 
 * Sensing uses a threshold of 5 in order to ignore arbitrary fluctuations.
 * Sensing is inhibited until amplitued drops under 5 again.
 */
inline void senseForHeartbeat() {
  int beatValue = analogRead(SENSING_PIN);
  if (isRisingEdge(beatValue)) {
    inhibitMeasurement = false;
    absSampleDiff.clear();
    if (!firstHeartbeatFound && lastAmplitude > 1){
      firstHeartbeatFound = true;
      freqCtr = 0;
      return;
    }
    updateBPM();
    beatReady = true;
  }
}

/**
 * Decides whether the given value represents a rising edge.
 * 
 * Values lower than 20 are omitted because they are assumed to be arbitrary fluctuations.
 * The function assumes value to be a falling edge if it drops under 20 and a signal was
 * present before.
 */
inline bool isRisingEdge(int value) {
  if (value >= 20 && !insideSignal) {
    insideSignal = true;
    return true;
  }
  if (value < 20 && insideSignal) {
    insideSignal = false;
  }
}

/**
 * Mesures the hearbeat by average of three samples.
 */
inline void mesureHeartbeatAmplitude() {
  if (inhibitMeasurement || cyclesWaited++ < 4) return;
  float beatVoltage = analogRead(SENSING_PIN) * 0.0049;
  //beatVoltage *= beatVoltage > 2.2 ? 1.35 : (beatVoltage > 1.7 ? 1.25 : 1.15);
  //beatVoltage *= beatVoltage > 2.0 ? 1.457 : 1.15;
  
  absSampleDiff.addValue(beatVoltage);
  if (++samplesCount >= 10) {
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
  pulseTriggered = true; // if pulseTriggered is true serial print is triggered in loop() 
}

void SEND_PULSE(float ampl) {
  sendPulse(14, (ampl * 255) / 5);
  intCount = freqCtr;
}

void PACEMAKER_O_TIME_OUT() {
  // Maybe overkill
  int pacedBPM = (intCount / 12000);
  int correction = (12000 / pacedBPM) - (12000 / currentBPM);
  intCount = correction;
  triggerHappened = true;
}

float CALC_AMPL() {
  return lastAmplitude;
}

int CALC_BPM() {
   if (lastCount == 0) {
    return 70;
   }

   return (12000 / lastCount);
}

int BPM_TO_FREQ(int bpm) {
  return (12000 / (bpm - 4)) + 1; 
}

void loop() {
  if (!firstHeartbeatFound) return; // inibits behavior in setup phase of the heart
  
  cli();
  
  PACEMAKER_I_INT(freqCtr);
  freqCtr = 0;
  bool lBeat = beatReady;
  
  sei();
  
  if (lBeat) {
    PACEMAKER_I_HEART_BEAT();
    lastHeartbeatTime = millis();
    lastCount = intCount;
    intCount = 0;
    beatReady = false;
  }

  // Maybe more carful with interrupts here
  PACEMAKER();

  if (pulseTriggered) {
    Serial.println("Pulse triggered");
    Serial.print("Last ampl: ");
    Serial.println(lastAmplitude);
	Serial.print("BPM: ");
    Serial.println(currentBPM);
    Serial.println();
    pulseTriggered = false;
  }

  if (lBeat) {   
    Serial.print("Beat: ");
    Serial.println(lastAmplitude);
    Serial.print("BPM: ");
    Serial.println(currentBPM);
    Serial.println();
  }
}
