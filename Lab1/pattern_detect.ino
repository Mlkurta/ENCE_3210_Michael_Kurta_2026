// Define pins as LED pins (PWM capable ones as default for brightness control if desired)
#define RED_PIN 11
#define GREEN_PIN 13

// Global variables

// Pattern to detect
const int gTargetPattern[3] = {5, 1, 2};

// Pattern to search
const int gSampleData[10] = {7, 2, 0, 5, 5, 5, 0, 2, 1, 2};

// Number of pattern matches
int gOccurrences = 0;

void setup() {
  // Automatically determine the length of the gTargetPattern and gSampleData.
  size_t sampleLen = sizeof(gSampleData) / sizeof(gSampleData[0]);
  size_t patLen  = sizeof(gTargetPattern) / sizeof(gTargetPattern[0]); // should be 3

  // Initialize the serial (UART) terminal at 9600 baud.
  Serial.begin(9600);

  // Declare the output pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Print a fresh line to the terminal.
  Serial.println();

  if (sampleLen >= patLen)
  {
    // Implement a 3-element sliding window to determine if a pattern exists.
    for(unsigned int i = 0; i <= sampleLen - patLen; i++)
    {
      if (gSampleData[i]     == gTargetPattern[0] &&
          gSampleData[i + 1] == gTargetPattern[1] &&
          gSampleData[i + 2] == gTargetPattern[2])
      {
        // Increment occurrences if a pattern is detected.
        gOccurrences++;
      }
      
      if(gOccurrences > 0){
        digitalWrite(GREEN_PIN, HIGH);
        Serial.println("Green LED On");
      }
    }
  }
    
  if(gOccurrences == 0){
    digitalWrite(RED_PIN, HIGH);
    Serial.println("Red LED on");
      
  }
  // Delay the turn off of the LEDs
  delay(3000);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  Serial.println("All LEDs off");

}

void loop() {
  // put your main code here, to run repeatedly:

}
