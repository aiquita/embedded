/* Pin declarations */

int A_1 = 1; // analog 1
const int D_6 = 6; // digital 2

/* Global variables */ 

volatile boolean inhibitPeek = false;
volatile boolean beat = false;
volatile int lastBeatAmpl = 0;

void setup() {
  Serial.begin(9600);

  pinMode(D_6, OUTPUT);
  pinMode(A_1, INPUT);
  
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
  
  int beatValue = analogRead(A_1);
  if (beatValue > 5 && !inhibitPeek) {
    inhibitPeek = true;
    beat = true;
    lastBeatAmpl = beatValue;
  }
  if (beatValue <= 5 && inhibitPeek) {
    inhibitPeek = false;
  }
}

void loop() {
}
