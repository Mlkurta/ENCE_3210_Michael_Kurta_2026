#include <stdio.h>

#define ARRAY_SIZE 51

// Global variables

// Note that this is a straight C program; it's not formatted for use with Arduino, but can be easily adapted to do so.

// initialize a zero array of size = ARRAY_SIZE
int gMyArray[ARRAY_SIZE] = {0};

// initialized integers to store the max and second-max numbers found
int gMax;
int g2Max;


int main()
{   
    // Fill the array with known maximum and second maximum numbers. 
    for(int i = 0; i < ARRAY_SIZE; i++){
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
    
    gMyArray[50] = g2Max;
    
    for(int i = 0; i < ARRAY_SIZE - 1; i++){
        
        printf("index: (%d) = %d\n", i, gMyArray[i]);
    }
    
        printf("\n2nd maximum: %d", g2Max);

    return 0;


}
