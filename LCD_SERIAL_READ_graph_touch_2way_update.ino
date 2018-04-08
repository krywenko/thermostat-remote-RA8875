

#include <SPI.h>
#include <RA8875.h>
#include "fonts/akashi_36.c"
#include "fonts/squarefont_14.c"
#define RA8875_INT 2 //--touch interface

#define RA8875_CS 10

#define RA8875_RESET 9//any pin or 255 to disable it!



RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);
//---touch interface--

//uint16_t tx, ty;
//uint16_t choosenColor = 0;
/*
void interface(){
  tft.fillRect(10,10,40,40,RA8875_WHITE);
  tft.fillRect(10+(40*1)+(10*1),10,40,40,RA8875_BLUE);
  tft.fillRect(10+(40*2)+(10*2),10,40,40,RA8875_RED);
  tft.fillRect(10+(40*3)+(10*3),10,40,40,RA8875_GREEN);
  tft.fillRect(10+(40*4)+(10*4),10,40,40,RA8875_CYAN);
  tft.fillRect(10+(40*5)+(10*5),10,40,40,RA8875_MAGENTA);
  tft.fillRect(10+(40*6)+(10*6),10,40,40,RA8875_YELLOW);
  tft.drawRect(10+(40*7)+(10*7),10,40,40,RA8875_WHITE);
}*/
int Screen =1;
int LScreen = 1;
int RScreen = 1;
//int Ttemp;
//int Tset;

///end of touch 
String weather = "please wait";
String Fhigh;
String Flow;
String Fday;
String Fpop;
uint32_t runTime = -99999;       // time for next update
uint32_t runTime1 = -99999;
int reading = 0; // Value to be displayed

int scan =0; //x step for graphing
int chg =0;  // value for drawing ersase block

int ext1 =0; /// external output so you can use the value outside its function
int ext2 =0;
int ext3 =0;
int ext4 =0;
int ext5 =0;///// thermostat 
int ext6 = 0;
int ext7 =0; 
int ext8 =0;
int ext9 =0;
int ext10 =0;///////relay 
int ext11 =0;
int ext12 = 0;
int ext13 =0; 
int ext14 =0;
int ext15 =0;
int ext16 =0;
int ext17 =0;
int ext18 = 0;//////// sensor relay
int ext19 =0;
int ext20 =0;///////relay 
int ext21 =0;
int ext22 = 0;
int ext23 =0; 
int ext24 =0;
int ext25 =0;
int ext26 =0;


boolean graph_1 = true; // set  vertical, horizontal,and graph function to redraw
boolean graph_2 = true;
boolean graph_3 = true;
boolean graph_4 = true;
boolean graph_5 = true;
boolean graph_6 = true;
boolean graph_7 = true;
boolean graph_8 = true; // set  vertical, horizontal,and graph function to redraw
boolean graph_9 = true;
boolean graph_10 = true;
boolean graph_11 = true;
boolean graph_12 = true;
boolean graph_13 = true;
boolean graph_14 = true;

boolean redraw1 = true;

double ox , oy ;/// graph plot ordinates 
double ox2 , oy2 ;
int Ttempb;
String command; // serial input capture string

char msg2[50];
char msg3[50];

void setup() {
 Serial.begin(115200);
Serial2.begin(19200);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("RA8875 start");

 // pinMode(ADJ_PIN, INPUT);
  tft.begin(RA8875_800x480);
 //double x, y;
 // put your setup code here, to run once:
Serial.println("started");
//touchscreen
tft.useINT(RA8875_INT);
  tft.touchBegin();//enable Touch support!
 // interface();
  tft.enableISR(false);
tft.brightness(50);
info_box(0);   

Sensor_error(-1,0);

}

void loop() 
{

   if(Serial2.available())
   {
      char c = Serial2.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
      }
  }
Top_touch();
Left_touch();
Right_touch();
}

