#include <LiquidCrystal.h>   
    
      // Einführung der Pins
const int RelAkSZ = 9;                          // Pin für das Relais zwischen Akku und Solarzelle
const int RelAkVer = 8;                         // Pin für das Relais zwischen Akku und Verbraucher
      // Einführung der Pins des Displays       
const int rs = 12;                              // Pin für Datenübertragung
const int en = 11;                              // Pin für Datenübertragung
const int d4 = 5;                               // Pin für Datenübertragung
const int d5 = 4;                               // Pin für Datenübertragung
const int d6 = 3;                               // Pin für Datenübertragung
const int d7 = 2;                               // Pin für Datenübertragung

    const int HValStSt = 0.5;                   // Höchstmögliche Stromstärke der Solarzellen
    const int VerbValOrg = 0;                   // Originaler Verbrauch des Verbrauchers in Ampere

    const int Delay = 2000;                     // Delay    

const float StS = A1;                           // Analoger Pin für den Stromstärkesensor
const float StVerb = A2;                        // Analoger Pin für den Stromstärkesensor für des Verbrauchers


      // Einführen der Variablen
float SensorVal;                                // Variable für den Eingangswert des Stromstärkesensors
float StStVal;                                  // Variable für den Stromstärkewert des Stromstärkemessers
int VerbVal;                                    // Verbrauch des Verbrauchers in Ampere
int VerState;                                   // Status des Verbrauchers
String StatAkk;                                 // Status des Akkus für das Display
String leer = "                ";               // Variable die für das löschen der Inhalte auf dem Display benötigt wird

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);      // Erste Indizierung des Displays

      // Indizieren der Pins
      // Dieser Teil des Codes wird einmal zum Start ausgeführt
void setup() {
  pinMode(RelAkSZ, OUTPUT);                     // Schaltet Pin 2 (RelAkSZ) in den Output Modus
  pinMode(RelAkVer, OUTPUT);                    // Schaltet Pin 4 (RelAkVEr) in den Output Modus

  lcd.begin(16,2);                              // Zweite Indizierung des Displays

  Serial.begin(9600);                           // Startet den Seriellen Monitor (benötigt zum debuggen)
}
      // Hauptteil des Codes
      // Dieser Teil des Codes wird stetig wiederholt
void loop() {
    SensorVal = analogRead(StS);                // Liest den Wert des Stromstärkesensors an Pin A1
    StStVal = SensorVal * (HValStSt / 1023.0);  // Konvertiert den ausglesen Wert (von 0-1023) in Ampere (0 - Höchstmögliche Stromstärke der Solarzellen)

    Serial.println(StStVal);                    // Schreibt den berechneten Amperewert in den Seriellen Monitor (benötigt zum debuggen)

    VerState = analogRead(StVerb);              // Liest den Wert des Stromstärkesensors an Pin A2
  if (VerState == 0){                           // Wenn keine Spannung am Pin anliegt
      VerbVal = 0;                              // Dann ist der Verbrauch 0, weil der Verbraucher keinen Strom benötigt
  }
  else{                                         // Wenn Spannung am Pin anliegt
      VerbVal = VerbValOrg;                     // Dann ist der Verbrauch so hoch wie oben bestimmt
  }
      // Schleife um die Relais zu schalten
  if (StStVal < VerbVal){                       // Wenn die Stromstärke der Solarzellen kleiner als der bestimmte Verbrauch ist
      digitalWrite(RelAkSZ,LOW);                // Ist das Relais zwischen Akku und Solarzellen geöffnet     (kein Stromfluss)
      digitalWrite(RelAkVer, HIGH);             // Ist das Relais zwischen Akku und Verbraucher geschlossen  (Stromfluss)
      StatAkk = "wird entladen.";               // Wird die Variable für das Display auf "wird entladen." geändert

      Serial.println(StStVal);                  // Schreibt den Wert des Integers StStVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
      Serial.print("  <  ");                    // Schreibt ein < in den seriellen Monitor                                          (benötigt zum debuggen)
      Serial.print(VerbVal);                    // Schreibt den Wert des Integers VerbVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
  }
  else if(StStVal == VerbVal){                  // Wenn die Stromstärke der Solarzellen gleich dem Verbrauch ist
      digitalWrite(RelAkSZ, LOW);               // Ist das Relais zwischen Akku und Solarzellen geöffnet     (kein Stromfluss)
      digitalWrite(RelAkVer, LOW);              // Ist das Relais zwischen Akku und Verbraucher geöffnet     (kein Stromfluss)
      StatAkk = "tut nichts.";                  // Wird die Variable für das Display auf "tut nichts." geändert

      Serial.println(StStVal);                  // Schreibt den Wert des Integers StStVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
      Serial.print("  =  ");                    // Schreibt ein = in den seriellen Monitor                                          (benötigt zum debuggen)  
      Serial.println(VerbVal);                  // Schreibt den Wert des Integers VerbVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
  }
  else if (StStVal > VerbVal){
      digitalWrite(RelAkSZ, HIGH);              // Ist das Relais zwischen Akku und Solarzellen geschlossen  (Stromfluss)
      digitalWrite(RelAkVer, LOW);              // Ist das Relais zwischen Akku und Verbraucher geöffnet     (kein Stromfluss)
      StatAkk = "lädt.";                        // Wird die Variable für das Display auf "lädt." geändert

      Serial.println(StStVal);                  // Schreibt den Wert des Integers StStVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
      Serial.print("  >  ");                    // Schreibt ein > in den seriellen Monitor                                          (benötigt zum debuggen)  
      Serial.println(VerbVal);                  // Schreibt den Wert des Integers VerbVal in eine neuen Zeile im seriellen Monitor  (benötigt zum debuggen)
  }
      Display();                                // Klasse Display wird aufgerufen
  delay(Delay);                                 // Delay zwischen dem neu lesen und schalten der Relais
}
    // Klasse für Seite 2 des Displays
