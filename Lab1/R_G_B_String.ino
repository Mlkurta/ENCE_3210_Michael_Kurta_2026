#define ARRAY_SIZE 14

// Define pins as LED pins (PWM capable ones as default for brightness control if desired)
#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9

// Enter your desired word in curly brackets, and update ARRAY_SIZE macro -> number of characters + 1 (for '\0')
char gMyArray[ARRAY_SIZE] = {"biogeographer"};

// Initialize global struct for color counts
struct colorCount{
  uint8_t RED = 0;
  uint8_t GREEN = 0;
  uint8_t BLUE = 0;
};

struct colorCount gC;

void foundRed(){
  // Increment counter
  gC.RED += 1;
  // Print color / count
  Serial.print("RED \tCount: ");
  Serial.println(gC.RED);
  // Turn on Red LED
  digitalWrite(RED_PIN, HIGH);
  // Delay 0.5 sec
  delay(500);
  // Turn off Red LED
  digitalWrite(RED_PIN, LOW);

}

void foundGreen(){
  // Increment counter
  gC.GREEN += 1;
  // Print color / count
  Serial.print("GREEN \tCount: ");
  Serial.println(gC.GREEN);
  // Turn on Green LED
  digitalWrite(GREEN_PIN, HIGH);
  // Delay 0.5 sec
  delay(500);
  // Turn off Green LED 
  digitalWrite(GREEN_PIN, LOW);

}

void foundBlue(){
  // Increment counter
  gC.BLUE += 1;
  // Print color / count
  Serial.print("BLUE \tCount: ");
  Serial.println(gC.BLUE);
  // Turn on Blue LED
  digitalWrite(BLUE_PIN, HIGH);
  // Delay 0.5 sec
  delay(500);
  // Turn off Blue LED
  digitalWrite(BLUE_PIN, LOW);

}

void setup() {
  // put your setup code here, to run once:

  // Initialize the serial (UART) terminal at 9600 baud.
  Serial.begin(9600);

  // Declare the output pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize the index variable.
  int i;
  // Print a fresh line to the terminal.
  Serial.println();

  // Loop through char array for key letters (r,R,g,G,b,B) and call the appropriate function.
  for(i = 0; i < ARRAY_SIZE - 1; i++){
    
    if((gMyArray[i] == 'r') || (gMyArray[i] == 'R')){
      foundRed();

    }else if ((gMyArray[i] == 'g') || (gMyArray[i] == 'G')){
      foundGreen();

    }else if ((gMyArray[i] == 'b') || (gMyArray[i] == 'B')){
      foundBlue();

    }
  } 

}

void loop() {
  // put your main code here, to run repeatedly:

}
