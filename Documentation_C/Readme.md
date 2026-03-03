
# Introduction


## Design Stage

The inital idea was to have a shield to include a Digital Analog Converter (DAC) for an Arduino Uno. Also added were an IMU, 3.5mm analog input and outputs, and a small 128x32 pixel OLED screen.  Since there was some extra digital and analog pins left over, buttons and additional analog inputs with potentiometers were added.

The intent for the DAC was to have 10 bit precision, since the onboard ADC is also 10 bit. The DAC was made using an R-2R architecture. This involves a chain of resisitors and a number of digital inputs, which creates cascading bit precision. The good thing about using an R-2 DAC with an Arduino is it is relatively fast. Rather than using serial communication, a DAC update can be accomplished with two instructions, since all 10  bits span across the PORT B and PORT D registers. 

![IMG_0489](https://github.com/user-attachments/assets/88fbef53-2d76-4fcb-9795-29947de8017c)


## Prototyping Stage

The after the DAC was whiteboard designed, a prototype was made on a breadboard:

![Daccircuit](https://github.com/user-attachments/assets/9224c89c-384b-4daa-b774-bd074601dfe8)

The following oscilloscope view is of a sine, square and triangle waveform outputs (Didn't work out so well initially).

![10bitdac](https://github.com/user-attachments/assets/449c8734-b969-48ca-836b-4b4f43883fb0)

## PCB Design

The schematic was designed in KiCad:

<img width="901" height="1113" alt="image" src="https://github.com/user-attachments/assets/277369d4-21be-4099-ad3c-0956b484e221" />

The layout made and traces and silkscreen prototyped in the PCB viewer:

<img width="1592" height="1047" alt="Layout2" src="https://github.com/user-attachments/assets/850f7d81-3066-4d7f-abc3-cf4ace6aa785" />

3d Views of the board at different angles:

<img width="919" height="1186" alt="PCB_Front" src="https://github.com/user-attachments/assets/861dee64-86b8-4a32-bd24-d0cd0fcaf474" />

<img width="938" height="1195" alt="PCB_Back" src="https://github.com/user-attachments/assets/0d4aafa1-c87c-4694-be4b-3134b440fed0" />

<img width="1377" height="1137" alt="PCB_3D" src="https://github.com/user-attachments/assets/1bfb54ef-fc15-48f2-902a-ec0267f33b9a" />

## Assembled Shield + Arduino

![IMG_7919](https://github.com/user-attachments/assets/5181b266-4063-4b5b-ab40-e01f150bc6fc)

## Testing

Fan controller

![VideoToGif_GIF (1)](https://github.com/user-attachments/assets/d5412512-04fa-422c-b3dd-5fdfc5492d54)


FSK Telemetry Modem

![FSK_Telem](https://github.com/user-attachments/assets/e6de6330-77e2-4ded-9deb-94e5e24202a9)




