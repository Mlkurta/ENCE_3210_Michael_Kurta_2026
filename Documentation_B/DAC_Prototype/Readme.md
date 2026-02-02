# 10-Bit DAC

## Idea

This mini-project is intended to be a prototype of a PCB Digital to Analog Converter (DAC) shield which will be built for an Arduino Uno.

## Falstad Simulation

<img width="600" height="569" alt="Screenshot 2026-01-28 092443" src="https://github.com/user-attachments/assets/3f2724be-7ce1-4df0-b067-a45682d97f64" /> 

This simulation is based on the circuit built below: It outputs 0 - 4.13V, based on the bit value input into the DAC. It utilizes an R-2R ladder to cascade each bit's contribution to the op amp's input proportionally. 

## Breadboard Circuit

Assembled circuit:

<img width="480" height="569" alt="Screenshot 2026-01-28 092443" src="https://github.com/user-attachments/assets/809ec3c8-de50-4fee-9f00-2a28331a81e2" />

It uses the TL-072 op-amp. This op amp is "ok" when using a single supply source (0 - 5V), while doesn't have the best single-rail characteristics, is mostly meant for prototyping, not the final product.  

## Output Waveforms

The waveform outputs both a "Sine" and "Triangle" wave, depending whether or not button 1 or button 2 was last pressed. I could've used one button to toggle, but the intent was to be more realistic to
the layout of the actual DAC shield having two buttons.
<img width="480" height="569" alt="Screenshot 2026-01-28 092443" src="https://github.com/user-attachments/assets/8f972c7f-83ef-4a1c-b52a-ca1018766921" />


