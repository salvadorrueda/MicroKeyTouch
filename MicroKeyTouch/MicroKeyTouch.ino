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

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void show_Serial(void)
{
    Serial.println(F("Most Touch Screens use pins 6, 7, A1, A2"));
    Serial.println(F("But they can be in ANY order"));
    Serial.println(F("e.g. right to left or bottom to top"));
    Serial.println(F("or wrong direction"));
    Serial.println(F("Edit name and calibration statements\n"));
    Serial.println(name);
    Serial.print(F("ID=0x"));
    Serial.println(ID, HEX);
    Serial.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
    Serial.println("Calibration is: ");
    Serial.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
    Serial.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
    Serial.println("Wiring is always PORTRAIT");
    Serial.println("YP=" + String(YP)  + " XM=" + String(XM));
    Serial.println("YM=" + String(YM)  + " XP=" + String(XP));
}

void show_tft(void)
{
/*
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print(F("ID=0x"));  
    tft.println(ID, HEX);
    tft.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
    tft.println("");
    tft.setTextSize(2);
    tft.println(name);
    tft.setTextSize(1);
    tft.println("PORTRAIT Values:");
    tft.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
    tft.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
    tft.println("\nWiring is: ");
    tft.println("YP=" + String(YP)  + " XM=" + String(XM));
    tft.println("YM=" + String(YM)  + " XP=" + String(XP));
    tft.setTextSize(2);
    
  //  tft.setTextColor(RED);
  //  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  //  tft.print("EXIT");
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(0, (tft.height() * 6) / 8);
    tft.print("Touch screen for loc");

  */  
    while (1) {
        tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
        //if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
        //tft.setCursor(0, (tft.height() * 3) / 4);
        tft.setCursor(0, 300);
        //tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
        if (tp.x > 450 && tp.x < 870  && tp.y > 750 && tp.y < 845){
          //tft.print("Salvador Rueda");
          Keyboard.println("Your text here"); 
          delay(1000);      
        }else tft.print("                    ");
    }
}


void setup(void)
{
    uint16_t tmp;

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    show_Serial();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);


////////////////////////
// Button
///////////////////////
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


/////////////////////////////


////////////////////////
//    bitmap  
//////////////////////// 

    int dx = 100, dy, w = 50, h = 75;
    const int SZ = w * h / 8;
    uint8_t sram[SZ];
    memcpy_P(sram, estrek, SZ);

    dy = 0;
    tft.drawBitmap(dx, dy, estrek, 50, 75, YELLOW); 
    
///////////////////////    

    show_tft();
       
}

void loop()
{

}
