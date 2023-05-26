# JeepDash
Auxiliary Gauges Instrument Panel for SUVs (Jeep Wrangler JL)

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
- Boards
  - [Makerfabs ESP32S3 Parallel TFT with Touch 4.0"](https://www.makerfabs.com/esp32-s3-parallel-tft-with-touch-4-inch.html "Product Link")
  - [Seed Studio CANBed Dual Dev Kit V1.1](https://www.seeedstudio.com/CANBed-DUAL-RP2040-based-Arduino-CAN-Bus-dev-board-2-independent-CAN2-0-CAN-FD-p-5377.html "Product Link")

- Connectors
  - [CAN Bus Connector (green)](https://www.mouser.com/ProductDetail/TE-Connectivity-AMP/5-2138650-1?qs=N0TJGnUfxCD1oGn85uoFLQ%3D%3D&countrycode=US&currencycode=USD)
  - [CAN Bus Connector (white)](https://www.mouser.com/ProductDetail/TE-Connectivity/2-2138650-1?qs=N0TJGnUfxCBU3xsQ5QFkFg%3D%3D&countrycode=US&currencycode=USD)
  - [CAN Bus Connector (terminal-female)](https://www.mouser.com/ProductDetail/TE-Connectivity-AMP/5-963715-6?qs=JRGdcu81duJRHENoNduZiA%3D%3D&countrycode=US&currencycode=USD)

## Status
- First set of instrument gauges with sample animation on ESP32S3 dev kit
- Initial CANBed test code (proven concept, but no yet in sample code)
  - receive CAN bus data from Raspberry PI 3B+ with CAN Bus hat
  - forward data via serial UART to ESP32S3

## Final Features 
- Accessory Gauges available in Jeep's "Off-Road Pages" (done)
- Gauges for pitch and roll (in progress)
- Compass rose (tbd. compass heading information / might need extra sensor) (in progress)
- Tire pressure and rotation (in progress)
- Extra screens accessible via swiping for 
  - Transmission state (Hi/Lo, Lockers)
  - Tire slip information
  - Aux switch information (pot. with interactions)
  - ... more tbd.

## Useful Links

- [Image to Hex Conversion (better for RGB 565)](https://www.digole.com/tools/PicturetoC_Hex_converter.php)
- [Image to Hex Conversion (better for RGB 8888)](https://lvgl.io/tools/imageconverter) 
