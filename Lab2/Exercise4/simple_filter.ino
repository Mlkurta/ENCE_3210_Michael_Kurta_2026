#define BUTTON_PIN 2
#define ARRAY_SIZE 10
#define ADC_PIN A0

const int DEBOUNCE_DELAY_MS = 150;

// Button state interrupt flag
volatile bool gButtonState = false;

// Variable to track the last press and last debounce time for the select button.
unsigned long gLastDebounceTime = 0;

// Additional variable to be able to track the button state outside of the button ISR flag (for debouncing)
bool gReading1 = HIGH;

unsigned long int gArray[ARRAY_SIZE] = {10,9,8,7,6,5,4,3,2,1};

void setup() {
  // Initialize the serial terminal 
  Serial.begin(9600);

  // Initialize the button and analog input pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(ADC_PIN, INPUT);

  // Attach an interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button, FALLING);
  noInterrupts();

  // unsigned integer for ADC values.
  unsigned long int adcVal;

  // Load the array with values generated from the ADC
  for(int i = 0; i < ARRAY_SIZE; i++){
    adcVal = analogRead(ADC_PIN);
    gArray[i] = adcVal;
  }

  // Initialize the last recorded debounce time to some variable close to the current time
  // Avoids negative subtraction.
  gLastDebounceTime = millis();
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(gButtonState == true){
    gButtonState = false;
    gReading1 = LOW;
  }

  // Detect a valid press (longer than defined debounce delay)
  if ((millis() - gLastDebounceTime) > DEBOUNCE_DELAY_MS) {

    // Button pressed (LOW because of pullup)
    if (gReading1 == LOW) {
      gLastDebounceTime = millis();
      gReading1 = HIGH;
      filterOperation();
    }
  }else{
    // Reset the read state of button 1 so that it does not count gPressCount by default when the debounce delay has elapsed.
    gReading1 = HIGH;
  }
}

void filterOperation(){
  int i = 0;
  int temp;
  for(i=0; i<ARRAY_SIZE; i++){
    temp = gArray[i];
    gArray[i] = 2*gArray[i] - gArray[i-1];

    Serial.print("Input: ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(temp);
    Serial.print("\tOutput: ");
    Serial.println(gArray[i]);

  }
}

void isr_button(){
  gButtonState = true;
} 