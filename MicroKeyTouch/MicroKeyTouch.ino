// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

#include "Keyboard.h" // Arduino Leonardo 
#include "bitmap_strek.h"

char *name = "BGood.";  //edit name of shield
//const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
//const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;

const int XP=7,XM=A1,YP=A2,YM=6; //240x320 ID=0x9329
const int TS_LEFT=895,TS_RT=153,TS_TOP=87,TS_BOT=905;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

boolean blocked = true;

/*
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
*/

const uint16_t BLACK = 0x0000;
const uint16_t RED = 0xF800;
const uint16_t YELLOW = 0xFFE0;
const uint16_t CYAN = 0x07FF;


void button(){
  uint16_t cxpos = 20;
  uint16_t cypos = 280;
  uint16_t cradius = 20; 
  uint16_t ccolor = CYAN;
  
  tft.fillRect(cxpos, cypos-20, 100, 41, ccolor);
  tft.fillCircle(cxpos, cypos, cradius, ccolor);
  cxpos = cxpos + 100;
  tft.fillCircle(cxpos, cypos, cradius, ccolor);
  tft.setCursor(cxpos - 100, cypos);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print(F("Password"));  
}

void button_exit(){
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  tft.print("EXIT");
  
}

void logo(uint16_t color){
  int dx = 100, dy = 0, w = 50, h = 75;
  const int SZ = w * h / 8;
  uint8_t sram[SZ];
  
  memcpy_P(sram, estrek, SZ);
  tft.drawBitmap(dx, dy, estrek, w, h, color);   
}

void block_screen(){

  logo(RED);

  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  tft.print("UNLOCK");
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0, (tft.height() * 6) / 8);
  tft.print("Touch screen for loc");
     
  while(blocked){
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
 
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) blocked = false;
    tft.setCursor(0, (tft.height() * 3) / 4);
    tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");    
  }

  tft.print(F("unlocked"));
}

boolean login(){
  block_screen();
  return true;
}


void screen(){
  logo(YELLOW);
  button_exit();
  button();
  
}

void touch(){
 while(!blocked){
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
 
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    // EXIT button_exit();
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) blocked = true;
    // button() 
    if (tp.x > 450 && tp.x < 870  && tp.y > 750 && tp.y < 845){
    Keyboard.println("Your text here"); 
    delay(1000);   
    }   
  }  
}

void setup(void){
  uint16_t tmp;

  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(Orientation);
  tft.fillScreen(BLACK);

}

void loop()
{
 tft.fillScreen(BLACK);
 
 if(login()){
    tft.fillScreen(BLACK);
    screen();
    touch();
  }else{
    // Error login()
  }
}
