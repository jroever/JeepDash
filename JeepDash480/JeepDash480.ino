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

static LGFX display;
static LGFX_Sprite sprite(&display);

static constexpr int LOOP_PERIOD = 32; // Display updates in ms

#include "Icons.h"

int value[5] = {0, 0, 0, 0, 0};
int delta[5] = {1, 1, 1, 1, 1};

uint32_t updateTime = 0; // time for next update
ArcMeter *meter[5];

void setup(void)
{
  display.init();
  display.fillScreen(TFT_BLACK);

  sprite.setColorDepth(16);
  sprite.createSprite(160,160);
  
  meter[0] = new ArcMeter(&display,"Coolant Temp","C","H",0+6,6); // Draw analogue meter
  meter[1] = new ArcMeter(&display,"Oil Temp","C","H",160+6,6); // Draw analogue meter
  meter[2] = new ArcMeter(&display,"Battery Voltage","L","H",320+6,6); // Draw analogue meter
  meter[3] = new ArcMeter(&display,"Trans Temp","C","H",6,320+6); // Draw analogue meter
  meter[4] = new ArcMeter(&display,"Oil Pressure","L","H",320+6,320+6); // Draw analogue meter
  meter[2]->setDigits(1);

  display.endWrite();

  //  void pushGrayscaleImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *image, color_depth_t depth, uint32_t fg_rgb888, uint32_t bg_rgb888);
  int gray18 = ArcMeter::rgb565_gray(21);
  display.pushGrayscaleImage(80-16,91,32,32,icon_coolant_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(240-16,90,32,32,icon_oiltemp_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(400-16,90,32,32,icon_battery_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(80-16,160+251,32,32,icon_transmission_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);
  display.pushGrayscaleImage(400-16,160+250,32,32,icon_oilpress_gray8,lgfx::grayscale_8bit,gray18,TFT_BLACK);

  //display.pushImage(16,320+16,128,128,(uint16_t*)image_jeep_side_rgb565);
  ArcMeter::drawArc(&display,6,160+6); // Draw analogue meter
  ArcMeter::drawArc(&display,320+6,160+6); // Draw analogue meter
  //ArcMeter::drawArc(&display,320+6,320+6); // Draw analogue meter

  display.setFont(&fonts::Font4);
  display.setTextColor(TFT_LIGHTGRAY, TFT_BKGRND);
  display.setTextDatum(textdatum_t::middle_center);
  display.drawNumber(34, 175, 190);
  display.drawNumber(34, 305, 190);
  display.drawNumber(34, 175, 274);
  display.drawNumber(34, 305, 274);
  display.pushImageRotateZoom(240,240,45,74,0.0,1.0,1.0,89,148,(uint16_t*)image_jeep_top_rgb565,(uint16_t) 0x0000); //float dst_x, float dst_y, float src_x, float src_y, float angle, float zoom_x, float zoom_y, int32_t w, int32_t h, const T* data)

  updateTime = millis(); // Next update time 
}

void loop(void)
{
  auto msec = millis();

  if (updateTime <= msec) {

    // we do the sprite manipulation outside the startWrite/endWrite section to no block the SPI for too long

    float angle3 = value[2]-100.0;

    // rotate compass scale (no alpha)
    sprite.pushImageRotateZoomAA(80,80,74,74,angle3,1.0,1.0,148,148,(uint16_t*)image_compass_rgb565); //float dst_x, float dst_y, float src_x, float src_y, float angle, float zoom_x, float zoom_y, int32_t w, int32_t h, const T* data)

    // overlay arrow (with alpha)
    sprite.pushImageRotateZoom(80,80,74,74,0.0,0.8,0.8,148,148,(uint16_t*)image_jeep_logo_rgb565,(uint16_t) 0x0000); 

    //sprite.fillRect(80, 0, 2, 30, TFT_DRKORANGE);

    while (display.displayBusy()) {}

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

    float angle1 = value[2]*0.5-50.0;
    float angle2 = value[1]*0.5-50.0;
    display.pushImageRotateZoom(80,240,64,64,angle1,0.9,0.9,128,128,(uint16_t*)image_jeep_side_rgb565,(uint16_t) 0x0000); //float dst_x, float dst_y, float src_x, float src_y, float angle, float zoom_x, float zoom_y, int32_t w, int32_t h, const T* data)
    display.pushImageRotateZoom(400,240,64,64,angle2,0.9,0.9,128,128,(uint16_t*)image_jeep_rear_rgb565,(uint16_t) 0x0000); //float dst_x, float dst_y, float src_x, float src_y, float angle, float zoom_x, float zoom_y, int32_t w, int32_t h, const T* data)

    sprite.pushSprite(&display,160,320);

    display.endWrite();

  }
}
