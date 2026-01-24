// Pin definitions
#define RED_PIN 5
#define GREEN_PIN 4
#define BUTTON_PIN 3

#define CIPHER_KEY 0x5A                         // :-o

#define TASK1_MAIN_TASK_RATIO 3                 // Adjustable ratio between Task1 triggers to Main Task activations

#define MAX_LEN 59                              // Maximum message length
#define NUM_STRINGS 9                           // Number of strings

#define TIMER1_COMPARE_500MS 31250              // 16 MHz / 256 prescalar = T = 16 us * 31250 = .5s
#define TIMER2_COMPARE_10MS 155                 // 16 MHz / 1024 prescalar = T = 64 us * 155 = ~.01 s

volatile bool gISRFlagTask1 = false;            // Task 1 flag
volatile bool gISRFlagTask2 = false;            // Task 2 flag

// Timer 2 counter to track counts since it cannot fire every 100ms
volatile uint8_t gT2Count = 0;

// Universal timer variable
uint32_t gStart = 0;

// Task 1 counter initalized at 0
uint16_t gTask1Count = 0;

// bool to track green LED state
bool gGreenState = false;         

// :-P
char gMessages[NUM_STRINGS][MAX_LEN] = {
  "\x12\x3f\x36\x36\x35\x7a\x2d\x35\x28\x36\x3e\x74\x7a\x13\x7a\x28\x3f\x3d\x28\x3f\x2e\x7a\x34\x35\x2e\x32\x33\x34\x3d\x74\x00",
  "\x09\x2e\x33\x36\x36\x7a\x3b\x36\x33\x2c\x3f\x74\x00",
  "\x13\x2e\x7a\x2d\x35\x28\x31\x3f\x3e\x74\x7a\x1e\x35\x34\x7d\x2e\x7a\x2e\x35\x2f\x39\x32\x7a\x33\x2e\x74\x00",
  "\x12\x2f\x37\x3b\x34\x76\x7a\x13\x7a\x28\x3f\x2b\x2f\x33\x28\x3f\x7a\x37\x35\x28\x3f\x7a\x3e\x3f\x36\x3b\x23\x29\x74\x00",
  "\x08\x2f\x34\x34\x33\x34\x3d\x7a\x35\x34\x7a\x32\x35\x2a\x3f\x7a\x3b\x34\x3e\x7a\x6f\x0c\x74\x00",
  "\x06\x05\x72\x04\x05\x04\x73\x05\x75\x00",
  "\x1d\x3f\x2e\x7a\x29\x35\x37\x3f\x7a\x29\x36\x3f\x3f\x2a\x76\x7a\x0a\x28\x35\x3c\x7a\x17\x3b\x28\x2e\x33\x34\x29\x7b\x00",
  "\x15\x2c\x3f\x28\x3b\x34\x3b\x36\x23\x20\x33\x34\x3d\x7a\x3b\x2e\x7a\x6b\x6c\x17\x12\x20\x76\x7a\x36\x35\x35\x31\x33\x34\x3d\x7a\x34\x35\x28\x37\x3b\x36\x7a\x3f\x2c\x3f\x28\x23\x7a\x6b\x12\x20\x74\x00",
  "\x03\x35\x2f\x7a\x2a\x2f\x2e\x7a\x2e\x32\x3f\x7a\x7d\x33\x29\x37\x7d\x7a\x33\x34\x7a\x2e\x32\x33\x29\x7a\x33\x29\x7a\x3b\x36\x36\x7a\x30\x2f\x29\x2e\x7a\x3b\x7a\x3e\x3f\x3c\x3f\x34\x29\x3f\x7a\x37\x3f\x39\x32\x3b\x34\x33\x29\x37\x00"
};

char gDecoded[MAX_LEN];                         // Decoded message buffer

void setup() {
  Serial.begin(9600);                           // Initialize serial (UART) at 9600 baud

  pinMode(BUTTON_PIN, INPUT);                   // Set the pin to input.

  // Initialize the LED pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(A0, INPUT);

  // Generate a random random number seed from analog input
  randomSeed(analogRead(A0));

  // Disable interrupts while configuring timer interrupts
  noInterrupts();
  ////////////////////////////////////
  ////// Timer 1 configuration ///////
  ////////////////////////////////////
  TCCR1A = 0;                                   // Clear timer 1 registers
  TCCR1B = 0;                                   // ...for setup
  OCR1A = TIMER1_COMPARE_500MS;                 // Set output compare register counter value
  TCCR1B |= (1<<WGM12) | (1<<CS12);             // Counter compare Clear Timer Mode (CTC) | 256 prescalar
  TIMSK1 |= (1<<OCIE1A);                        // enable timer compare interrupt

  ////////////////////////////////////
  ////// Timer 2 configuration ///////
  ////////////////////////////////////
  TCCR2A = 0;                                   // Clear timer 2 registers
  TCCR2B = 0;                                   // ...for setup
  OCR2A = TIMER2_COMPARE_10MS;                  // Set output compare register counter value for 10ms (100ms not possible on Timer 2)
  TCCR2A |= (1 << WGM21);                       // Counter compare Clear Timer Mode (CTC)

  // Highest prescalar value in Timer 2 (1024) to minimuze interrupts
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);                      // Enable timer compare interrupt

  // Reenable interrupts
  interrupts();

  // Print a newline to the terminal 
  Serial.println();
}

void loop() {

  // ************** Task 1 **************
  if(gISRFlagTask1){
    gISRFlagTask1 = false;                      // Reset task 1 flag
    gGreenState = !gGreenState;                 // Toggle Green LED state
    digitalWrite(GREEN_PIN, gGreenState);       // Change Green LED
    if(gGreenState){                            // If the green LED just turned on...
      gTask1Count++;                            // Increment the Task 1 counter (1sec)
    }
  }

  // ************** Task 2 **************
  if(gISRFlagTask2){
    gISRFlagTask2 = false;                      // Reset task 1 flag
    if(digitalRead(BUTTON_PIN) == HIGH){        
      digitalWrite(RED_PIN, HIGH);
    }else{
      digitalWrite(RED_PIN, LOW);
    }
  }

  // ************** Main Task **************
  // Checks if the modulo of the task1 to main task ratio + 1 of the task1 counter is 0. 
  // Why + 1? because this will continue to execute printing messages until a second has elapsed, 
  // ...so we increment the counter immediately to only print one message.
  if(gTask1Count % (TASK1_MAIN_TASK_RATIO + 1) == 0){
    int i = random(NUM_STRINGS);                // Generate a random number (0 to NUM_STRINGS - 1)
    xorCipherTo(gDecoded, gMessages[i]);        // Decode message 
    Serial.println(gDecoded);                   // Print decoded message
    gTask1Count++;                              // Increment task counter to print only one message
  }
}

// Timer 1 ISR
ISR(TIMER1_COMPA_vect){
  gISRFlagTask1 = true;                         // Set task 1 flag
}

// Timer 2 ISR
ISR(TIMER2_COMPA_vect) {
  // Fires every ~10ms
  if (++gT2Count >= 10) {                       // Increment counter & check for overflow
    gT2Count = 0;                               // Reset counter
    gISRFlagTask2 = true;                       // Set task 2 flag
  }
}

// ;-(
char* xorCipherTo(char *dst, const char *src) {
  while (*src) {                                // While the source string has chars that aren't '\0'
    *dst++ = *src++ ^ CIPHER_KEY;               // Increment both source and destination characters and XOR src with the cipher key
  }
  *dst = '\0';                                  // Place a null terminator so the printer knows when to stop printing
  return dst;                                   // Return the decoded string
}


