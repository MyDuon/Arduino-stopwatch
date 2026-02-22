#include <LiquidCrystal.h> //the liquid cyrstal library
#include <math.h>

// minutt:sekund:millisekund
int milliSekunder = 0; //milliseconds
int sekunder = 0;//seconds
int minutter = 0;//minutes

// en knapp for start
int startKnapp = 4; 
int switchStateStart = 0;

// en knapp for stopp
int stoppKnapp = 5;
int switchStateStop = 0;

// en knapp for lagrer sist tid man trykket på knappen
int lapKnapp = 6;
int switchStateLap = 0;


// definere pins paa arduinoen som blir brukt
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void oppdaterTid() {

  lcd.setCursor(0, 0);
  lcd.print("Tid ");
  lcd.print(minutter);
  lcd.print(":");
  lcd.print(sekunder);
  lcd.print(":");
  lcd.print(milliSekunder);
}

void skriverUtSisteTid() {

    lcd.setCursor(0, 1);
    lcd.print("Sist ");
    lcd.print(minutter);
    lcd.print(":");
    lcd.print(sekunder);
    lcd.print(":");
    lcd.print(milliSekunder);
}

// setter opp pins og LCD
void setup() {

  // displayet til LCD-en er 16 x 2 sa vi definerer at vi bruker hele LCD-en
  lcd.begin(16, 2);
  
  // siden vi bruker knapper saa definerer vi dem som INPUT_PULLUP
  pinMode(startKnapp, INPUT_PULLUP);
  pinMode(stoppKnapp, INPUT_PULLUP);
  pinMode(lapKnapp, INPUT_PULLUP);
  lcd.setCursor(0, 0);
  // printer Stoppeklokke naar man slaar den paa
  lcd.print("Stoppeklokke-");
  delay(1000);
  lcd.clear();
}

void loop() {

  // sjekker om knappene er LOW eller HIGH
  switchStateStop = digitalRead(stoppKnapp);
  switchStateLap = digitalRead(lapKnapp);
  switchStateStart = digitalRead(startKnapp);

  // vi vil at LCD-en skal vise 0.0.0s
  // printer tid først og deretter minutter:sekunder:millisekunder
  oppdaterTid();

  // hvis ingen start knappen IKKE er trykke så skal milli, sekund, minutt være 0
  if (switchStateStart == HIGH) {
    milliSekunder = 0;
    sekunder = 0;
    minutter = 0;
  }
  // hvis start knapp er trykke 
  else {
    // bruker for loop siden millisekunder gaar fra 0 til 100
    for (milliSekunder = 0; milliSekunder <= 100; milliSekunder++) {
      // maa ha delay for at det skal rytmen skal vaere korrekt
      delay(5);
      // hvis millisekund er hundre, start fra null igjen
      if (milliSekunder == 100) {
        milliSekunder = 0;
        //og ett sekund blir lagt til
        sekunder += 1;

        // oppdaterer displayet med sekunder
        oppdaterTid();
      }
      // hvis sekunder er 60 saa skal alt oppdateres og ett minutt blir lagt til
      if (sekunder == 60) {
        lcd.clear();
        sekunder = 0;
        milliSekunder = 0;
        minutter += 1;
        
        // opdaterer den nye verdien med minutter
        oppdaterTid();
      }

      // oppdaterer nye verdien til slutt
      oppdaterTid();

      // sjekker om knappene er LOW eller HIGH
      switchStateStop = digitalRead(stoppKnapp);
      switchStateLap = digitalRead(lapKnapp);

      // hvis stoppknappen blir trykket inn
      if (switchStateStop == LOW) {
        while(switchStateStop == LOW){
          switchStateStart = digitalRead(startKnapp);
          // oppdaterer naavarende verdier uten aa endre paa noe
          oppdaterTid();
          if (switchStateStart == LOW) {
            lcd.clear();
            // bruker break for aa komme ut av while loopen
            break;
          }
        }
      }

      // sjekker om lap knappen er LOW eller HIGH
      switchStateLap = digitalRead(lapKnapp);
      // knappen blir trykket paa
      if(switchStateLap == LOW){
          // skriver ut tiden paa bunnen av skjermen
          skriverUtSisteTid();
      }
    }
  }
}