///////touch-interfaces///////////
//////////////////////////////////

 void Top_touch() {
uint16_t tx, ty;
uint16_t choosenColor = 0;
 if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 10 && ty <= 60){ //interface area
        if ((tx > 10 && tx < (10+120))){
          choosenColor = RA8875_WHITE;
         // interface();
         Screen =1;
          tft.fillRect(0,0,800,128,RA8875_BLACK);
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
        } 
        else if ((tx > 10+(120*1)+(10*1) && tx < 10+(120*2)+(10*1))){
          choosenColor = RA8875_BLUE;
          //interface();
          Screen = 2;
           tft.fillRect(0,0,800,127,ORANGE);
       
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
        } 
        else if ((tx > 10+(120*2)+(10*2) && tx < 10+(120*3)+(10*2))){
          choosenColor = RA8875_RED;  
         // interface();
         Screen =3;
          tft.fillRect(0,0,800,128,RA8875_PURPLE);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
        } 
        else if ((tx > 10+(120*3)+(10*3) && tx < 10+(120*4)+(10*3))){
          choosenColor = RA8875_GREEN;  
          //interface();
          Screen=4;
           tft.fillRect(0,0,800,128,RA8875_YELLOW);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
        } 
        else if ((tx > 10+(120*4)+(10*4) && tx < 10+(120*5)+(10*4))){
          choosenColor = RA8875_CYAN;  
          //interface();
          Screen=5;
           tft.fillRect(0,0,800,128,RA8875_GREEN);
    
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
        } 
        else if ((tx > 10+(120*5)+(10*5) && tx < 10+(120*6)+(10*2))){
          choosenColor = RA8875_MAGENTA;  
          //interface();
          Screen=6;
           tft.fillRect(0,0,800,128,RA8875_BLACK);
        
          tft.fillCircle(tft.width()-10,10,5,choosenColor);
          delay(500);
       } 
    } 
  } 
  
}

void Left_touch() {
  uint16_t tx, ty;
uint16_t choosenColor = 0;
  if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 380 && ty <= 460){ //interface area
        if ((tx > 10 && tx < (350))){
         LScreen++;
         if (LScreen > 4) LScreen = 1;
         // interface();
         
    tft.fillRect(0,440,280,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(0,400,280,40,RA8875_BLACK);
    tft.fillRect(0,360,280,40,RA8875_BLACK);
    tft.fillRect(0,320,280,40,RA8875_BLACK);
    tft.fillRect(0,280,280,40,RA8875_BLACK); 
    tft.fillRect(0,240,280,40,RA8875_BLACK);
    tft.fillRect(0,200,280,40,RA8875_BLACK);
    tft.fillRect(0,160,280,40,RA8875_BLACK); 
    tft.fillRect(0,120,280,40,RA8875_BLACK); 
    //tft.fillRect(280,80,520,40,RA8875_BLACK);
         // tft.fillRect(0,480,280,-280,RA8875_BLACK);
            tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(0, 128);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(LScreen);
        tft.setFontScale(0);
        graph_2=true;graph_5=true;
        delay(500);
        }
      }
  } 
}


void Right_touch() {
  uint16_t tx, ty;
uint16_t choosenColor = 0;
  if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 380 && ty <= 460){ //interface area
        if ((tx > 500 && tx < (770))){
          RScreen++;
         if (RScreen > 4) RScreen = 1;
         // interface();
         //RScreen =30;
          //tft.fillRect(0,0,800,128,RA8875_PURPLE);
    tft.fillRect(280,440,520,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(280,400,520,40,RA8875_BLACK);
    tft.fillRect(280,360,520,40,RA8875_BLACK);
    tft.fillRect(280,320,520,40,RA8875_BLACK);
    tft.fillRect(280,280,520,40,RA8875_BLACK); 
    tft.fillRect(280,240,520,40,RA8875_BLACK);
    tft.fillRect(280,200,520,40,RA8875_BLACK);
    tft.fillRect(280,160,520,40,RA8875_BLACK); 
    tft.fillRect(280,120,520,40,RA8875_BLACK); 
    tft.fillRect(280,80,520,40,RA8875_BLACK);
    graph_3=true;graph_4=true;
         tft.setFontScale(2);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(750, 120);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(RScreen);
        tft.setFontScale(0);
        delay(500);
        }
      }
  } 
}

