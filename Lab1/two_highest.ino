#define ARRAY_SIZE 51  // Array size + next memory location for results.

// Global variables

// Initialize a zero array of size = ARRAY_SIZE.
int gMyArray[ARRAY_SIZE] = {0};

// Initialized integers to store the max and second-max numbers found.
int gMax;
int g2Max;

void setup() {
  // Initialize serial (UART) Terminal at 9600 baud.
  Serial.begin(9600);
  // Initialize i as index.
  int i;

  for(i = 0; i < ARRAY_SIZE - 1; i++){
    gMyArray[i] = 50 - i;
  }
    
  // Loop through the array
  for(int i = 0; i < ARRAY_SIZE - 1; i++){
    if(gMyArray[i] > gMax){             // If the current value is greater than the highest,
      g2Max = gMax;                     // save that number as the new second-highest.
      gMax = gMyArray[i];               // Then save the highest number variable as the current number

    }else if (gMyArray[i] > g2Max){     // Otherwise if the current number is ONLY larger than the second highest,
      g2Max = gMyArray[i];              // save the second highest as the current number
    }
  }

  // Save the second highest value into the next memory location (last array element: 50 + 1).
  gMyArray[50] = g2Max;

  // Start a fresh line in the terminal.
  Serial.println();

  // Loop through the elements and print the values, and denote if it's the last element (second highest value).
  for(int i = 0; i < ARRAY_SIZE; i++){

    if(i == 50){
      Serial.print("2nd Max----> ");
    }else{
      Serial.print("Index: ");
      Serial.print(i);
    }

    Serial.print("\t Value: ");
    Serial.println(gMyArray[i]);

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
