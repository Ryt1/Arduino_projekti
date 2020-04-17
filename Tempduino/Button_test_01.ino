#define DEBUG 1
#define ARD_LCD216 0

#ifdef ARD_LCD216
const int buttonPin = A0;
const float voltageEq = 5.0f / 1023.0f;   // Analog-signal-to-voltage-constant
float buttonValue;
#else
// Tähän teidän vakiomuuttujat pinneille joilla luetaan napit + muut vakiot tai muuttujat
#endif

// Function declarations.
int readButtons(void);

// Types
enum Buttons {
  BUTTON_NONE = 0,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_SELECT
} button;

void setup() {
  Serial.begin(9600);
}

void loop() {
  button = readButtons();
  #ifdef DEBUG
  Serial.println(button);
  #endif
}

#ifdef ARD_LCD216

int readButtons(void)
{
  buttonValue = analogRead(buttonPin);
  buttonValue *= voltageEq;

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

#else

int readButtons(void)
{
  // Teidän koodi tähän.
}

#endif
