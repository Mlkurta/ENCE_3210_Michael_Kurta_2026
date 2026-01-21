# two_buttons.ino

This exercise uses button presses to trigger interrupt service routines (ISRs). Each ISR sets a flag for the main loop to check for.

When the code retuns to the main loop, it checks which flags are active and the determines the difference between the number of presses of each button. Then the results are printed.

![two_buttons](https://github.com/user-attachments/assets/e04297fd-4728-4dfa-b6e6-6599691d72c7)
