#include <stdio.h>
#include <math.h>


// Global variables
struct s_Quadratic
{
    float x1;
    float x2;
};


struct s_Quadratic quadratic(int a, int b, int c){
    
    struct s_Quadratic x;
    
    float w = sqrt(b * b - 4 * a * c);
    
    if(w >= 0){
        
        x.x1 = (-b + w) / (2 * a);
        x.x2 = (-b - w) / (2 * a);
        
    }else{
        
        x.x1 = 0;
        x.x2 = 0;
        printf("Complex Roots\n");
    }
    
    
    return x;
    
}

int main()
{   

    struct s_Quadratic y;
    
    y = quadratic(1, -4, 4);
    
    printf("Result: %.2f, %.2f", y.x1, y.x2);

    return 0;
}