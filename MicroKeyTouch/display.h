//Display's drawing functions 

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
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xF800;
const uint16_t GREEN = 0x07E0;
const uint16_t MAGENTA = 0xF81F;
const uint16_t YELLOW = 0xFFE0;
const uint16_t CYAN = 0x07FF;
const uint16_t WHITE = 0xFFFF;


uint16_t ID;
uint8_t Orientation = 0;    //PORTRAIT



void tft_setup(){
  
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(Orientation);
  tft.fillScreen(BLACK);
}




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

void digit8(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t c){
  // Write 8 digit segments on screen
  //
  //      d3
  //       _
  //  d2  |_|  d4 __
  //  d1  |_|  d5   \ d6
  //  
  //      d0

  uint16_t r = h/2;
  
  //  d6  _
  //     |.|   
  //     |_|     
  tft.drawRoundRect(x0+h, y0+w, w, h, r, c);
  
  //  d5  _
  //     |_|  
  //     |_.    
  tft.drawRoundRect(x0+w+h, y0+r+w, h, w, r, c);

  //  d4  _
  //     |_.  
  //     |_|    
  tft.drawRoundRect(x0+w+h, y0+r, h, w, r, c);

  //  d3  .
  //     |_|   
  //     |_|   
  tft.drawRoundRect(x0+h, y0, w, h, r, c);

  //  d2  _
  //     ._|  
  //     |_|    
  tft.drawRoundRect(x0, y0+r, h, w, r, c);

  //  d1  _
  //     |_|   
  //     ._|  
  tft.drawRoundRect(x0, y0+r+w, h, w, r, c);
  
  //  d0  _
  //     |_|   
  //     |.|     
  tft.drawRoundRect(x0+h, y0+w+w, w, h, r, c);
 
}

int ckeypad(uint16_t x0, uint16_t y0, uint16_t r, uint16_t c){
  // return the selected number.
  
  blocked = true;
  // O O O
  // O O O
  // O O O
  //   O [O] 

  // 1 2 3
  // 4 5 6
  // 7 8 9
  //   0 [] // 
  
  int n; // number touched on cKeypad.
  
  //1rst col 
  tft.drawCircle(x0,y0,r,c);    //  1
  tft.drawCircle(x0,y0+2*r,r,c);//  4
  tft.drawCircle(x0,y0+4*r,r,c);//  7
  
  //2on col
  tft.drawCircle(x0+2*r,y0,r,c);    // 2
  tft.drawCircle(x0+2*r,y0+2*r,r,c);// 5
  tft.drawCircle(x0+2*r,y0+4*r,r,c);// 8
  tft.drawCircle(x0+2*r,y0+6*r,r,c);// 0
  

  //3rd Col
  tft.drawCircle(x0+4*r,y0,r,c);    // 3
  tft.drawCircle(x0+4*r,y0+2*r,r,c);// 6
  tft.drawCircle(x0+4*r,y0+4*r,r,c);// 9
  tft.fillCircle(x0+4*r,y0+6*r,r,c);// . // 10



  while(blocked){
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
 
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
   // if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) blocked = false;

    
    //tft.setCursor(0, (tft.height() * 3) / 4);
    //tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + " n:"+n);

    tp.x = map(tp.x, TS_MAXX, TS_MINX, 0, tft.width());
    tp.y = map(tp.y, TS_MINY, TS_MAXY, 0, tft.height());    
    tft.fillCircle(tp.x, tp.y, 10, GREEN);

    // Delete the number printing it in black 
    //tft.setCursor(0, (tft.height() * 3) / 4);
    //tft.setCursor(0, (tft.height()-60));
    // tft.setTextColor(BLACK);
    //tft.print(n);

    if (tp.x > x0-r && tp.x < x0+r && tp.y > y0-r && tp.y < y0+r) n = 1;     
    if (tp.x > x0+r && tp.x < x0+3*r && tp.y > y0-r && tp.y < y0+r) n = 2; 
    if (tp.x > x0+3*r && tp.x < x0+5*r && tp.y > y0-r && tp.y < y0+r) n = 3;

    if (tp.x > x0-r && tp.x < x0+r && tp.y > y0+r && tp.y < y0+3*r) n = 4;     
    if (tp.x > x0+r && tp.x < x0+3*r && tp.y > y0+r && tp.y < y0+3*r) n = 5; 
    if (tp.x > x0+3*r && tp.x < x0+5*r && tp.y > y0+r && tp.y < y0+3*r) n = 6;

    if (tp.x > x0-r && tp.x < x0+r && tp.y > y0+3*r && tp.y < y0+5*r) n = 7;     
    if (tp.x > x0+r && tp.x < x0+3*r && tp.y > y0+3*r && tp.y < y0+5*r) n = 8; 
    if (tp.x > x0+3*r && tp.x < x0+5*r && tp.y > y0+3*r && tp.y < y0+5*r) n = 9;

    if (tp.x > x0+r && tp.x < x0+3*r && tp.y > y0+5*r && tp.y < y0+7*r) n = 0; 
    if (tp.x > x0+3*r && tp.x < x0+5*r && tp.y > y0+5*r && tp.y < y0+7*r) n = 10; 


    
    //Print the number
    //tft.setCursor(0, (tft.height() * 3) / 4);
    //tft.setCursor(0, (tft.height()-60));
    //tft.setTextSize(2);
    //tft.setTextColor(RED);
    //tft.println(n);
    
    blocked = false;
    
  }
  return n;
}

