// Define pins
#define BUTTON_PIN 3
#define EXECUTE_PIN 2
#define RED_LED 5
#define GREEN_LED 4
// Not using a blue LED, simulating by lighting the red and green ones.


// Input & Output Arrays
int gInArrayA[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int gInArrayB[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int gOutArray[10] = {0};

// delay to determine debounce vs actual press.
const unsigned int DEBOUNCE_DELAY_MS  = 150;     // ms
const unsigned int LED_OFF_DELAY      = 500;    // ms 

// variables to track the current and previous button states.
volatile bool gButtonState = false;

// State to track the execute button (not debounced)
bool gExecuteState = HIGH;

// Variable to track the last press and last debounce time for the select button.
unsigned long gLastDebounceTime = 0;

// Variable to track the number of select button presses.
int gPressCount = 0;

// Additional variable to be able to track the button state outside of the button ISR flag (for debouncing)
bool gReading1 = HIGH;

// Add function.
void add(){
  for(int i = 0; i < 10; i++){
    gOutArray[i] = gInArrayA[i] + gInArrayB[i];
    Serial.print(gInArrayA[i]);
    Serial.print(" + ");
    Serial.print(gInArrayB[i]);
    Serial.print(" = ");
    Serial.println(gOutArray[i]);
  }
}

// Subtract function.
void subtract(){
  for(int i = 0; i < 10; i++){
    gOutArray[i] = gInArrayA[i] - gInArrayB[i];
    Serial.print(gInArrayA[i]);
    Serial.print(" - ");
    Serial.print(gInArrayB[i]);
    Serial.print(" = ");
    Serial.println(gOutArray[i]);
  }
}

// Multiply function. 
void multiply(){
  for(int i = 0; i < 10; i++){
    gOutArray[i] = gInArrayA[i] * gInArrayB[i];
    Serial.print(gInArrayA[i]);
    Serial.print(" * ");
    Serial.print(gInArrayB[i]);
    Serial.print(" = ");
    Serial.println(gOutArray[i]);
  }
}

// Function to turn the LEDs off.
void ledsOff(){
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button, FALLING);

  // Print a newline to the terminal 
  Serial.println();

  // Initialize the last recorded debounce time to some variable close to the current time
  // Avoids negative subtraction.
  gLastDebounceTime = millis();
}

void loop() {
  // Booleans to track the input state of both buttons.

  if(gButtonState == true){
    gButtonState = false;
    gReading1 = LOW;
  }

  bool reading2 = digitalRead(EXECUTE_PIN);

  // Detect a valid press (longer than defined debounce delay)
  if ((millis() - gLastDebounceTime) > DEBOUNCE_DELAY_MS) {

    // Button pressed (LOW because of pullup)
    if (gReading1 == LOW) {
      gPressCount++;
      gLastDebounceTime = millis();
      gReading1 = HIGH;
    }
  }
  else{
    // Reset the read state of button 1 so that it does not count gPressCount by default when the debounce delay has elapsed.
    gReading1 = HIGH;
  }


  // If the execute button is currently pressed and press count > 0, execute the calculation.
  if (reading2 == HIGH && gPressCount > 0) {
    handlePresses(gPressCount);
  }
}

// Function to goto when the execute button is pressed, to illumunate the LED(s) and print the gOutArray contents.
void handlePresses(int count) {
  // Count is the number of recorded button presses.
  switch (count) {
    case 1:
      // If one button press....add, print, and reset count.
      Serial.println("Single press");
      digitalWrite(RED_LED, HIGH);
      add();

      // Reset the press count.
      gPressCount = 0;
      break;

    case 2:
      // If two button presses....subtract, print, and reset count.
      Serial.println("Double press");
      digitalWrite(GREEN_LED, HIGH);
      subtract();

      // Reset the press count.
      gPressCount = 0;
      break;

    case 3:
      // If three button presses....multiply, print, and reset count.
      Serial.println("Triple press");
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      multiply();

      // Reset the press count.
      gPressCount = 0;
      break;

    default:
      // If more than three button presses....assume three presses; multiply, print, and reset count.
      Serial.print("Too many presses: ");
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      multiply();

      // Reset the press count.
      gPressCount = 0;
      break;
  }
  // turn off interrupts, delay before turning off the LEDs and repeating loop.
  noInterrupts();
  delay(LED_OFF_DELAY);

  // turn interrupts back on.
  interrupts();

  // Turn LEDs off after a print statement and delay.
  ledsOff();

}

void isr_button(){
  gButtonState = true;
} 