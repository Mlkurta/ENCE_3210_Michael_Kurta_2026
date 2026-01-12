#define INPUT_PIN 3

// Pin definitions
#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9

// default button state (input pullup).
uint8_t buttonState = 1;

// Enumerate the LED states.
typedef enum {
    STATE_R = 0,
    STATE_RG,
    STATE_RGB,
    STATE_GB,
    STATE_B,
    STATE_RB,
    STATE_COUNT
} LedState;

// bool to toggle state.
bool running = false;
// Enum initialization and starting state.
LedState state = STATE_R;

void setup() {
  // Initialize serial (UART) at 9600 baud.
  Serial.begin(9600);
  // set the pin to input pullup.
  pinMode(INPUT_PIN, INPUT_PULLUP);

  // Initialize the LED pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);


}

void loop() {
  // Read the pinstate:
  buttonState = digitalRead(INPUT_PIN);
  
  // if button press is detected:
  if(buttonState == LOW){

    running = !running;     // toggle the running state
    delay(200);             // delay .2 s for debouncing 
  }

  // Turn LEDs off every loop iteration
    digitalWrite(RED_PIN, 0);
    digitalWrite(GREEN_PIN, 0);
    digitalWrite(BLUE_PIN, 0);

  if(running){

    // switch / case statement to transition LED states.
    switch (state)
    {
      case STATE_R:     // Red LED only.
        digitalWrite(RED_PIN, HIGH);
        break;

      case STATE_RG:    // Red & Green LED.
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        break;

      case STATE_RGB:   // Red, Green & Blue LEDs.
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_GB:    // Green & Blue LEDs.
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_B:     // Blue LED only.
        digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_RB:    // Red & Blue LEDs.
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        break;

      default:
        break;
    }

    // Increment the state only if running.
    state = (state + 1) % STATE_COUNT;
    // delay 1/2 sec.
    delay(500);
  }else{
    // If not running, reset the state to the first state.
    state = STATE_R;
  }

}
