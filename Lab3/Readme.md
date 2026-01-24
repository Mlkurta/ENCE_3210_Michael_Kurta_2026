# Lab3_tasks.ino

This project has a number of requirements:

<img width="600" height="633" alt="Screenshot 2026-01-24 151432" src="https://github.com/user-attachments/assets/d7c94e81-ac4e-4f5b-b09f-8a5a312d74e1" />

## Thought process

1. The determination of timers (labelled 1 and 2) automatically means using timer interrupts. This means using volatile flags to change in the interrupts and then checking their state / resetting if necessary in main().

2. Blinking a green LED once every second would be easily handled with a 1/2 second timer interrupt to toggle the LED.

3. Since Task 2 will be executed 10x a second, no button debouncing is really required.

4. Since the main tasks execution required Task 1 to increment a number, make the number a decently high unsigned value (16 bit +), and then in main(), for the main tasks, use a modulo to trigger the main tasks when counter % value == 0.

5. Have a message bank declared in a 2d char array to print individual lines. Obfuscate the messages externally and paste them into the array, then use an XOR-based decoder (xor_encoder.py, see below) to decode the messages, one at a time into a buffer. Then print the buffer.

6. A random value will be generated to select which message to use. Activate the ADC and use analogRead() to produce a pseudo-random number as a seed for random values, i.e. randomSeed().

7. Using Timer 1, it's maximum output compare counter (OCR1A) value is that of a 16-bit unsigned integer: 65,535. I was lazy and already had a sketch with Timer1 prepared for 1 second with a counter value of 62,500; so I just had to divide it by two. But more formally, this is how it fits.

   $T_{timer1} = \frac{256}{16 MHz} = 16 \mu s$

   We take our desired Interrupt interval time (0.5s) and figure out what we need to count to:

   $\frac{0.5s}{16 \mu s} - 1 = 31249$

9. Since the maximum prescalar value for Timer 2 (TCCR2B) is 1024, and the highest the Timer 2 output compare register counter (OCR2A) can be set to is 255, then a task rate of once every .1 second cannot be achieved unless we use another volatile global counter variable.

   $T_{timer2} = \frac{1024}{16 MHz} = 64 \mu s$

   For ease of calculation, we can start and see if we can do 0.01 seconds using a maximum count setting of 255:

   $64 \mu s * (255 + 1) =  0.0163 s > 0.01s$

   We can indeed, so now we figure out how many counts we need to set OCR2A to to get closest to 0.01s.

   $\frac{0.01s}{64 \mu s} - 1 = 155.25$......we'll call it $155$.

   Remember to account for an extra count to reset the counter. So this is our setting: 155. Just to confirm:

   $(155 + 1) * 64 \mu s = 9.98 ms$

## Block Diagram

<img width="600" height="633" alt="IMG_0427" src="https://github.com/user-attachments/assets/3bb0254c-ef0a-440b-9fa0-0ca6b319ac05" />

## Operation

![image0](https://github.com/user-attachments/assets/dfb0beef-5153-4bd9-953f-9b7b3a2baddc)

## xor_encoder.py

Open this file in any Python IDE, paste your desired message string for the variable s, then run. Copy + paste your new scrambled message.

<img width="1200" height="413" alt="Screenshot 2026-01-24 154445" src="https://github.com/user-attachments/assets/33d929df-0c8d-4bc0-ac0a-51988a2dbe34" />
