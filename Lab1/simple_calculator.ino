#define buttonPin 3
#define executePin 2
#define redPin 5
#define greenPin 4
// Not using a blue LED, simulating by lighting the red and green ones.


// Input & Output Arrays
int gInArrayA[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int gInArrayB[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int gOutArray[10] = {0};

// delay to determine debounce vs actual press.
const unsigned long gDebounceDelay = 40;     // ms

// variables to track the current and previous button states.
bool gButtonState = HIGH;
bool gLastButtonState = HIGH;

// State to track the execute button (not debounced)
bool gExecuteState = HIGH;

// Variables to track the last press and last debounce time for the select button.
unsigned long gLastDebounceTime = 0;
unsigned long gLastPressTime = 0;

// Variable to track the number of select button presses.
int gPressCount = 0;

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
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);

  // Print a newline to the terminal 
  Serial.println();
}

void loop() {
  // Booleans to track the input state of both buttons.
  bool reading1 = digitalRead(buttonPin);
  bool reading2 = digitalRead(executePin);

  // If a change happens with button state, record the time.
  if (reading1 != gLastButtonState) {
    gLastDebounceTime = millis();
  }

  // Detect a valid press (longer than defined debounce delay)
  if ((millis() - gLastDebounceTime) > gDebounceDelay) {

    // Button pressed (LOW because of pullup)
    if (reading1 == LOW && gButtonState == HIGH) {
      gPressCount++;
      gLastPressTime = millis();
    }
    // update the button state to the current reading.
    gButtonState = reading1;
  }
  // update the last button state to the current reading.
  gLastButtonState = reading1;


  // If the execute button is currently pressed and press count > 0, execute the calculation.
  if (reading2 == LOW && gPressCount > 0) {
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
      digitalWrite(redPin, HIGH);
      add();
      gPressCount = 0;
      break;

    case 2:
      // If two button presses....subtract, print, and reset count.
      Serial.println("Double press");
      digitalWrite(greenPin, HIGH);
      subtract();
      gPressCount = 0;
      break;

    case 3:
      // If three button presses....multiply, print, and reset count.
      Serial.println("Triple press");
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, HIGH);
      multiply();
      gPressCount = 0;
      break;

    default:
      // If more than three button presses....assume three presses; multiply, print, and reset count.
      Serial.print("Too many presses: ");
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, HIGH);
      multiply();
      gPressCount = 0;
      break;
  }
  // delay before turning off the LEDs and repeating loop.
  delay(2000);
  ledsOff();
}