void Thermo(int Ttemp, int Tset, int heat, int fan) {
   uint16_t tx, ty;
uint16_t choosenColor = 0;
    int16_t xpos = 0;
    int16_t ypos = 128;
    uint16_t radius = 135;
    int16_t distance = 14;
   
    
  tft.ringMeter(Ttemp,-10,40,xpos,ypos,radius,"none",3,tft.htmlTo565(0x848482),150,10);
  tft.setFont(&akashi_36);
 
  if(Ttempb == Ttemp){
  tft.setFontScale(2);tft.setCursor(70, 200);tft.setTextColor(RA8875_WHITE);tft.print(Ttemp);
  } else {
    tft.setFontScale(2);tft.setCursor(70, 200);tft.setTextColor(RA8875_BLACK);tft.print(Ttempb);tft.setCursor(70, 200);tft.setTextColor(RA8875_WHITE);tft.print(Ttemp);
  }
  Ttempb=Ttemp;
  tft.setFont(INT);
  tft.setFontScale(2);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(115, 320);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(Tset);
  tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 165);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("    ");
  tft.setFontScale(2);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(20, 390);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("THERMOSTAT");      
        tft.setFontScale(0);
       if(ext7 ==0){ tft.fillCircle(150,205,7,RA8875_RED);}
       if(ext7 ==1){ tft.fillCircle(150,205,7,RA8875_BLUE);}
       if(ext7 ==2){ tft.fillCircle(150,205,7,RA8875_YELLOW);}
             
       if(ext8 ==1){ tft.fillCircle(130,205,7,RA8875_GREEN);}
       if(ext8 ==0){ tft.fillCircle(130,205,7,RA8875_RED);}

       Serial.print("ext8   "); Serial.println(ext8);
       
  if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 150 && ty <= 300){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 165);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-0)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 165);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-0)");
          delay(200);
        }
        else if (tx >160  && tx <190 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 165);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print("HEAT");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-h)");
          delay(200);
        } 
        else if (tx >70  && tx <100 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 165);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" FAN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-f)");
          delay(200);
        } 
      }
  } 
  graph_6=true;graph_7=true; graph_8=true;graph_9=true;
}

void Zone1(int sensor1, int sensor2, int sensor3, int sensor4, int relay1, int relay2, int relay3, int relay4 ){
    uint16_t tx, ty;
    tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("    ");
   tft.setFontScale(2);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(20, 390);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("  Zone 1");
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 150);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay1); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 210);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay2); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 270);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay3); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 330);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay4);   
        tft.setFontScale(0);
if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 150 && ty <= 175){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-1)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-1)");
          delay(200);
        }
      }
      if (ty >= 210 && ty <= 255){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-2)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-2)");
          delay(200);
        }
      }
      if (ty >= 270 && ty <= 295){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-3)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-3)");
          delay(200);
        }
      }
      if (ty >= 330 && ty <= 350){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-4)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-4)");
          delay(200);
        }
      }
}


        
        reading = sensor1;
  DrawBarChartH(tft, 40, 150, 180, 25, 0, 70, 10, reading, 0, 0, GREEN, BLACK,  BLUE, WHITE, BLACK, "", graph_6);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor2;
  DrawBarChartH(tft, 40, 210, 180, 25, 0, 70, 10, reading, 0, 0, YELLOW, BLACK,  RED, WHITE, BLACK, "", graph_7);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor3;
  DrawBarChartH(tft, 40, 270, 180, 25, 0, 70, 10, reading, 0, 0, RED, BLACK,  YELLOW, WHITE, BLACK, "", graph_8);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor4;
  DrawBarChartH(tft, 40, 330, 180, 25, 0, 70, 10, reading, 0, 0, BLUE, BLACK,  GREEN, WHITE, BLACK, "", graph_9);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
graph_10=true;graph_11=true; graph_12=true;graph_13=true;
} 

void Zone2(int sensor5, int sensor6, int sensor7, int sensor8, int relay5, int relay6, int relay7, int relay8){

     uint16_t tx, ty;
    tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("    ");
   tft.setFontScale(2);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(20, 390);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("  Zone 2");
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 150);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay5); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 210);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay6); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 270);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay7); 
   tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(5, 330);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(relay6);   
        tft.setFontScale(0);
if (tft.touched()){//easy!
      tft.touchReadPixel(&tx, &ty);//read directly in pixel!
      if (ty >= 150 && ty <= 175){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-5)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-5)");
          delay(200);
        }
      }
      if (ty >= 210 && ty <= 255){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-6)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-6)");
          delay(200);
        }
      }
      if (ty >= 270 && ty <= 295){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-7)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-7)");
          delay(200);
        }
      }
      if (ty >= 330 && ty <= 350){ //interface area
        if ((tx > 10 && tx < 50)){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("DOWN");
        tft.setFontScale(0);
        Serial2.println("cmd_100(0-8)");
        delay(200);
        }
         else if (tx >200  && tx <290 ){
         tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(100, 115);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.print(" UP ");
        tft.setFontScale(0);
        Serial2.println("cmd_100(1-8)");
          delay(200);
        }
      }
}

 
        reading = sensor5;
        DrawBarChartH(tft, 40, 150, 180, 25, 0, 70, 10, reading, 0, 0, GREEN, BLACK,  BLUE, WHITE, BLACK, "", graph_10);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor6;
  DrawBarChartH(tft, 40, 210, 180, 25, 0, 70, 10, reading, 0, 0, YELLOW, BLACK,  RED, WHITE, BLACK, "", graph_11);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor7;
  DrawBarChartH(tft, 40, 270, 180, 25, 0, 70, 10, reading, 0, 0, RED, BLACK,  YELLOW, WHITE, BLACK, "", graph_12);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 
