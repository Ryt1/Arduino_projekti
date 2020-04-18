#define DEBUG_INFO 1
#define ARD_LCD216 0

#if ARD_LCD216
const int buttonPin = A0;
const float voltageEq = 5.0f / 1023.0f;   // Analog-signal-to-voltage-constant
float buttonValue;
#else
const int buttonLeftPin = 6;
const int buttonRightPin = 7;
const int buttonUpPin = 8;
const int buttonDownPin = 9;
const int buttonSelectPin = 10;
// Tähän teidän vakiomuuttujat pinneille joilla luetaan napit + muut vakiot
#endif

// Function declarations.
int readButtons(void);

enum Buttons {
  BUTTON_NONE = 0,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_SELECT
} button;

void setup() {
  #if DEBUG_INFO
  Serial.begin(9600);
  #endif

  #if !ARD_LCD216
  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  #endif
}

void loop() {
  button = readButtons();
  #if DEBUG_INFO
  Serial.println(button);
  #endif
}

// This code is for ARD LCD216: LCD + buttons-combination circuit.
#if ARD_LCD216

int readButtons(void)
{
  buttonValue = analogRead(buttonPin);
  buttonValue *= voltageEq;
  
  if (buttonValue < 5.0 && buttonValue >= 4.2) {
    #if DEBUG_INFO
    Serial.println("Vasen-nappi painettu. ");
    #endif
    return BUTTON_LEFT;
  } else if (buttonValue < 4.0 && buttonValue >= 3.3) {
    #if DEBUG_INFO
    Serial.println("Alas-nappi painettu. ");
    #endif
    return BUTTON_DOWN;
  } else if (buttonValue < 3.0 && buttonValue >= 2.4) {
    #if DEBUG_INFO
    Serial.println("Ylös-nappi painettu. ");
    #endif
    return BUTTON_UP;
  } else if (buttonValue < 2.0 && buttonValue >= 1.2) {
    #if DEBUG_INFO
    Serial.println("Oikea-nappi painettu. ");
    #endif
    return BUTTON_RIGHT;
  } else if (buttonValue < 1.0 && buttonValue >= 0.0) {
    #if DEBUG_INFO
    Serial.println("Select-nappi painettu. ");
    #endif
    return BUTTON_SELECT;
  }
  
  return BUTTON_NONE;
}

// Not an ARD LCD216. Every button is handled by different pin.
#else

int readButtons(void)
{
  if (digitalRead(buttonLeftPin) == LOW) {
    #if DEBUG_INFO
    Serial.println("Vasen-nappi painettu.");
    #endif
    return BUTTON_LEFT;
  } else if (digitalRead(buttonDownPin) == LOW) {
    #if DEBUG_INFO
    Serial.println("Alas-nappi painettu.");
    #endif
    return BUTTON_DOWN;
  } else if (digitalRead(buttonUpPin) == LOW) {
    #if DEBUG_INFO
    Serial.println("Ylös-nappi painettu.");
    #endif
    return BUTTON_UP;
  } else if (digitalRead(buttonRightPin) == LOW) {
    #if DEBUG_INFO
    Serial.println("Oikea-nappi painettu.");
    #endif
    return BUTTON_RIGHT;
  } else if (digitalRead(buttonSelectPin) == LOW) {
    #if DEBUG_INFO
    Serial.println("Select-nappi painettu.");
    #endif
    return BUTTON_SELECT;
  }

  return BUTTON_NONE;
}

#endif
