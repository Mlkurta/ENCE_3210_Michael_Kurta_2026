#include <stdio.h>

#define ARRAY_SIZE 512

// Global variables
struct s_myStruct
{
    unsigned long int myArray[ARRAY_SIZE];
};

// Function which writes to an array of size ARRAY_SIZE, the value 2 * i^2
struct s_myStruct twiceSquare(void){
    
    struct s_myStruct x = {0};
    
    for(int i = 0; i < ARRAY_SIZE; i++){
        x.myArray[i] = 2UL * (unsigned long)i * (unsigned long)i;
    }
    
    return x;
    
}

int main()
{   

    struct s_myStruct y = twiceSquare();
    
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("2 * %d^2 = %lu\n", i, y.myArray[i]);
    }

    return 0;

}