
// Pin definitions
#define RED_PIN 5
#define GREEN_PIN 4
#define BUTTON_PIN 3

// delay to determine debounce vs actual press.
const unsigned int DEBOUNCE_DELAY_MS  = 250;     // ms

// default button state (input pullup in external hardware).
volatile bool gButtonPressed = false;

// Variable to track the last press and last debounce time for the select button.
unsigned long gLastDebounceTime = 0;

// Additional variable to be able to track the button state outside of the button ISR flag (for debouncing)
bool gReading1 = HIGH;

// Enumerate the LED states.
typedef enum {
    STATE_R = 0,
    STATE_RG,
    STATE_RGB,
    STATE_GB,
    STATE_B,
    STATE_RB,
} LedState;

// bool to toggle LED sequence.
bool running = false;

// Enum initialization and starting state.
int state = STATE_R;

void setup() {
  // Initialize serial (UART) at 9600 baud.
  Serial.begin(9600);
  // set the pin to input.
  pinMode(BUTTON_PIN, INPUT);

  // Initialize the LED pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Print a newline to the terminal 
  Serial.println();

  // Attach interrupt for the button.
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button, FALLING);

  // Initialize the last recorded debounce time to some variable close to the current time
  // Avoids negative subtraction.
  gLastDebounceTime = millis();

}

void loop() {
  // if button press is detected:
  if(gButtonPressed){
    gButtonPressed = false;
    gReading1 = LOW;
    gLastDebounceTime = millis();
  }

  // Detect a valid press (longer than defined debounce delay)
  if ((millis() - gLastDebounceTime) > DEBOUNCE_DELAY_MS) {

    // Button pressed (LOW because of pullup)
    if (gReading1 == LOW) {
      gLastDebounceTime = millis();
      gReading1 = HIGH;
      digitalWrite(GREEN_PIN, 1);
      running = !running;
    }
  }

  // Turn LEDs off every loop iteration
    digitalWrite(RED_PIN, 0);
    digitalWrite(GREEN_PIN, 0);
    delay(500);
    // Blue pin optional depending on the hardware used.
    // digitalWrite(BLUE_PIN, 0);

  // Every loop iteration, check if the LED sequence is running.
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
        //digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_GB:    // Green & Blue LEDs.
        digitalWrite(GREEN_PIN, HIGH);
        //digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_B:     // Blue LED only.
        //digitalWrite(BLUE_PIN, HIGH);
        break;

      case STATE_RB:    // Red & Blue LEDs.
        digitalWrite(RED_PIN, HIGH);
        //digitalWrite(BLUE_PIN, HIGH);
        break;

      default:
      // Do nothing unless an explicit matching state is achieved.
        break;

    }

    // Increment the state only if running.
    state += 1;
    // delay 1/2 sec.
    delay(500);

    // Reset the state to 0 if we reached the max state.
    if(state > 5){
      running = 0;
    }
  }else{
    // If not running, reset the state to the first state.
    state = STATE_R;
  }

}

// Interrupt service routine to set the button pressed flag.
void isr_button(){
  gButtonPressed = true;
}
