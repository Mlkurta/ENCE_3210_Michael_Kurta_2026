# Lab 1 Projects

## twice_square.c
This program computes 2 time the square of numbers 0 to 511 and saves them into an array and prints the values. Since the highest value attained is 522,242, which is greater than
an unsigned 16 bit integer, we must declare a 32-bit integer (unsigned optional). But since a 32 bit integer occupies 4 bytes, and there are 512 of them to be initialized, that occupies
4 * 512 = 2048 bytes. When you add other SRAM requirements, that exceeds the available RAM on the device. Therefore, this was completed in a standard C compiler found here: https://www.onlinegdb.com/online_c_compiler#



## cos_loop.ino
This program fill an array with the cosine values from 0 to 360 degrees (361 entries). It then prints the contents of the loop. There is not much to note about this exercise, other than the fact that the arduino built-in cosine
functions require the values to be in radians. Therefore, the degrees must be converted to radians first. 

<img width="500" height="1219" alt="Screenshot 2026-01-12 133823" src="https://github.com/user-attachments/assets/70a0c908-8bf1-4499-92e6-326180500b0b" />

## two_highest.ino
This program will search for the second highest value in an array of 50 elements. It will then print the contents of the 50 elements and then print the second highest value in the array.

<img width="500" height="1205" alt="Screenshot 2026-01-12 134333" src="https://github.com/user-attachments/assets/e8c379e7-17ba-4f93-b124-c55fc1491435" />

## char_LEDs.ino
Problem: Write a C program to find the R, G, and B letters in an array. If the letters are detected, the red,
green, and blue colors LEDs will turn on, respectively. Your program should count the number of
occurrences of each letter in the array. The test word here is "biogeographer", so you'll see Blue, Green, Green, Red, Red.

![RGBString](https://github.com/user-attachments/assets/c28fab99-9c53-4777-b245-ff73a0d5b406)

## pattern_detect.ino
Problem: Write a C program to detect a specified pattern with three entries in an array. The pattern is saved in
another array. When the pattern is detected, the green color LED will turn on. If the pattern is not
detected, the red color LED will turn on at the end of the program. Your program should count the
number of occurrences of the pattern.

I used ChatGPT for suggestions on how to check for the pattern. It uses a loop that incorporates a sliding window to detect for the target pattern.
It also uses the serial terminal to indicate if/ when LEDs turn on or off.


![pattern_detect](https://github.com/user-attachments/assets/85d441bd-9290-48c0-824f-55e43e58fd17)

## LED_Sequence.ino
Problem: We would like to turn on and off the red, green, and blue LEDs in a sequence. Therefore, write a C
program with the following specifications:
a) When the button is pressed, turn on the red, green, and blue color LEDs with the following
order: R – RG – RGB – GB – B – RB
b) This procedure is repeated until the button is pressed again.


![LedSequence](https://github.com/user-attachments/assets/b1a52bbd-6eb5-43e3-8aac-be5697db6768)

## simple_calculator.ino
This sketch controls a program which is controlled by two buttons. There are three arrays: two input arrays and one output array. The program conducts add, subtract, and multiply operations
between array one and array two and writes the results to array 3. Which operation is conducted depends on user input. If the user presses the select button once, adding will be conducted. Two presses,
subtracting will be done. Three or more presses will conduct multiplication and print the results. THe user must press a second button after pressing the select button to execute. This will light either a red (add),
green (subtract) or both red and green (multiply) LEDs. The count is reset once the execute button is pressed. I used ChatGPT for ideas on how to debounce the buttons without having a large delay. 

![simple_calculator](https://github.com/user-attachments/assets/f0382f51-0901-46a8-8282-de3fe59e35b6)



