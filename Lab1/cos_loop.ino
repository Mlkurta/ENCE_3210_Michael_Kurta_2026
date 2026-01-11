int angleDeg[361];   // 0–360 degrees

void setup() {
  // Intialize UART terminal at 9600 baud
  Serial.begin(9600);

  // fill array
  for (int i = 0; i <= 360; i++) {
    angleDeg[i] = i;
  }

  // Start with a fresh line
  Serial.println();

  // Compute & print cosine for each angle
  for (int i = 0; i <= 360; i++) {

    // Std arduino library takes angle argument in radians, so convert the degrees to radians.
    float radians = angleDeg[i] * (PI / 180.0);
    // Calculate the cosine value of the radian value.
    float value = cos(radians);
    
    // Print the angle in degrees and also the cosine value.
    Serial.print("cos(");
    Serial.print(angleDeg[i]);
    Serial.print(") = ");
    Serial.println(value, 6);
  }
}

void loop() {
}