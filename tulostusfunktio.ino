void tulostusfunktio() {

  switch (displaytila) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature (C):");
      lcd.setCursor(0, 1);
      lcd.print(temp);
      break;
    case 2:
      
      int fahrenheit = temp*1.8+32;
      
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
