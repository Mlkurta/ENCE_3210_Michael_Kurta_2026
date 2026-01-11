#include <math.h>

// Global variables

// Struct for quadratic roots
struct s_Quadratic
{
    float x1;
    float x2;
};

// Quadratic function, returns struct of roots
struct s_Quadratic quadratic(int a, int b, int c){
    
  struct s_Quadratic x;
  
  float w = sqrt(b * b - 4 * a * c);
  
  // If w is greater than or equal to zero, then the roots are real.
  if(w >= 0){
      
      // assign the + and - elements to each root variable
      x.x1 = (-b + w) / (2 * a);
      x.x2 = (-b - w) / (2 * a);
      
  }else{
      
      // Otherwise, set the root variables to zero and indicate complex roots.
      x.x1 = 0;
      x.x2 = 0;
      Serial.println();
      Serial.println("Complex Roots");
  }
  
  return x;
    
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Initialize struct
  struct s_Quadratic y;

  // *Enter your coefficients here
  y = quadratic(1, -8, 16);
  Serial.println();           // Start a new line

  // print results, change # in .#f for number of decimal place precision
  Serial.print("Result: r1 = ");
  Serial.print(y.x1);
  Serial.print("\t r2 = ");   // Tab for same line spacing
  Serial.println(y.x2);

}

void loop() {
  // put your main code here, to run repeatedly:

}