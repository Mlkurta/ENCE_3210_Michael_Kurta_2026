
# Introduction

The purpose of this shield design was to provide some additional features and capabilities to an Arduino Uno. It provides the ability to do simple Digital Signal Processing (DSP) tasks, utilizing the built in Analog to Digital Converters (ADC), and an added 10-bit Digital to Analog Converter (DAC). Other useful features were added, such as a 128x32 OLED screen to serve as a graphic user interface, and an Inertial Measurement Unit (IMU) for acceleration and gyro monitoring. 

## Design Stage

The inital idea was to have a shield to include a DAC for an Arduino Uno. Also added were an IMU, 3.5mm analog input and outputs, and a small 128x32 pixel OLED screen.  Since there was some extra digital and analog pins left over, buttons and additional analog inputs with potentiometers were added.

The intent for the DAC was to have 10 bit precision, since the onboard ADC is also 10 bit. The DAC was made using an R-2R architecture. This involves a chain of resisitors and a number of digital inputs, which creates cascading bit precision. The good thing about using an R-2 DAC with an Arduino is it is relatively fast. Rather than using serial communication, a DAC update can be accomplished with two instructions, since all 10  bits span across the PORT B and PORT D registers. 

The IMU is an MPU 6050, which transmits both acceleration and gyroscopic data for x, y, and z over I2C. This I2C bus is shared with the 128x32 OLED screen.  Additionally, there is a MCP 6002 Op Amp, which has decent rail to rail output voltage as well as single rail performance. Since the input voltage is only meant for simple 5V from USB (no dual rail, negative voltage), this Op amp is a good choice.  There is both a potentiometer to control the op amp DC bias, as well as a jumper to optionally connect the non-inverting input to ground. Two of the analog inputs (A0 and A1) are individually connected to potentiometers, which function as voltage dividers, providing between 0V and 5V DC. Lastly, Arduino Uno digital inputs D2 and D3 are connected to GND via 100k ohm pulldown resistors. Two pushbutton switches, when pressed, pull each individual digital input pins high.

<img width="601" height="1113" alt="IMG_0489" src="https://github.com/user-attachments/assets/88fbef53-2d76-4fcb-9795-29947de8017c" />


## Prototyping Stage

The after the DAC was whiteboard designed, a prototype was made on a breadboard:

<img width="601" height="1113" alt="Daccircuit" src="https://github.com/user-attachments/assets/9224c89c-384b-4daa-b774-bd074601dfe8" />

The following oscilloscope view is of a sine, square and triangle waveform outputs (Didn't work out so well initially).

![10bitdac](https://github.com/user-attachments/assets/449c8734-b969-48ca-836b-4b4f43883fb0)

## PCB Design

The schematic was designed in KiCad:

<img width="900" height="1113" alt="image" src="https://github.com/user-attachments/assets/277369d4-21be-4099-ad3c-0956b484e221" />

The layout made and traces and silkscreen prototyped in the PCB viewer:

<img width="700" height="1047" alt="Layout2" src="https://github.com/user-attachments/assets/850f7d81-3066-4d7f-abc3-cf4ace6aa785" />

3d Views of the board at different angles:

<img width="700" height="1186" alt="PCB_Front" src="https://github.com/user-attachments/assets/861dee64-86b8-4a32-bd24-d0cd0fcaf474" />

<img width="700" height="1195" alt="PCB_Back" src="https://github.com/user-attachments/assets/0d4aafa1-c87c-4694-be4b-3134b440fed0" />

<img width="700" height="1137" alt="PCB_3D" src="https://github.com/user-attachments/assets/1bfb54ef-fc15-48f2-902a-ec0267f33b9a" />

## Assemble Stage

Delivered PCB board (front and back)

<img width="700" height="1137" alt="IMG_7939" src="https://github.com/user-attachments/assets/1cd02c37-ae7d-4b94-b359-29e8d9c73276" />

<img width="700" height="1137" alt="IMG_7940" src="https://github.com/user-attachments/assets/014a4e83-e018-48b1-a9ca-2c3839869104" />

Fully assembled with an MCP6002 operational amplifier:

<img width="700" height="1137" alt="IMG_7919" src="https://github.com/user-attachments/assets/5181b266-4063-4b5b-ab40-e01f150bc6fc" />

## Testing

Fan controller

The fan controller output several different PWM stages. The fan controller outputs a PWM frequency to control a motor. The PWM changes with temperature (simulated via onboard analog potentiometer), as well as having three different fan settings, each with a different multiplier to the PWM output. 

![VideoToGif_GIF (1)](https://github.com/user-attachments/assets/d5412512-04fa-422c-b3dd-5fdfc5492d54)


FSK Telemetry Modem

The Frequency Shift Keying (FSK) Modem made use of the Analog 3.5 mm jacks, the IMU, the screen, the DAC, etc. This project was designed as a proof of concept: That the Arduino Uno could:

1. Read accelerometer data via I2C.
2. Modulate the data for transmission
3. Output a digital modulation waveform using the DAC
4. Read incoming data via the ADC
5. Demodulate the waveform and error check
6. Output the received accelerometer data as a plot on the OLED screen via I2C

![FSK_Telem](https://github.com/user-attachments/assets/e6de6330-77e2-4ded-9deb-94e5e24202a9)


<img width="773" height="879" alt="Screenshot 2026-03-04 193335" src="https://github.com/user-attachments/assets/711a7940-3f8f-4646-aee7-503da18cf776" />