reading = sensor8;
  DrawBarChartH(tft, 40, 330, 180, 25, 0, 70, 10, reading, 0, 0, BLUE, BLACK,  GREEN, WHITE, BLACK, "", graph_13);//xpos,ypos, width,height,L_range,H_range,step,reading, font, decimial 

}
void info_box(int cond){
//drawRoundRect
if (Screen ==1){ 
 tft.drawRoundRect(425,0,360,128,10,RA8875_CYAN); 
 tft.drawRoundRect(424,1,360,126,10,RA8875_CYAN);
 tft.drawRoundRect(423,2,360,124,10,RA8875_CYAN);
 tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(430, 11);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("INFORMATION:");
 if(cond ==0){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(640, 11);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("STANDBY");}
 if(cond ==1){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(630, 11);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(" READY  ");}
 tft.setFontScale(0);
}
}
void Sensor_error(int Error, int Sen_ID){
 if (Screen ==1){ 
tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(430, 45);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("TEMP.SENSORS"); 
if(Error == -1){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(635, 45);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("OFFLINE");}
if( Sen_ID ==0){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(635, 45);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print("ONLINE ");}
 else {if(Error == 0){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(635, 45);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print("ONLINE");tft.print(Sen_ID);} }
if(Error > 0){tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(635, 45);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("ERROR ");tft.print(Error);}
tft.setFontScale(0);}
}

////////// Parse serial string and graphs them////////////
////////////////////////////////////////////////////////// 

