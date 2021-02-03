/* Dieses Programm modelliert ein kuenstliches Herz, das hin und wieder
 * aussetzt, die Frequenz veraendert und auch eine koerperliche
 * Anstrenung simuliert. Das Herz benoetigt einen Schrittmacher, um es
 * am Leben zu erhalten.
 * 
 * Es ist fuer den Arduino NANO konzipiert und benoetigt eine
 * zusaetzliche Platine, die die Leds und die Tiefpassfilter
 * fuer die PWM-Signale enthaelt.
 * 
 * ISSE, Uni Augsburg, 06.12.2017
 * 
 * Ba.Sc Lukas Schreier (HiWi)
 * Auftrag/Unterstuetzung:
 * Prof. Dr. Alexander Knapp
 * M.Sc. Constantin Wanniger
 * Dr. Andreas Schierl
 * 
 * Bei Fragen und Anregungen:
 * lukas.schreier@student.uni-augsburg.de
 */

#include "RunningAverage.h"

#define pulseLed1 4     //LED zeigt ersten Herzschlag an
#define pulseOut1 6     //Erster Ausgangspuls von Herzschlag
#define pulseLed2 3     //LED zeigt zweiten Herzschlag an
#define pulseOut2 11    //Zweiter Ausgangspuls von Herzschlag

#define impulseLed1 5   //LED zeigt zweiten eingehenden Impuls von Schrittmacher an
#define impulseIn1 A1   //Eingang fuer ersten Impuls des Herzschrittmachers
#define impulseLed2 2   //LED zeigt ersten eingehenden Impuls von Schrittmacher an
#define impulseIn2  A0  //Eingang fuer zweiten Impuls des Herzschrittmachers

#define init 0          //Zustaende fuer Patient
#define alive 1
#define dead 2

//Programmvariablen
unsigned long pulseStart = 0;
volatile int analogValue = 0;
volatile int freq = 70;         //Herzfrequenz in bpm
volatile int freqCount = 0;     //Zaehlvariable fuer Herzschlag
volatile int freqComp = 171;    //Zwischenwert fuer Herzfrequenzeinstellung
volatile int sPulse = 0;        //Interruptflag fuer Herzschlag
volatile int pulseEnable = 1;   //Steuer-Variable fuer Herzschlag
volatile int saved = 0;         //Variable, wenn Patient gerettet wurde
volatile float ampl = 2.167;    //Amplitude des Herzschlags in V
volatile int decide = 3;        //Variable fuer das Verhalten des Herzes
volatile int lastDecide = 3;    //Speichervariable fuer das Verhalten des Herzes
volatile int patState;          //Patientenzustand
volatile int lastCF = 0;        //Speichervariable fuer Frequenzaenderung
volatile int sport = 0;         //Zaehlvariable fuer Methode physAct()

RunningAverage absSampleDiff(5);    //Sample-Variable zur Unterdrueckung von PWM-Zacken im Analogsignal

//Spezifikationen, Vorgaben, Toleranzen...
int maxHeartrate = 180;
int minHeartrate = 60;
int sampleDelay = 15;         //Zeit in ms, ab der gesampled wird, damit nicht waehrend der rising-edge gesampled wird
int impulseThreshold = 20;    //Schwelle fuer Eingang
float amplTolerance = 0.15;   //Toleranz fuer die Abweichung der Amplitude
int maxDelay = 110;           //Maximale erlaubte Verzoegerung des Schrittmachers in ms
int pulseDur = 70;            //Pulsdauer in ms

