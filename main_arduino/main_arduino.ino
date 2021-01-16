/* Pin declarations */

const int D6 = 6; // used for analog write

/* Global variables */ 

volatile boolean inhibitPeek = false;
volatile boolean beat = false;
volatile int lastBeatAmpl = 0;

volatile boolean pulseActive = false;
volatile int remainingPulseLength = 0;

void setup() {
  Serial.begin(9600);

  pinMode(D6, OUTPUT);
  
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
  if (beat) {
    Serial.print("Beat: ");
    Serial.println(lastBeatAmpl);
  }
}

void senseForHeartbeat() {
  if (beat) {
    beat = false;
  }
  
  int beatValue = analogRead(A1);
  if (beatValue > 5 && !inhibitPeek) {
    inhibitPeek = true;
    beat = true;
    lastBeatAmpl = beatValue;
  }
  if (beatValue <= 5 && inhibitPeek) {
    inhibitPeek = false;
  }
}

/**
 * Sends a pulse.
 * 
 * length: Length in milli seconds. Should be divideable by 5. Portion that is not aligned to 5 will be ignored.
 * scale: Between 0 and 255.
 */
void sendPulse(int length, int scale) {
  analogWrite(D6, scale);
  pulseActive = true;
  remainingPulseLength = length;
}

/**
 * Called by timing interrupt to terminate pulse after its length.
 */
void terminatePulseIfRequired() {
  if (pulseActive) {
    remainingPulseLength = remainingPulseLength - 5;
    
    if (remainingPulseLength < 5) {
      pulseActive = false;
      analogWrite(D6, 0);
    }
  }
}

void loop() {
  sendPulse(1000, 100);
  delay(2000);
}