void parseCommand(String com)
{
 //--graphing variables 
    int16_t xpos = 0;
    int16_t ypos = 0;
    uint16_t radius = 65;
    int16_t distance = 14;

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  //int test = part1.toInt();
  //Serial.print(part1);
  //Serial.println("#");
  part2 = com.substring(com.indexOf("(")+1);
  Serial.println(part2);

//--input and graphing 
//////////////////////  
//info_box();
//Serial.print("SCREEN  "); Serial.println(Screen);
  if (part1 == "1")
  {
    
   // Serial.print("recieved 1 ");
    String raw_CMD;
    float input1 = part2.toFloat();
    raw_CMD=input1;
//Serial.println(input1);
    }
  if (part1== "2")
    {
      
    //Serial.print("recieved 2 ");
    String raw_CMD;
    float input2 = part2.toFloat();
    raw_CMD=input2;
//Serial.println(input2);
reading = input2;
ext3= input2;
if (LScreen ==1) DrawBarChartV(tft, 10,  440, 10, 120, -40, 40 , 20, reading , 4 , 0, DKORANGE, BLACK, BLUE, WHITE, BLACK, "TEMP", graph_2);
 int Cntr = 30; if (input2 > 999) Cntr = 20; //if(input2<100) Cntr=40;
 int Gnum = 4;
 if (Screen ==1){
tft.ringMeter(input2,-40,40,xpos+ (radius * Gnum) + (distance*2),ypos,radius,"none",3,tft.htmlTo565(0x848482),110,10);
tft.setFontScale(1);tft.setTextColor(RA8875_BLUE, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+30,ypos+40);tft.print("TEMP");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+Cntr,ypos+80);tft.print(reading);tft.print(" ");
 }
 Sensor_error(0,0); //  1st 0. means no error. 2nd 0  denotes not to display sensor ID
tft.setFontScale(0);  
    }
 if (part1 == "3")
    {
      
    //Serial.print("recieved 3 ");
    String raw_CMD;
    float input3 = part2.toFloat();
    raw_CMD=input3;
int Gnum = 3;   //graph number  
int Cntr = 30; if (input3 > 999) Cntr = 20;
if (Screen ==1){
tft.ringMeter(input3,0,100,xpos+ (radius * Gnum) + (distance*2),ypos,radius,"none",7,tft.htmlTo565(0x848482),110,10);
tft.setFontScale(1);tft.setTextColor(RA8875_BLUE, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+30,ypos+40);tft.print(" RH%");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + (distance*2)+Cntr,ypos+80);tft.print("50");
}
tft.setFontScale(0);  
    
   // Serial.println(input3);
    
  }

  if (part1 == "4")
  {
    
    //Serial.print("recieved 4 ");
    String raw_CMD;
     float input4 = part2.toInt();
    ext1 = input4;
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =2;
if (Screen==1){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("SOLAR");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(ext1);tft.print("   ");
tft.ringMeter(input4,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);    
//Serial.println(ext1);
    }
    //Serial.print(ext1);
     //Serial.println("   ext1");
  if (part1== "5")
    {
      
    //Serial.print("recieved 5 ");
    String raw_CMD;
    float input5 = part2.toInt();
    //input5 = input5/1000;
    int Cntr = 30;
        
   // if (input5 > 999){ Cntr = 20; if (chg > 0) chg=0;}
    //if (input5 < 999){ Cntr = 30;if (chg < 2 ){tft.fillRect(xpos+15,ypos+30,75,25,RA8875_BLACK);chg++;}}
if (Screen==1){ 
info_box(1);   
    
tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(xpos+30,ypos+40);tft.print("GRID");tft.setFontScale(1);tft.setCursor(xpos+Cntr,ypos+80);tft.print(ext2);tft.print("   ");
  
tft.ringMeter(input5,-1,8000,xpos,ypos,radius,"none",4,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);
//tft.fillRect(10,30,80,25,RA8875_GREEN);
  ext2=input5;
//Serial.println(input5);
if (LScreen == 1) screenPie(ext1,ext2,ext4);
    }
 if (part1 == "6")
    {
      
   // Serial.print("recieved 6 ");
    String raw_CMD;
    float input6 = part2.toFloat();
    raw_CMD=input6;
    ext4=input6;
    //Serial.println(input6);
    
  }

/////////////////////thermostat settings////////////////////
///////////////////////////////////////////////////////////
  if (part1 == "7")
  {
    
   // Serial.print("recieved 7 ");
    String raw_CMD;
    float input7 = part2.toFloat();
    raw_CMD=input7;
    ext5=input7;
    info_box(1);
    Sensor_error(0,1);
//Serial.println(input7);

    }
  if (part1== "8")
    {
      
   // Serial.print("recieved 8 ");
    String raw_CMD;
    float input8 = part2.toFloat();
    raw_CMD=input8;
    ext6=input8;
//Serial.println(input8);

    }
 if (part1 == "9")
    {
      
   // Serial.print("recieved 9 ");
    String raw_CMD;
    float input9 = part2.toFloat();
    raw_CMD=input9;
    ext7 = input9;
//    Serial.println(input9);
    
  }
  
  if (part1 == "10")
  {
    
   // Serial.print("recieved 10 ");
    String raw_CMD;
    float input10 = part2.toFloat();
    ext8=input10;
///Serial.println(input10);
    }
      
  if (part1== "11")
    {
      
   // Serial.print("recieved 11 ");
    String raw_CMD;
    float input11 = part2.toInt();
    raw_CMD=input11;
    Sensor_error(input11,1);
///Serial.println(input11);

    }
 /////////////////////relays///////////////////
  if (part1== "12")
    {
      
  ///  Serial.print("recieved 12 ");
    String raw_CMD;
    float input12 = part2.toFloat();
    ext10=input12;
///Serial.println(input12);

    }
 if (part1 == "13")
    {
      
 //   Serial.print("recieved 13 ");
    String raw_CMD;
    float input13 = part2.toFloat();
    ext11=input13;
 //   Serial.println(input13);
    
  }
  
  if (part1 == "14")
  {
    
  ///  Serial.print("recieved 14 ");
    String raw_CMD;
    float input14 = part2.toFloat();
    ext12=input14;
///Serial.println(input14);
    }
  
  if (part1== "15")
    {
      
   /// Serial.print("recieved 15 ");
    String raw_CMD;
    float input15 = part2.toFloat();
    ext13=input15;
///Serial.println(input15);

    }
    
  if (part1== "16")
    {
      
  ////  Serial.print("recieved 16 ");
    String raw_CMD;
    float input16 = part2.toFloat();
    ext14=input16;
////Serial.println(input16);

    }
 if (part1 == "17")
    {
      
   /// Serial.print("recieved 17 ");
    String raw_CMD;
    float input17 = part2.toFloat();
    ext15=input17;
  ///  Serial.println(input17);
    
  }
  
  if (part1 == "18")
  {
    
  ///  Serial.print("recieved 18 ");
    String raw_CMD;
    float input18 = part2.toFloat();
    ext16=input18;
///Serial.println(input18);
    }
  if (part1== "19")
    {
      
  ///  Serial.print("recieved 19 ");
    String raw_CMD;
    float input19 = part2.toFloat();
    ext17=input19;
///Serial.println(input19);
///////////////////////////relay sensors//////////////
    }
 if (part1 == "20")
    {
      
   /// Serial.print("recieved 20 ");
    String raw_CMD;
    float input20 = part2.toFloat();
    ext18=input20;
  ///  Serial.println(input20);
    
  }
if (part1 == "21")
    {

    String raw_CMD;
    float input21 = part2.toFloat();
    ext19=input21;

  }

if (part1 == "22")
    {
  String raw_CMD;
    float input22 = part2.toFloat();
    ext20=input22;
  }

  if (part1 == "23")
    {
    String raw_CMD;
    float input23 = part2.toFloat();
    ext21=input23;
  }
if (part1 == "24")
    {
   String raw_CMD;
    float input24 = part2.toFloat();
    ext22=input24;
  }
if (part1 == "25")
    {
   String raw_CMD;
    float input25 = part2.toFloat();
    ext23=input25;
  }

if (part1 == "26")
    {

 String raw_CMD;
    float input26 = part2.toFloat();
    ext24=input26;

  }

if (part1 == "27")
    {
   String raw_CMD;
    float input27 = part2.toFloat();
    ext25=input27;;
  }
  
  ////////////////////end of thermostat  controlls//////////
//////////////////////////////////////////////////////////

  if (part1 == "28")
    {
 String raw_CMD;
    float input28 = part2.toFloat();
    ext26=input28;
  }


  
if (part1 == "29")
    {
    String raw_CMD;
    
reading = part2.toInt();
if (Screen==2){ 
 int Cntr = 30;  
    
tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(xpos+30,ypos+40);tft.print("INPUT1");tft.setFontScale(1);tft.setCursor(xpos+Cntr,ypos+80);tft.print(reading);tft.print("   ");
  
tft.ringMeter(reading,-1,8000,xpos,ypos,radius,"none",4,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);
    
  // Fday=part2;
   // Serial.println(part2);
  }
if (part1 == "30")
    {
    String raw_CMD;
    reading = part2.toInt();
if (Screen==2){ 
 int Cntr = 30;  
    
tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(xpos+30,ypos+40);tft.print("INPUT2");tft.setFontScale(1);tft.setCursor(xpos+Cntr,ypos+80);tft.print(reading);tft.print("   ");
  
tft.ringMeter(reading,-1,8000,xpos,ypos,radius,"none",4,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);
   ///Fpop=part2;
    //Serial.println(part2);
  }
  if (part1 == "31")
    {

    String raw_CMD;
   //weather=part2;
   reading = part2.toInt();
  
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =2;
if (Screen==2){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("input3");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(reading);tft.print("   ");
tft.ringMeter(reading,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0);   

  }

if (part1 == "32")
    {
    String raw_CMD;
      reading = part2.toInt();
  
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =3;
if (Screen==2){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("input4");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(reading);tft.print("   ");
tft.ringMeter(reading,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0); 
   //F//low=part2;
   /// Serial.println(part2);
  }

  if (part1 == "33")
    {
    String raw_CMD;
      reading = part2.toInt();
  
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =4;
if (Screen==2){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("input5");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(reading);tft.print("   ");
tft.ringMeter(reading,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0); 
  // Fhigh=part2;
   /// Serial.println(part2);
  }
if (part1 == "34")
    {
    String raw_CMD;
      reading = part2.toInt();
  
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =5;
if (Screen==2){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("input3");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(reading);tft.print("   ");
tft.ringMeter(reading,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0); 
   //Fday=part2;
    ///Serial.println(part2);
  }
if (part1 == "35")
    {
    String raw_CMD;
      reading = part2.toInt();
  
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =6;
if (Screen==2){
tft.setFontScale(1);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.setCursor(xpos+ (radius * Gnum) + distance+30,ypos+40);tft.print("input6");tft.setFontScale(1);tft.setCursor(xpos+ (radius * Gnum) + distance+Cntr,ypos+80);tft.print(reading);tft.print("   ");
tft.ringMeter(reading,-10,2000,xpos+ (radius * Gnum) + distance,ypos,radius,"none",5,tft.htmlTo565(0x848482),110,10);
}
tft.setFontScale(0); 
   ///Fpop=part2;
    ///Serial.println(part2);
  }
  if (part1 == "36")
    {

    String raw_CMD;
   //weather=part2;

  }
///////////////////////////end of WU//////////////
//////////////////////////enviro/////////////////
if (part1 == "37")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }

  if (part1 == "38")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
if (part1 == "39")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
if (part1 == "40")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
  if (part1 == "41")
    {

   String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;

  }

if (part1 == "42")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }

  if (part1 == "43")
    {
    String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;;
  }
if (part1 == "44")
    {
   String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;;
  }
if (part1 == "45")
    {
  String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;;
  }
  if (part1 == "46")
    {
String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;

  }

if (part1 == "47")
    {
   String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }

  if (part1 == "48")
    {
   String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
if (part1 == "49")
    {
  String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
if (part1 == "50")
    {
   String raw_CMD;
    float input = part2.toFloat();
    raw_CMD=input;
  }
if (part1 == "51")
    {
    String raw_CMD;
   //Fday=part2;
    //Serial.println(part2);
  }
if (part1 == "52")
    {
    String raw_CMD;
   //Fpop=part2;
   // Serial.println(part2);
  }








 /* 
if (Screen==1){
tft.setFontScale(0);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 40);tft.print(Fhigh);//tft.setFontScale(0);tft.print(" C ");tft.setFontScale(0);tft.setCursor(430, 40);tft.print("High");
 tft.setFontScale(0);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 70);tft.print(Flow);//tft.setFontScale(0);tft.print(" C ");tft.setFontScale(0);tft.setCursor(430, 70);tft.print("Low");
 tft.setFontScale(0);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(430, 10);tft.print(Fday);//tft.setCursor(430, 10);tft.setFontScale(1);tft.print("");
  tft.setFontScale(0);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(505, 100);tft.print(Fpop);//tft.setFontScale(0);tft.print(" % ");tft.setFontScale(0);tft.setCursor(430, 100);tft.print("PoP ");
 tft.setFontScale(0);}*/
 
 if(Screen==6){
  tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(320, 0);tft.print(weather);tft.setFontScale(1);tft.setCursor(0, 0);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print("TODAY'S FORECAST - ");
 tft.setFontScale(0);
 
 }
 if (LScreen ==2) Thermo(ext5, ext6, ext7,ext8); 
 if (LScreen ==3) Zone1(ext18, ext19, ext20,ext21,ext10, ext11, ext12,ext13); 
 if (LScreen ==4) Zone2(ext22, ext23, ext24,ext25, ext14, ext15, ext16,ext17);
if (RScreen == 1) Screen_Graph1();
if (RScreen == 2) Screen_Graph2();
if (RScreen == 3) Screen_Graph3();
if (RScreen == 4) Screen_Graph4();
}

void Screen_Graph1(){
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    // ivT = 60; /// time interval 1 seconds 60 min ets
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext2;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, 0, 7000, 1000, "kw", "hrs", "Solar/Grid", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
     y= ext1;
     Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 7000, 1000, "kw", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);
//tft.fillRect(320,200,460,40,RA8875_BLACK);
//utft.fillRect(320,160,460,40,RA8875_BLACK); 
  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }

void Screen_Graph2(){
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    // ivT = 60; /// time interval 1 seconds 60 min ets
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext3;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, -40, 40, 10, "", "hrs", "Outside Temp", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
    // y= ext1;
     //Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 7000, 1000, "kw", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);
//tft.fillRect(320,200,460,40,RA8875_BLACK);
//utft.fillRect(320,160,460,40,RA8875_BLACK); 
  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }  
  void Screen_Graph3(){
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    // ivT = 60; /// time interval 1 seconds 60 min ets
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext1;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, 0, 3000, 500, "kw", "hrs", "Solar", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
     //y= ext1;
    // Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 7000, 1000, "kw", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);
//tft.fillRect(320,200,460,40,RA8875_BLACK);
//utft.fillRect(320,160,460,40,RA8875_BLACK); 
  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }
    void Screen_Graph4(){
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    // ivT = 60; /// time interval 1 seconds 60 min ets
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext4;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, 0, 2000, 300, "kw", "hrs", "Diverter", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
    // y= ext1;
    // Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 7000, 1000, "kw", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);
//tft.fillRect(320,200,460,40,RA8875_BLACK);
//utft.fillRect(320,160,460,40,RA8875_BLACK); 
  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }    

//////////// Pie Chart ///////////
/////////////////////////////////

int screenPie(int inp1,int inp2 ,int inp3)
{
  const uint16_t x = 89;
  const uint16_t y = 219;
  const uint16_t radius = 80;
  //Serial.println("sgraph");
  //Serial.println(inp1);
 // Serial.println(inp2);
  //Serial.println("Egraph");
  if (inp1 <0){inp1 =0;}
  if (inp2 <0) {inp2 =0;}
  if (inp3 <10){inp3 = 0;}
  float vx = inp1+inp2 +inp3;
  float t1= inp1/vx;
  float t2 = inp2/vx;
  float t3 = inp3/vx;
int d1 = 360*t1;
int d2 = d1+(360*t2);
int d3 = 360*t3;
int t1a = t1;
int t2a =t2;
int t3a = t3;
int t1b;
int t2b;
int t3b;
 // tft.clearScreen();
  tft.drawArc(x , y , radius, radius, 0, d1, tft.Color565(198, 255, 13));
  tft.drawArc(x , y , radius , radius , d1,d2 , tft.Color565(255, 0, 54));
  tft.drawArc(x , y , radius, radius, d2, 360, tft.Color565(0, 255, 241));

  //tft.fillRect(180,180,10,10,RA8875_BLUE);
  tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(180, 150);tft.print(100*t3);tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 130);tft.print("DIVERTER");
 // tft.fillRect(180,240,10,10,RA8875_RED);
  tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(180, 210);tft.print(100*t2);;tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 190);tft.print("GRID");
 // tft.fillRect(180,280,10,10,RA8875_GREEN);
    tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(180, 270);tft.print(100*t1);tft.print("% ");tft.setFontScale(0);tft.setCursor(180, 250);tft.print("SOLAR");
 tft.setFontScale(3);tft.setTextColor(LTBLUE, RA8875_BLACK);tft.setCursor(90, 350);tft.print(inp1+inp2);tft.print(" ");tft.setFontScale(1);tft.setCursor(90, 310);tft.print("TOTAL");
  
  t1b = ext1;
  t2b =ext2;
  t3b = t3a;
  
  tft.setFontScale(0);
}

///////////Vertical Charts///////////////
/////////////////////////////////////////

void DrawBarChartV(RA8875 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{

  double stepval, range;
  double my, level;
  double i, data;
  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  if (redraw == true) {
    redraw = false;

    d.drawRect(x - 1, y - h - 1, w + 2, h + 2, bordercolor);
    d.setTextColor(textcolor, backcolor);
    //d.setFontScale(1);
    d.setCursor(x , y + 10);
    d.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      d.drawFastHLine(x + w + 1, my,  5, textcolor);
      // draw lables
    //  d.setFontScale(0);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  d.fillRect(x, y - h, w, h - level,  voidcolor);
  d.fillRect(x, y - level, w,  level, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
  //d.setFontScale(1);
  d.setCursor(x , y - h - 23);
  d.println(Format(curval, dig, dec));

}


//////////////Horizontal Charts////////////
//////////////////////////////////////////

void DrawBarChartH(RA8875 & d, double x , double y , double w, double h , double loval , double hival , double inc , double curval ,  int dig , int dec, unsigned int barcolor, unsigned int voidcolor, unsigned int bordercolor, unsigned int textcolor, unsigned int backcolor, String label, boolean & redraw)
{
  double stepval, range;
  double mx, level;
  double i, data;

  // draw the border, scale, and label once
  // avoid doing this on every update to minimize flicker
  // draw the border and scale
  if (redraw == true) {
    redraw = false;
    d.drawRect(x , y , w, h, bordercolor);
    d.setTextColor(textcolor, backcolor);
   // d.setFontScale(1);
    d.setCursor(x , y - 20);
    d.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      d.drawFastVLine(i + x , y + h + 1,  5, textcolor);
      // draw lables
     // d.setFontScale(0);
      d.setTextColor(textcolor, backcolor);
      d.setCursor(i + x , y + h + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      d.println(Format(data, dig, dec));
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  d.fillRect(x + level + 1, y + 1, w - level - 2, h - 2,  voidcolor);
  d.fillRect(x + 1, y + 1 , level - 1,  h - 2, barcolor);
  // write the current value
  d.setTextColor(textcolor, backcolor);
 // d.setFontScale(1);
  d.setCursor(x + w + 10 , y + 5);
  d.println(Format(curval, dig, dec));
}


String Format(double val, int dec, int dig ) {
  int addpad = 0;
  char sbuf[20];
  String condata = (dtostrf(val, dec, dig, sbuf));


  int slen = condata.length();
  for ( addpad = 1; addpad <= dec + dig - slen; addpad++) {
    condata = " " + condata;
  }
  return (condata);

}

///////////////Graphs /////////////////
//////////////////////////////////////

void Graph(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
//if (redraw1==true){redraw=true;}
  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
     //int strip =(i/.66666666666666666666);
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}
void Graph2(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
//if (redraw1==true){redraw=true;}
  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox2 = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy2 = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
     //int strip =(i/.66666666666666666666);
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox2, oy2, x, y, pcolor);
  d.drawLine(ox2, oy2 + 1, x, y + 1, pcolor);
  d.drawLine(ox2, oy2 - 1, x, y - 1, pcolor);
  ox2 = x;
  oy2= y;

}

