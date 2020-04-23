#include <LiquidCrystal.h>
#include <SimpleDHT.h>

#define void alarm(almr)

// määritetään pinnit ja muuttujat
int mittari = 8;
int displaytila = 1;
SimpleDHT11 dht11(mittari);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

  byte temp = 0;
  byte hum = 0;
  

int almr = 0;

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

void loop() {
  

//luetaan arvot sensorilta ja käynnistetään hälytysfunktio
  dht11.read(&temp, &hum, NULL);
  alarm(almr);

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

void alarm(alrm)

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


// tästä eteenpäin alkaa temporary functions
//===============================================================================================


//tiloille. tila 1 = print celsius. tila 2= print fahrenheit. 
//tila 31 = print kosteus, muistissa aiempi celsius. tila 32 = print kosteus, muistissa aiempi fahrenheit
//kosteusmuunnin v2

void kosteusmuunnos()
{
  if(displaytila == 1) {
    displaytila = 31
    //vaihdetaan kosteudenesitykseen, muistiin aiempi tila celsius
  } else if(displaytila == 2) {
    displaytila = 32
    //vaihdetaan kosteudenesitykseen, muistiin aiempi tila fahrenheit
  } else if(displaytila == 31) {
    displaytila = 1
    //jos oltiin jo kosteustilassa, palaudutaan aikaisempaan aste asetukseen
  } else if(displaytila == 32) {
    displaytila = 2
    //jos oltiin jo kosteustilassa, palaudutaan aikaisempaan aste asetukseen
  } else {
    return;
  }
}

void fahrenheitmuutos()
{
  if(displaytila == 1) {
    displaytila = 2
  } else {
    displaytila = 1
  }
}
