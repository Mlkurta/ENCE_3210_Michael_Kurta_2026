#include <stdio.h>

#define ARRAY_SIZE 10

int myArray[ARRAY_SIZE] = {0};
int gSum = 0;
float gAverage = 0;


int main()
{   

    for(int i = 0; i < ARRAY_SIZE; i++){
        scanf("%d", &myArray[i]);
        gSum += myArray[i];
    }
    
    printf("\nResult:\n");
    
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("%d\n", myArray[i]);
    }
    
    gAverage = (float)gSum / (float)ARRAY_SIZE;
    printf("Sum: %d\t Average: %.2f", gSum, gAverage);

    return 0;
}

