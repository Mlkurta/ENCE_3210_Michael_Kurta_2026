#define DEBOUNCE_TIME 100

const int RED_LED = 5;
const int GREEN_LED = 4;
const int BUTTON1_PIN = 2;
const int BUTTON2_PIN = 3;

volatile bool button1Pressed = false;
volatile bool button2Pressed = false;

int gButton1Presses = 0;
int gButton2Presses = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);

  // Configure interrupt vector
  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), isr_button1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), isr_button2, FALLING);
  Serial.println();

  //interrupts();
  Serial.println();
}
void loop() {
  if(button1Pressed){
    gButton1Presses += 1;
    delay(DEBOUNCE_TIME);
    button1Pressed = false;
    Serial.print("B1 Pressed; Abs(button1 presses - button2 presses): ");
    Serial.println(abs(gButton1Presses - gButton2Presses));
  }
  if(button2Pressed){
    gButton2Presses += 1;
    delay(DEBOUNCE_TIME);
    button2Pressed = false;
    Serial.print("B2 Pressed; Abs(button1 presses - button2 presses): ");
    Serial.println(abs(gButton1Presses - gButton2Presses));
  }

  if(gButton1Presses > gButton2Presses){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  
  }else if(gButton1Presses < gButton2Presses){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }else{
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }

  
}

// Interrupt service routine (ISR)
void isr_button1(){
  button1Pressed = true;
}

void isr_button2(){
  button2Pressed = true;
}