#include <LiquidCrystal.h>
#include <SimpleDHT.h>


// määritetään pinnit ja muuttujat

int mittari = 8;
int displaytila = 1;
int raja = 35;
int alrm = 1;
int menuopen = 1;
SimpleDHT11 dht11(8);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte temp = 0;
byte hum = 0;

  

void setup() {

pinMode(6, INPUT);
pinMode(7, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);
pinMode(13, OUTPUT);
digitalWrite(13, LOW);
  
  // määritetään näytön koko:
  lcd.begin(20, 4);
  // tulostetaan pysyvät tekstit näytölle:
  lcd.setCursor(0, 0);
  lcd.print("Temperature (C):");
}


void alarm() {
switch(alrm) {
  case 1:
    if(temp < raja) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
    break;
  case 2:
    if(temp > raja) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
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

void menu()
{   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm is set:");
    lcd.setCursor(0, 1);
    if (alrm == 1) {
      lcd.print("<");
    } else {
      lcd.print(">");
    }
    lcd.print(raja);
    delay(300);

while(menuopen==2){

    if(digitalRead(7) == HIGH){
        raja = raja+1;
        lcd.setCursor(1, 1);
        lcd.print(raja);
        delay(300);

    } 
    else if(digitalRead(6) == HIGH){
        raja = raja-1;
        lcd.setCursor(1, 1);
        lcd.print(raja);
        delay(300);

    }
    else if(digitalRead(10) == HIGH){
        alrm = (alrm == 1) ? 2 : 1;
        delay(300);
        menu();
    }
    else if(digitalRead(9) == HIGH){
        menuopen=1;
        return;
    }
    else {
        menu();
    }
}

}


void loop() {
//luetaan arvot sensorilta ja käynnistetään hälytysfunktio

while(menuopen==1){
//luetaan napit
  dht11.read(&temp, &hum, NULL);
  alarm();
  if(digitalRead(6) == HIGH) {
    kosteusmuunnos();
  } else if(digitalRead(7) == HIGH) {
    fahrenheitmuutos();
  } else if(digitalRead(9) == HIGH) {
    menuopen=2;
    menu();
    delay(500);
  } else if(digitalRead(10) == HIGH) {
    delay(500);
  } else {
    tulostusfunktio();
    delay(500);
  } 
}
}