void Display(){

    Verb();                                   // Klasse Verb wird aufgerufen
    delay(1000);                              // 1 Sekunde Delay
    lcd.setCursor(0,0);                       // Der Cursor wird auf Reihe 1 und Zeile 1 gesetzt
    lcd.print(leer);                          // Zeile 1 wird gelöscht
    lcd.setCursor(0,1);                       // Der Cursor wird auf Reihe 1 und Zeile 2 gesetzt
    lcd.print(leer);                          // Zeile 2 wird gelöscht

    lcd.setCursor(0,0);                       // Der Cursor wird auf Reihe 1 und Zeile 1 gesetzt
    lcd.print("Der Akku");                    // In Zeile 1 ab Anfang wird "Der Akku" geschrieben
    lcd.setCursor(0,1);                       // Der Cursor wird auf Reihe 1 und Zeile 2 gesetzt
    lcd.print(StatAkk);                       // In Zeile 2 ab Anfang wird die Variable StatAkk ausgegeben
    delay(2000);                              // 2 Sekunden Delay

    lcd.setCursor(0,0);                       // Der Cursor wird auf Reihe 1 und Zeile 1 gesetzt
    lcd.print(leer);                          // Zeile 1 wird gelöscht
    lcd.setCursor(0,1);                       // Der Cursor wird auf Reihe 1 und Zeile 2 gesetzt
    lcd.print(leer);                          // Zeile 2 wird gelöscht

  
}
    // Klasse für Seite 1 des Displays
void Verb(){

    lcd.setCursor(0,0);                       // Der Cursor wird auf Reihe 1 und Zeile 1 gesetzt
    lcd.print("Verb:");                       // In Zeile 1 ab Anfang wird "Verb:" geschrieben
    lcd.setCursor(0,1);                       // Der Cursor wird auf Reihe 1 und Zeile 2 gesetzt
    lcd.print(VerbVal);                       // In Zeile 2 ab Anfang wird die Variable VerbVal ausgegeben
    lcd.setCursor(5,1);                       // Der Cursor wird auf Reihe 5 und Zeile 2 gesetzt
    lcd.print("A");                           // In Zeile 2 ab Reihe 5 wird "A" geschrieben

    lcd.setCursor(8,0);                       // Der Cursor wird auf Reihe 8 und Zeile 1 gesetzt
    lcd.print("Herg:");                       // In Zeile 1 ab Reihe 8 wird "Herg:" geschrieben
    lcd.setCursor(8,1);                       // Der Cursor wird auf Reihe 8 und Zeile 2 gesetzt
    lcd.print(SensorVal);                     // In Zeile 1 ab Reihe 8 wird die Variable SensorVal ausgegeben
    lcd.setCursor(13,1);                      // Der Cursor wird auf Reihe 13 und Zeile 2 gesetzt
    lcd.print("A");                           // In Zeile 2 ab Reihe 13 wird "A" geschrieben
}