void setup() {
  Serial.begin(9600);               //Serielle Ausgabe fuer Debugging initialisieren
  
  pinMode(pulseLed1, OUTPUT);
  pinMode(pulseOut1, OUTPUT);
  pinMode(impulseIn1, INPUT);
  pinMode(impulseLed1, OUTPUT);

  randomSeed(analogRead(A4));        //Zufallsgenerator initialisieren
  
  patState = init;
  
  noInterrupts();
  
  //Timer1 fuer Interrupts initialisieren
  TCCR1A = 0;               //TCCR1A-Register reset
  TCCR1B = 0;               //TCCR1B-Register reset
  TIMSK1 = 0;               //TIMSK1-Register reset
  TCNT1 = 0;                //Zaehler initialisieren
  TCCR1B |= (1 << CS12);    //256 als Prescale-Wert einstellen
  TCCR1B |= (1 << WGM12);   //CTC-Mode aktivieren
  TIMSK1 |= (1 << OCIE1A);  //Timer Compare Interrupt aktivieren
  OCR1A = 312;              //Compare-Wert einstellen (f=200Hz)

  //fast PWM einschalten auf den Ausgangspins
  //Evtl noch anschauen: http://arduino-projekte.webnode.at/registerprogrammierung/fast-pwm/
  //Pin 6 benutzt Timer0, Output A
  pinMode(pulseOut1, OUTPUT);
  TCCR2A = _BV(COM2A1)  | _BV(WGM21) | _BV(WGM20); //WGM = 011 aktiviert fast pwm
                                                   // COM = 10 aktiviert nichtinvertierende PWM
  TCCR2B = _BV(CS22);   //Prescaler = 
  OCR2A = 180;    //Output compare Wert
  
  //Pin 11 benutzt Timer2, Output A
  pinMode(pulseOut2, OUTPUT);   //pulseOut2 = pin 11
  TCCR2A = _BV(COM2A1)  | _BV(WGM21) | _BV(WGM20); //WGM = 011 aktiviert fast pwm
                                                   // COM = 10 aktiviert nichtinvertierende PWM
  TCCR2B = _BV(CS22);   //Prescaler = 
  OCR2A = 180;    //Output compare Wert
  
  interrupts();


  
  int preBeat = 10;         //Bevor sich etwas veraendert werden
  while(preBeat > 0){       //10 normale Herzschlaege geschickt
    if(sPulse == 1){
      sendPulse();
      sPulse = 0;
      preBeat--;
    }
  }
  patState = alive;
  Serial.println("Setup erfolgreich");
}

ISR(TIMER1_COMPA_vect){     //Frequenz dieses Interrupts: 200Hz
  freqCount++;
  analogValue = analogRead(impulseIn1);
  if(analogValue > impulseThreshold || (millis() < pulseStart + 200)){
    if(pulseStart == 0) 
      pulseStart = millis();
    digitalWrite(impulseLed1, HIGH);
  } else {
    digitalWrite(impulseLed1, LOW);
    pulseStart = 0;
  }  
  if(freqCount >= freqComp){
    freqCount = 0;
    sPulse = 1;
  }
}



void sendPulse(){
  /* In dieser Methode wird ein Herzschlag erzeugt.
   * Es wird die PWM-Funktion analogWrite verwendet,
   * da keine echten digitalen Werte mit dem Arduino
   * erzeugt werden koennen. Das PWM-Signal dieser
   * Funktion wird anschließend mit einem Tiefpassfilter
   * in einen analogen Wert umgewandelt.
   */
  unsigned long int sendRef = millis();
  analogWrite(pulseOut1, (ampl*255)/5);    //Herzschlag wird als PWM-Signal ausggeben.
  digitalWrite(pulseLed1, HIGH);//LED zeigt Herzschlag an
  while(millis()-sendRef < pulseDur){ //pulseDur in ms warten, waehrenddessen ueberpruefen
    if(analogValue > impulseThreshold){          //ob vom Schrittmacher faelschlicherweise
      patState = dead;//ein Impuls gesendet wird
      Serial.println("Pat. tot, Impuls waehrend Herzschlag");
      Serial.println("Todeszeitpunkt in s:");
      Serial.println(millis()/1000);
      break;
    }
  }
  digitalWrite(pulseOut1, LOW);
  while(millis()-sendRef < pulseDur + 200 && patState != dead){ //LED etwas laenger leuchten lassen
    if(analogValue > impulseThreshold){
      patState = dead;
      Serial.println("Pat. tot wg. Fehlimpuls direkt nach Herzschlag");
      Serial.println("Todeszeitpunkt in s:");
      Serial.println(millis()/1000);
      break;
    }
  }
  digitalWrite(pulseLed1, LOW);
}

