#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// määritetään pinnit
int mittari = 8;
SimpleDHT11 dht11(mittari);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

pinMode(6, INPUT);
pinMode(7, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);

void setup() {
  // määritetään näytön koko:
  lcd.begin(20, 4);
  // tulostetaan pysyvät tekstit näytölle:
  lcd.setCursor(0, 0);
  lcd.print("Temperature (C):");
}

void loop() {
  
//määritetään muuttujat lämpötila-anturia varten
  byte temp = 0;
  byte hum = 0;
  
//luetaan arvot sensorilta
  dht11.read(&temp, &hum, NULL);

//asetetaan kursori oikeaan paikkaan ja tulostetaan lämpötila
  lcd.setCursor(0, 2);
  lcd.print(temp);

//luetaan napit
  if(digitalRead(6) == HIGH) {
    //suorita kosteusaliohjelma
  } else if(digitalRead(7) == HIGH) {
    //suorita fahrenheitaliohjelma
  } else if(digitalRead(9) == HIGH) {
    //suorita valikkoaliohjelma
  } else if(digitalRead(10) == HIGH) {
    //suorita näytön-sammutus-aliohjelma
  } else {
    delay(500)
  }
  
  
}
