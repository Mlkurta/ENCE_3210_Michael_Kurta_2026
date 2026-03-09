# Balloon Sat High Altitude Data Collection Platform

This is a repository for my High Altitude Balloon Sat cdata collection platform.

## Concept

To ideally be able to collect humidity, pressure, acceleration data, and exterior and interior temperature using an Arduino Uno platform + a custom shield. Data will be recorded on a separate memory module that uses an SD card. 
Parts must be U.S. sourced The module will be created and placed inside an impact resistant container. This container will contain all of the electronics for recording data, and will be attached to a baloon that will reach many kilometers up into the atmosphere, and record data. The balloon will eventually pop, and the sensors will fall to the ground for later collection.

## Bill of Materials

These are parts I chose that are either identical to (or the best replication of) the original guidelines directed by the NASA / CU Boulder / University of Denver partnership. 

1x Arduino Uno

1x 9V battery

1x 9V battery to Arduino Barrel Jack

1x PCB to function as a shield for Arduino

1x Sparkfun OpenLog module (UART)

1x Honeywell HH-4030 Humididy Sensor Module (No longer in production)

1x Adafruit ADXL 335 Accelerometer Module

1x Sparkfun Qwiic Micropressure Sensor

2x Analog Devices TMP36 Temperature Sensors

2x Blue 5mm LEDs

1x Orange 5mm LED

1x Yellow 5mm LED

1x Green 5mm LED

1x Red 5mm LED

2x 8-Pin stackable plug headers

2x 6-Pin stackable plug headers

2x DIP socket halves

2x 6-Pin socket headers

1x 3-Pin socket header

2x 2-Pin plug breakaway headers

1x 3-Pin locking headers

1x 6-Pin breakaway header

1x 3-Pin plug breakaway header

## Block Diagram

<img width="601" height="1113" alt="Balloon_BDV2" src="https://github.com/user-attachments/assets/1c3b4549-107a-4685-a135-c4791d4c77ab" />

## Weight and Power

The estimated power consumption is 496 mW, with an estimated mass of ~124g. This does not include the foam package itself.

<img width="601" height="609" alt="Screenshot 2026-03-09 121051" src="https://github.com/user-attachments/assets/b253790d-4676-45ae-9429-c65f5249ca4f" />

## Feasibility

The project is broadly feasible, with the main exception that a US-sourced Humidity sensor is no longer available. If having a humidity sensor is not critical to the functionality of the device, building the Balloon Sat with components is possible, for generally under $147. The PCB can be sourced from US based Osh Park for $5 per square inch; which is around ~$30 when using a shield similarly sized to an Arduino Uno. The downside is you must allow 12-21 calendar days for the order. Small components not necessarily critical to the functioning of the Balloon Sat device may be difficult to source from US providers: such as the various colored 5mm LEDs. Other US sourced LEDs may be found in different varieties at an increased price.