void changeFreq(int cF){
  /* Hier wird die Herzfrequenz geaendert.
   */
  if(cF == 0){    //Wenn die Frequenz nach Belieben verändert werden soll
    cF = random(0, 7);
    noInterrupts();
    freq = freq + cF - 3;       //Herzfrequenz anpassen
    freq = constrain(freq, minHeartrate, maxHeartrate);   //Haelt die Herzfrequenz im Bereich 60-180bpm
    freqComp = 12000/freq;      //Umrechnung fuer Timer-Interrupt
    ampl = freq*0.0042 +0.25;   //Amplitude proportional zu Frequenz
    interrupts();
    Serial.println("Frequenz geaendert:");
    Serial.println(freq);
  }else{        //Wenn die Frequenz sich um einen bestimmten Wert verändern soll
    noInterrupts();
    freq = freq + cF;       //Herzfrequenz anpassen
    freq = constrain(freq, minHeartrate, maxHeartrate);   //Haelt die Herzfrequenz im Bereich 60-180bpm
    freqComp = 12000/freq;      //Umrechnung fuer Timer-Interrupt
    ampl = freq*0.016 + 1;      //Amplitude proportional zu Frequenz(2-4V)
    //ampl = freq*0.0042 +0.25;   //Amplitude proportional zu Frequenz
    interrupts();
    Serial.println("Frequenz:");
    Serial.println(freq);
    Serial.println("Frequenz geaendert um:");
    Serial.println(cF);
  }
}

void skipBeat(){
  pulseEnable = 0;
}

void physAct(){   //Hier wird eine koerperliche Anstrengung simuliert
  if(sport == 0){    //Erstmaliger Aufruf der Methode
    sport = 2;
    Serial.println("Koerperliche Aktivitaet begonnen");
  }
  if(sport == 1 && freq <= 90){      //Ende der koerperlichen Anstrengung
    sport = 0;
  }
  if(sport == 1 && freq > 90){      //Puls wieder senken
    changeFreq(-2);
  }
  if(sport == 2 && freq >= maxHeartrate){    //Leistungsspitze erreicht, Puls wieder senken lassen
    sport = 1;
  }
  if(sport == 2 && freq < maxHeartrate){       //Anstrengung, Frequenz erhoehen
    changeFreq(3);
  } 
}

void nextStep(){

  //Hier stimmt etwas mit den if-Abfragen von trainInterval nicht
  unsigned long int timeRef = millis();
  unsigned long int trainInterval = timeRef % 120000;   //Damit alle 2 min physAct() aufgerufen wird
  //if(trainInterval < 2000);{
  //  Serial.println(trainInterval);
  //}
  
  if(sport != 0){   //Falls die physAct-Methode noch "aktiv" ist
    if(lastDecide != 0){      //Aussetzer zufällig erzeugen
      decide = random(0,2);
    }else{                    //Kein Aussetzer, falls vorheriger
      decide = 1;             //Schlag ausgefallen ist
    }
  }else{            //Sonst wird zufällig der naechste Schritt gewaehlt
    decide = random(0, 6);
    if(timeRef < 30000 && decide == 1){  //physAct() erst ab 180s
      decide = 3;
    }else{
      if(lastDecide == 1 || lastDecide == 0){
        decide = 3;
      }else{
        if(trainInterval < 4000){ //physAct() aufrufen(Spielraum 4s)
          decide = 1;
        }
      }
    }
  }
  
  lastDecide = decide;    //Die Wahl speichern, um doppelte Aussetzer etc.
  switch(decide){         //zu vermeiden
    case 0:
      skipBeat();
      break;
    case 1:
      physAct();
      break;
    case 2:
      changeFreq(0);
      break;
    default:
      break;
  }
}

