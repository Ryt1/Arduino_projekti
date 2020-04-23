#include <LiquidCrystal.h>
#include <SimpleDHT.h>


// määritetään pinnit ja muuttujat
int mittari = 8;
int displaytila = 1;
int raja = 35;
int almr = 0;
SimpleDHT11 dht11(mittari);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

  byte temp = 0;
  byte hum = 0;
  

void setup() {

pinMode(6, INPUT);
pinMode(7, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);
pinMode(A1, OUTPUT);
  
  // määritetään näytön koko:
  lcd.begin(20, 4);
  // tulostetaan pysyvät tekstit näytölle:
  lcd.setCursor(0, 0);
  lcd.print("Temperature (C):");
}


void alarm() {
int alrm = 1;
switch(alrm) {
  case 1:
    if(temp < raja) {
      digitalWrite(A1, HIGH);
      delay(500);
      digitalWrite(A1, LOW);
      delay(500);
    }
    break;
  case 2:
    if(temp > raja) {
      digitalWrite(A1, HIGH);
      delay(500);
      digitalWrite(A1, LOW);
      delay(500);
    }
    break;
  default:
    break;
}
}

void kosteusmuunnos()
{
 if (displaytila == 1)
  {
    displaytila = 31;
  } 
  else if (displaytila == 2)
  {
    displaytila = 32;
  } 
  else if (displaytila == 31)
  {
    displaytila = 1;
  } 
  else if (displaytila == 32)
  {
    displaytila = 2;
  } 
  else 
  {
    return;
  }
}

void fahrenheitmuutos()
{
  if(displaytila == 1) {
    displaytila = 2;
  } else {
    displaytila = 1;
  }
}
  
void tulostusfunktio()
{
int fahrenheit = temp*1.8+32;
  switch (displaytila) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature (C):");
      lcd.setCursor(0, 1);
      lcd.print(temp);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature (F):");
      lcd.setCursor(0, 1);
      lcd.print(fahrenheit);
      break;
    case 31:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Humidity (%):");
      lcd.setCursor(0, 1);
      lcd.print(hum);
      break;
    case 32:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Humidity (%):");
      lcd.setCursor(0, 1);
      lcd.print(hum);
      break;
    default:
      break;
  }
}

void loop() {
//luetaan arvot sensorilta ja käynnistetään hälytysfunktio
  dht11.read(&temp, &hum, NULL);
  alarm();

//asetetaan kursori oikeaan paikkaan ja tulostetaan lämpötila
  lcd.setCursor(0, 2);
  lcd.print(temp);

//luetaan napit
  if(digitalRead(6) == HIGH) {
    kosteusmuunnos();
  } else if(digitalRead(7) == HIGH) {
    fahrenheitmuutos();
  } else if(digitalRead(9) == HIGH) {
    //suorita valikkoaliohjelma
    delay(500);
  } else if(digitalRead(10) == HIGH) {
    delay(500);
  } else {
    tulostusfunktio();
    delay(500);
  } 
}