void block_screen(){
  int n; // number touched on cKeypad.
  unsigned int password = 1234;
  unsigned int ipassword = 0; // incomming password
  //int i=0; // index for ipassword.
  int c = 0;    // c is the counter to avoid overflow the unsigned int. 
  
  logo(RED);
 
  // digit8(50,70,100,20,WHITE);
 
  do{
    
    ipassword=0;
    n = ckeypad(60,100,30,WHITE);
    c = 0;    // c is the counter to avoid overflow the unsigned int. 
    
    while(n != 10 && c<4){  // 10 is the key number to send the code. 
      
      tft.setCursor(0, (tft.height()-60));
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(ipassword);

      ipassword=ipassword*10+n;
      
      tft.setCursor(0, (tft.height()-60));
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print(ipassword);

      n = ckeypad(60,100,30,WHITE);
      c ++;
    }

    tft.setCursor(0, (tft.height()-60));
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.print(ipassword);

  }while (ipassword!=password); 
  
}


unsigned getCode(){
// Return 4 digit code
  
  int n;      // number touched on cKeypad.
  int c = 0;  // c is the counter to avoid overflow the unsigned int. 

  unsigned int code = 0;
//  logo(RED);
    
    n = ckeypad(60,100,30,WHITE);
    c = 0;    // c is the counter to avoid overflow the unsigned int. 
    
    while(n != 10 && c<4){  // 10 is the key number to send the code. 
      
      tft.setCursor(0, (tft.height()-60));
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print(code);

      code=code*10+n;
      
      tft.setCursor(0, (tft.height()-60));
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print(code);

      n = ckeypad(60,100,30,WHITE);
      c ++;
    }

    tft.setCursor(0, (tft.height()-60));
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.print(code);
    
    return code;
}



void button_one(){
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  tft.print("EXIT");
  
}

void touch_one(){
 boolean touched = false;
 while(!touched){
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
 
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    // EXIT button_exit();
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) touched = true;
    // button() 
    //if (tp.x > 450 && tp.x < 870  && tp.y > 750 && tp.y < 845){
    //Keyboard.println("Your text here"); 
    //delay(1000);   
    }   
}    

void one(){
  tft.fillScreen(BLACK);
  logo(GREEN);
  button_one();
  touch_one();
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
