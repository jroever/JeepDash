/*----------------------------------------------------------------------------/
  JeepDash480 - Auxiliary Car Instrument Panel for SUVs (Jeep Wrangler JL)

Original Source:
 (https://github.com/jroever/JeepDash/)


Licence:
 [GnuGPL3](https://github.com/jroever/JeepDash/blob/main/LICENSE)

Author:
 [jroever](https://jroever.github.io/)

/----------------------------------------------------------------------------*/

#include "LGFX_ESP32S3_RGB_MakerfabsParallelTFTwithTouch40.h"
#include "ArcMeter.h"

/*#include "SPI.h"
#include "FS.h"

#define SD_SCK  12
#define SD_MISO 13
#define SD_MOSI 11
#define SD_CS   10*/

LGFX display;

static constexpr int LOOP_PERIOD = 16; // Display updates in ms

#include "Icons.h"

int value[5] = {0, 0, 0, 0, 0};
int delta[5] = {1, 1, 1, 1, 1};

uint32_t updateTime = 0; // time for next update
ArcMeter *meter[5];

void setup(void)
{
  display.init();
  display.fillScreen(TFT_BLACK);

  meter[0] = new ArcMeter(&display,"Coolant Temp","C","H",0+6,6); // Draw analogue meter
  meter[1] = new ArcMeter(&display,"Oil Temp","C","H",160+6,6); // Draw analogue meter
  meter[2] = new ArcMeter(&display,"Battery Voltage","L","H",320+6,6); // Draw analogue meter
  meter[3] = new ArcMeter(&display,"Trans Temp","C","H",80+6,160+6); // Draw analogue meter
  meter[4] = new ArcMeter(&display,"Oil Pressure","L","H",240+6,160+6); // Draw analogue meter
  meter[2]->setDigits(1);

  display.endWrite();

  //  void pushGrayscaleImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *image, color_depth_t depth, uint32_t fg_rgb888, uint32_t bg_rgb888);
  int gray18 = ArcMeter::rgb565_gray(21);
  display.pushGrayscaleImage(80-16,91,32,32,icon_coolant_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(240-16,90,32,32,icon_oiltemp_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(400-16,90,32,32,icon_battery_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(160-16,251,32,32,icon_transmission_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(320-16,250,32,32,icon_oilpress_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  updateTime = millis(); // Next update time 
}

void loop(void)
{
  auto msec = millis();

  if (updateTime <= msec) {

    if (!display.displayBusy()) {

      updateTime = msec + LOOP_PERIOD;
      display.startWrite();

      for(int i=0;i<5;i++) {

        if ((i==0) or ((value[0]&((1<<i)-1))==0)) {
          value[i]+=delta[i];

          if (value[i]>=199) delta[i] = -1;
          else if (value[i]<=0) delta[i] = 1;
          
          meter[i]->updateValue(value[i]);
        }
      }

      display.endWrite();
    }
  }
}