void nextStepLite(){    //Diese Methode sorgt dafuer, dass nach
  if(decide > 5){       //Einem Aussetzer mind. 3 Schlaege kommen
    decide--;
  }else{
    decide = random(0, 6);
  }
  if(lastDecide == 0){
    decide = 8;
  }
  lastDecide = decide;
  switch(decide){
    case 0:
      skipBeat();
      break;
    case 1:
    changeFreq(0);
      break;
    default:
      break;
  }
}

void waitForImp(){
  saved = 0;
  unsigned long int waitRef = millis();   //Ab hier wird die Reaktionszeit des Schrittmachers gemessen
  unsigned long int impTime = 0;
  patState = dead;
  //Serial.println("Auf Schrittmacher warten");
  long diff = 0;
  while( (diff = millis() - waitRef) <= maxDelay +1000 ){  //Pruefung der zeitl. Toleranzen
    if(analogValue > impulseThreshold){    //"Hardware-Interrupt" registriert eingehenden Impuls
      //Serial.println("Impuls angekommen");
      impTime = millis();
      delay(sampleDelay);    //die Anstiegszeit tau=10ms abwarten, um den richtigen Wert zu samplen
      absSampleDiff.clear();
      for(int i = 0; i < 6; i++){   //Mittelwert von 3 Samples bilden, um PWM-Zacken im Analogsignal zu kompensieren
        float tempSample1 = (analogValue/1023.0)*5 - ampl;
        float tempSample2 = fabs(tempSample1);    //tempSample2 ist die Differenz zwischen Ist- und Sollwert der Amplitude
        absSampleDiff.addValue(tempSample2);
        delay(2);
      }
      Serial.println(absSampleDiff.getAverage());
      Serial.print("Imp Recieved after: ");
      Serial.println(diff);
      if(absSampleDiff.getAverage() <= amplTolerance){    //Toleranz von +- 0,15V
        patState = alive;       //Impuls vom HS wurde innerhalb der Toleranzen gesendet
        saved = 1;
        break;
      }else{
        Serial.print("Impulsamplitude nicht korrekt: ");
        Serial.println(absSampleDiff.getAverage());
        // break;
      }
      patState = alive;   //Fuer Debugging ohne Beruecksichtigung der Amplitude
      saved = 1;
      break;
    }    
  }

 
  
  if(saved == 1){
    Serial.println("Yippie!");
    //Serial.println(impTime - waitRef);
    delay(100);      //Damit nicht vorzeitig in den else-Fall des loops gewechselt wird
  }else{
    Serial.println("Patient tot wegen zu langer Wartezeit auf Impuls, Todeszeitpunkt in s:");
    Serial.println(millis()/1000);
  }
}
 
void loop() {
  if(patState == alive){
    if(sPulse == 1 && patState == alive){
      if(pulseEnable == 1){     //normaler Herzschlag
        sendPulse();
        Serial.println("normaler Herzschlag");
      }else{                    //Aussetzer
        waitForImp();           //Auf Schrittmacher warten
      }
      if(saved = 1){
        saved = 0;
      }
      sPulse = 0;
      pulseEnable = 1;
      nextStep(); 
    }else{                //Wenn kein Puls/Impuls da sein sollte,
       if(analogValue > impulseThreshold){  //wird ueberprueft ob faelschlicherweise ein Impuls kommt.
          patState = dead;
          Serial.println("Patient tot wegen Fehlimpuls zwischen zwei Herzschlaegen");
          Serial.println("Todeszeitpunkt in s:");
          Serial.println(millis()/1000);
      }
    }
  }
  //Nichts tun wenn der Patient tot ist
}
