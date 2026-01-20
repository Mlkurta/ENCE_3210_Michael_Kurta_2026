# two_buttons.ino

This exercise uses button presses to trigger interrupt service routines (ISRs). Each ISR sets a flag for the main loop to check for.
When the code retuns to the main loop, it checks which flags are active and the determines the difference between the number of presses of each button. Then the results are printed.
