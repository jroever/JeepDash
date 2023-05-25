/*----------------------------------------------------------------------------/
  JeepDash480 - Auxiliary Car Instrument Panel for SUVs (Jeep Wrangler JL)

Original Source:
 (https://github.com/jroever/JeepDash/)


Licence:
 [GnuGPL3](https://github.com/jroever/JeepDash/blob/main/LICENSE)

Author:
 [jroever](https://jroever.github.io/)

/----------------------------------------------------------------------------*/

#ifndef ArcMeter_h
#define ArcMeter_h
#include "LGFX_ESP32S3_RGB_MakerfabsParallelTFTwithTouch40.h"

static constexpr int TFT_DRKORANGE = 0xE381;
static constexpr int TFT_BKGRND = TFT_BLACK;
static constexpr int TFT_LABEL = TFT_WHITE;

static constexpr int RADIUS_X = 74;
static constexpr int RADIUS_Y = 74;

static constexpr int RADIUS_R4 = RADIUS_Y * 16 / 16;
static constexpr int RADIUS_R3 = RADIUS_Y * 14 / 16;
static constexpr int RADIUS_R2 = RADIUS_Y * 12 / 16;
static constexpr int RADIUS_R1 = RADIUS_Y * 11 / 16;
static constexpr int RADIUS_R0 = RADIUS_Y * 10 / 16;

class ArcMeter {

public:
  ArcMeter(LGFX *display, char* label, char* label_left, char* label_right, int pos_x, int pos_y);
  void setDigits(int digits){_digits = digits;}
	static int rgb565_gray(int b5){return((b5<<11)+(b5<<6)+b5);}
  static void drawArc(LGFX *display, int pos_x, int pos_y);
	void updateValue(int value);

private:
  int _pos_x, _pos_y;
  int _v0_ow,_v1_ow,_v2_ow;
  int _old_val;
  char *_label;
  int _digits;
  LGFX *_display;
};
#endif

