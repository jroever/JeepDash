/*----------------------------------------------------------------------------/
  JeepDash480 - Auxiliary Car Instrument Panel for SUVs (Jeep Wrangler JL)

Original Source:
 (https://github.com/jroever/JeepDash/)


Licence:
 [GnuGPL3](https://github.com/jroever/JeepDash/blob/main/LICENSE)

Author:
 [jroever](https://jroever.github.io/)
 
 /----------------------------------------------------------------------------*/


#include "ArcMeter.h"

ArcMeter::ArcMeter(LGFX *display, char* label, char* label_left, char* label_right, int pos_x, int pos_y) 
// =======================
{
  _pos_x = pos_x;
  _pos_y = pos_y;
  _label = label;
  _display = display;

  _digits = 0;
  _old_val = 0;

  _v0_ow=0;
  _v1_ow=0;
  _v2_ow=0;

  // static background 
  display->fillRect(_pos_x, _pos_y, 2*RADIUS_X, 2*RADIUS_Y  , TFT_BKGRND);
 
  // outter gradient arc
  int color, j=1;

  for (int k=2;k<60;k=k+3){
    color = rgb565_gray(j++); // 565 grayscale (32 level)
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R4-3, RADIUS_R4-1, 174+k, 366-k, color); // outter line
  }

  _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R0-1, RADIUS_R0+1, 170-5, 370+5, TFT_WHITE); // inner line

  //_display->setFont(&fonts::Font4);
  //_display->setFont(&fonts::FreeSans12pt7b);
  _display->setFont(&fonts::FreeSansBold9pt7b);
  _display->setTextColor(TFT_LIGHTGRAY, TFT_BKGRND);
  _display->setTextDatum(textdatum_t::middle_center);
  _display->drawString(label, _pos_x+RADIUS_X, _pos_y+RADIUS_Y+28+24);

  // Lower display
  //_display->setFont(&fonts::Font2);
  _display->setFont(&fonts::FreeSans9pt7b);
  //_display->setTextColor(TFT_DARKGREEN, TFT_BKGRND);
  _display->setTextColor(TFT_DARKGRAY, TFT_BKGRND);
  _display->setTextDatum(textdatum_t::bottom_left);
  _display->drawString(label_left, _pos_x+15, _pos_y+2*RADIUS_Y-37);

  //_display->setTextColor(TFT_RED, TFT_BKGRND);
  _display->setTextColor(TFT_DARKGRAY, TFT_BKGRND);
  _display->setTextDatum(textdatum_t::bottom_right);
  _display->drawString(label_right, _pos_x+2*RADIUS_X-15, _pos_y+2*RADIUS_Y-37);
}

// =======================
void ArcMeter::updateValue(int val)
// =======================
{
  if (val==_old_val) return;

  //200 -> 64.0
  float f = val*0.32;

  int color, txtCol;
  if (f<32.0) {
    color = ((int(f)%32)<<11)+((int(2*f)%64)<<5)+(31); // Blue to White
    txtCol = TFT_WHITE;
  } else {
    color = (31<<11)+((63-(int(2*f)%64))<<5)+((31-(int(f)%32))); // White to Red
    txtCol = color;
  }  

  color = TFT_DRKORANGE;

  // ==============
  // Center Digits
  // ==============
  // _display->setFont(&fonts::FreeMonoBold18pt7b);
  _display->setFont(&fonts::FreeSansBold18pt7b);
  //_display->setFont(&fonts::Font4);
  _display->setTextDatum(textdatum_t::middle_center);

  if (_digits>0){
    float fval = val/10.0;
    float ofval = _v0_ow/10.0;
    _display->setTextColor(TFT_BKGRND, TFT_BKGRND);
    _display->drawFloat(ofval, 1, _pos_x+RADIUS_X, _pos_y+RADIUS_Y-2);
    _display->setTextColor(txtCol, TFT_BKGRND);
    _display->drawFloat(fval, 1, _pos_x+RADIUS_X, _pos_y+RADIUS_Y-2);
  } else {
    _display->setTextColor(TFT_BKGRND, TFT_BKGRND);
    _display->drawNumber(_v0_ow, _pos_x+RADIUS_X, _pos_y+RADIUS_Y-2);
    _display->setTextColor(txtCol, TFT_BKGRND);
    _display->drawNumber(val, _pos_x+RADIUS_X, _pos_y+RADIUS_Y-2);
  }  
  // clear old remaining text if needed
  //if (_v0_ow>v0_w) {
  //  _display->fillRect(_pos_x+RADIUS_X-(_v0_ow>>1), _pos_y+RADIUS_Y-16, (_v0_ow-v0_w)>>1, 30, TFT_BKGRND);
//    _display->fillRect(_pos_x+RADIUS_X-(_v0_ow>>1), _pos_y+RADIUS_Y-16, _v0_ow, 30, TFT_BKGRND);
  //}
  _v0_ow = val;

  if(0){
  // ==============
  // Lower Left
  // ==============
    _display->setFont(&fonts::Font4);
    _display->setTextColor(TFT_DARKGRAY, TFT_BKGRND);
    _display->setTextDatum(textdatum_t::bottom_left);
    int v1_w = _display->drawNumber(val>>1, _pos_x, _pos_y+2*RADIUS_Y);
    
    // clear old remaining text if needed
    if (_v1_ow>v1_w) _display->fillRect(_pos_x+v1_w, _pos_y+2*RADIUS_Y-24, _v1_ow-v1_w, 30, TFT_BKGRND);
    _v1_ow = v1_w;

    // ==============
    // Lower Right
    // ==============
    _display->setTextColor(TFT_DARKGRAY, TFT_BKGRND);
    _display->setTextDatum(textdatum_t::bottom_right);
    int v2_w =_display->drawNumber(val+100, _pos_x+2*RADIUS_X, _pos_y+2*RADIUS_Y);

    // clear old remaining text if needed
    if (_v2_ow>v2_w) _display->fillRect(_pos_x+2*RADIUS_X-_v2_ow, _pos_y+2*RADIUS_Y-24, _v2_ow-v2_w, 30, TFT_BKGRND);
    _v2_ow = v2_w;
  }

  // ==============
  // update Arc
  // ==============
  _display->setFont(&fonts::Font4);
  if (_old_val<0){
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R1+2, RADIUS_R3, 170, 170+val, color);
  }
  else if (val<_old_val){ // smaller value - erase previous
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R1+2, RADIUS_R3, 170+val, 171+_old_val, TFT_BLACK);
  }
  else {
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R1+2, RADIUS_R3, 170+_old_val, 170+val, color);
  }
  
  // ============
  // draw ticks
  // ============
  for (int i = 1; i <= 3; i++)
  {
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R0, RADIUS_R2, 168 + i * 50, 172 + i * 50, TFT_WHITE);
  }
  if (0) for (int i = 0; i <= 1; i++)
  {
    _display->fillArc(_pos_x+RADIUS_X, _pos_y+RADIUS_Y, RADIUS_R0, RADIUS_R3, 168 + i * 200, 172 + i * 200, TFT_WHITE);
  }

  // bottom lines
  _display->fillRect(_pos_x+13, _pos_y+RADIUS_X+10, 17, 3, TFT_WHITE);
  _display->fillRect(_pos_x+2*RADIUS_X-13-17, _pos_y+RADIUS_X+10, 17, 3, TFT_WHITE);
  
  _old_val=val;

}
