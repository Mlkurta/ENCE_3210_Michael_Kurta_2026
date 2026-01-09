#include <stdio.h>

#define ARRAY_SIZE 51

// Global variables

int gMyArray[ARRAY_SIZE] = {0};

int gMax;
int g2Max;


int main()
{   

    for(int i = 0; i < ARRAY_SIZE; i++){
        gMyArray[i] = 50 - i;
    }

    for(int i = 0; i < ARRAY_SIZE - 1; i++){
        if(gMyArray[i] > gMax){
          g2Max = gMax;
          gMax = gMyArray[i];
    
        }else if (gMyArray[i] > g2Max){
          g2Max = gMyArray[i];
        }
    }
    
    gMyArray[50] = g2Max;
    
    for(int i = 0; i < ARRAY_SIZE - 1; i++){
        
        printf("index: (%d) = %d\n", i, gMyArray[i]);
    }
    
        printf("\n2nd maximum: %d", g2Max);

    return 0;

}