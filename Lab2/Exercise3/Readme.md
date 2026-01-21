# Simple_calculator_interrupt.ino

This prorgram is identical to one used last week. There are 3 arrays with a length of 10: The first two arrays have values filled in them, while the third is initialized as all zeroes. 

When button 1 is pressed once, then button 2 is pressed, the third array will be filled, element by element by adding the two arrays together. Then the contents of the third array are printed.

When button 1 is pressed twice, then button 2 is pressed, the third array will be filled, element by element by subtracting array 2 from array 1. Then the contents of the third array are printed.

When button 1 is pressed three times, then button 2 is pressed, the third array will be filled, element by element by multipying the two arrays together. Then the contents of the third array are printed.

The main difference between this program and last week's is the use of interrupts.

![simple_calc_int](https://github.com/user-attachments/assets/d03e9cf4-3bd6-4eb5-bfdf-6b1863001e90)
