# Led_Sequence_interrupts.ino

This program uses a button interrupt as a modification of last week's lab "LED_sequence.ino".  Only instead of using a delay in a loop as a debouncer, we first determin if an interrupt (button press) happened within the main loop. If a button press is detected, then the current time in milliseconds "millis()" is saved to an unsigned long variable. Then we check if the difference between the current time and the last button press time is greater than our established debounce time, then we continue as if it were a valid button press. 

Then we iterate through the sequence with one big switch / case statement.  If a button press is detected during the animation, then  the button sequence turns off and then returns to baseline. 
