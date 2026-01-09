#define ARRAY_SIZE 14

char gMyArray[ARRAY_SIZE] = {"biogeographer"};

struct colorCount{
  uint8_t RED = 0;
  uint8_t GREEN = 0;
  uint8_t BLUE = 0;
};

struct colorCount gC;

void foundRed(){
  gC.RED += 1;
  Serial.print("RED \tCount: ");
  Serial.println(gC.RED);
  // Turn on LED pin
  delay(500);
  // Turn off LED pin

}

void foundGreen(){
  gC.GREEN += 1;
  Serial.print("GREEN \tCount: ");
  Serial.println(gC.GREEN);
  // Turn on LED pin
  delay(500);
  // Turn off LED pin

}

void foundBlue(){
  gC.BLUE += 1;
  Serial.print("BLUE \tCount: ");
  Serial.println(gC.BLUE);
  // Turn on LED pin
  delay(500);
  // Turn off LED pin

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  int i;
  Serial.println();
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