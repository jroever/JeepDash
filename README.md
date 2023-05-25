# JeepDash
Auxiliary Car Instrument Panel for SUVs (Jeep Wrangler JL)

:warning: This Project is work in progress! 

## Overview
Auxiliary Instrument Panel to show car data gained via access to CAN Bus.
The project is targeting a 2020 Jeep Wrangler JLUR, but it should be easily adaptable to other car models as long as information about CAN bus protocal is available.

![alt text](https://github.com/jroever/JeepDash/blob/main/JeepDash480.jpg?raw=true)

Two controller boards are used (see below). 
The first board is used for main display and user interaction.
The second board is responsible for gathering the data from the two CAN busses that are used on the Jeep.
Communication between the two boards is done via simple serial (UART) communication.

## Hardware
- Makerfabs ESP32S3 Parallel TFT with Touch 4.0"
- Seed Studio CANBed Dual Dev Kit V1.1

## Status
- First set of instrument gauges with sample animation on ESP32S3 dev kit
- Initial CANBed test code
  - receive CAN bus data from Raspberry PI 3B+ with CAN Bus hat
  - forward data via serial UART to ESP32S3

## Immediate Goals
- add gauges for pitch and roll
- add compass rose (tbd. compass heasing information / might need extra sensor)

## Further Goals
- add extra screens accessible via swiping for 
  - Tire pressure and rotation
  - Transmission state (Hi/Lo, Lockers)
  - Tire slip information
  - Aux switch information (pot. with interactions)
  - more tbd.
