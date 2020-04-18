
#ifdef ARD_LCD216
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
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  #ifndef ARD_LCD216
  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  #endif
}

void loop() {
  button = readButtons();
  #ifdef DEBUG
  Serial.println(button);
  #endif
}

// This code is for ARD LCD216: LCD + buttons-combination circuit.
#ifdef ARD_LCD216

int readButtons(void)
{
  buttonValue = analogRead(buttonPin);
  buttonValue *= voltageEq;
  Serial.println("Terve!");

  if (buttonValue < 5.0 && buttonValue >= 4.2) {
    #ifdef DEBUG
    Serial.println("Vasen-nappi painettu. ");
    #endif
    return BUTTON_LEFT;
  } else if (buttonValue < 4.0 && buttonValue >= 3.3) {
    #ifdef DEBUG
    Serial.println("Alas-nappi painettu. ");
    #endif
    return BUTTON_DOWN;
  } else if (buttonValue < 3.0 && buttonValue >= 2.4) {
    #ifdef DEBUG
    Serial.println("Ylös-nappi painettu. ");
    #endif
    return BUTTON_UP;
  } else if (buttonValue < 2.0 && buttonValue >= 1.2) {
    #ifdef DEBUG
    Serial.println("Oikea-nappi painettu. ");
    #endif
    return BUTTON_RIGHT;
  } else if (buttonValue < 1.0 && buttonValue >= 0.0) {
    #ifdef DEBUG
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
    #ifdef DEBUG
    Serial.println("Vasen-nappi painettu.");
    #endif
    return BUTTON_LEFT;
  } else if (digitalRead(buttonDownPin) == LOW) {
    #ifdef DEBUG
    Serial.println("Alas-nappi painettu.");
    #endif
    return BUTTON_DOWN;
  } else if (digitalRead(buttonUpPin) == LOW) {
    #ifdef DEBUG
    Serial.println("Ylös-nappi painettu.");
    #endif
    return BUTTON_UP;
  } else if (digitalRead(buttonRightPin) == LOW) {
    #ifdef DEBUG
    Serial.println("Oikea-nappi painettu.");
    #endif
    return BUTTON_RIGHT;
  } else if (digitalRead(buttonSelectPin) == LOW) {
    #ifdef DEBUG
    Serial.println("Select-nappi painettu.");
    #endif
    return BUTTON_SELECT;
  }

  return BUTTON_NONE;
}

#endif
