
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//#include <JsonListener.h>
//#include "WundergroundForecast.h"
String command; // serial input capture string

/**
 * Wunderground Settings

const String  WUNDERGRROUND_API_KEY = "e01e78beb97907b8";
const String  WUNDERGR_UND_STATE_OR_COUNTRY = "CAN";
const String  WUNDERGR_UND_CITY = "ARBORG";
const String  WUNDERGRROUND_LANGUAGE = "EN";
const boolean IS_METRIC = true;
const boolean USE_PM = false;
int startW =0;
// initiate the WundergoundClient
WundergroundForecast wunderground(IS_METRIC);
*/
uint32_t runTime = -99999;

//--topics
String input1 = "/energy/invert";
String input2 = "/temp/28ff48a470165ae";
String input3 = "/enviro/humid";
String input4 = "/wind";
String input5 = "/grid";
String input6 = "/energy/divert";
///thermostat  radial dial settings
String input7 = "/temp/28ff4f3c8c163e9";
String input8 = "/switch/SW1/Tset";
String input9 = "/switch/SW1/Theat";
String input10 = "/switch/SW1/Tfan";
String input11 = "/switch/failure/thermo";
// thermostat Zone settings
String input12 = "/switch/SW1/Tset1";
String input13 = "/switch/SW1/Tset2";
String input14 = "/switch/SW1/Tset3";
String input15 = "/switch/SW1/Tset4";
String input16 = "/switch/SW1/Tset5";
String input17 = "/switch/SW1/Tset6";
String input18 = "/switch/SW1/Tset7";
String input19 = "/switch/SW1/Tset8";
//Thermostat Zone sensors
String input20 = "/temp/28ff5d370164db";/// edit these to match your sensors ROM IDs
String input21 = "/temp/28ffb7da8b1634b";
String input22 = "/temp/28ff49a470165fe";
String input23 = "/temp/28ff38a4701631d";
String input24 = "/temp/28ff5d270164db";
String input25 = "/temp/28ff5d170164db";
String input26 = "/temp/28ff5d770164db";
String input27 = "/temp/28ff4f9c8c163e9";
String input28 = "/temp/28ff5d370364db";
//weather underground setting if using Mqtt sends from router otherwise can be used for other sensors 
String input29 = "/energy/input1";
String input30 = "/energy/input2";
String input31 = "/energy/input3";
String input32 = "/energy/input4";
String input33 = "/energy/input5";
String input34 = "/energy/input6";
String input35 = "/energy.input7";
String input36 = "/energy/input8";
///Other user installed sensors
String input37 = "/enviro/sensor1";
String input38 = "/enviro/sensor2";
String input39 = "/enviro/sensor3";
String input40 = "/enviro/sensor4";
String input41 = "/enviro/sensor5";
String input42 = "/enviro/sensor6";
String input43 = "/enviro/sensor7";
String input44 = "/enviro/sensor8";
String input45 = "/enviro/sensor9";
String input46 = "/enviro/sensor10";
String input47 = "enviro/sensor11";
String input48 = "/enviro/sensor12";
String input49 = "/enviro/sensor13";
String input50 = "/enviro/sensor14";
// Update these with values suitable for your network.

const char* ssid = "IOT";
const char* password = "";
const char* mqtt_server = "192.168.168.150";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 // weather(); // built in weather underground 
}
/*
void weather(){
   uint8_t maxForecasts = 1;
  WGForecast forecasts[maxForecasts];
  wunderground.updateForecast(forecasts, maxForecasts, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGR_UND_STATE_OR_COUNTRY, WUNDERGR_UND_CITY);

  for (int i = 0; i < maxForecasts; i++) {

    Serial.println("cmd_24(" + forecasts[i].forecastIcon + ")");//Serial.println(")");
    delay(150);
    //Serial.println("getForecastTitle: " + forecasts[i].forecastTitle);
   Serial.println("cmd_22(" + forecasts[i].forecastLowTemp + ")");//Serial.println(")");
   delay(150);
   Serial.println("cmd_23(" + forecasts[i].forecastHighTemp + ")");//Serial.println(")");
   delay(150);
   //Serial.print("cmd_26(" + forecasts[i].forecastDay);Serial.println(")");
   // Serial.println("getForecastMonth: " + forecasts[i].forecastMonth);
    Serial.println("cmd_21(" + forecasts[i].forecastText + ")");//;Serial.println(")");
    delay(150);
   Serial.println("cmd_25(" + forecasts[i].PoP + ")");//Serial.println(")");
   delay(150);
   Serial.println("cmd_0(DATA ERROR)");
  }

delay(1000);
}
*/
void setup_wifi() {
WiFi.hostname("espTFTScreen2");
  delay(10);
WiFi.mode(WIFI_STA);   
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {


if (input1 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
  Serial.print("cmd_1("); Serial.print(inString); Serial.println(")");
  }
if (input2 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
   Serial.print("cmd_2("); Serial.print(inString); Serial.println(")");
} 
 if (input3 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
   Serial.print("cmd_3("); Serial.print(inString); Serial.println(")");
  }
if (input4 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_4("); Serial.print(inString); Serial.println(")");  
} 
if (input5 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);     
  }
 Serial.print("cmd_5("); Serial.print(inString); Serial.println(")"); 
} 
//---reseved for later use 

if (input6 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);   
  }
  Serial.print("cmd_6("); Serial.print(inString); Serial.println(")");
  }
if (input7 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);      
  }
   Serial.print("cmd_7("); Serial.print(inString); Serial.println(")");
} 
 if (input8 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);    
  }
  Serial.print("cmd_8("); Serial.print(inString); Serial.println(")");
  }
if (input9 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_9("); Serial.print(inString); Serial.println(")");    
} 
if (input10 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_10("); Serial.print(inString); Serial.println(")");
      
} 

if (input11 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
     Serial.print("cmd_11("); Serial.print(inString); Serial.println(")");
  }
  }
if (input12 == topic){
String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_12("); Serial.print(inString); Serial.println(")");
} 
 if (input13 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_13("); Serial.print(inString); Serial.println(")");
  }
if (input14 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
     Serial.print("cmd_14("); Serial.print(inString); Serial.println(")");
} 
if (input15 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_15("); Serial.print(inString); Serial.println(")");
} 

 if (input16 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_16("); Serial.print(inString); Serial.println(")");
  }
if (input17 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_17("); Serial.print(inString); Serial.println(")");
} 
 if (input18 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_18("); Serial.print(inString); Serial.println(")");
  }
if (input19 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_19("); Serial.print(inString); Serial.println(")");
} 
if (input20 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_20("); Serial.print(inString); Serial.println(")");
      
} 

if (input21 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
  Serial.print("cmd_21("); Serial.print(inString); Serial.println(")");
  }
if (input22 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
   Serial.print("cmd_22("); Serial.print(inString); Serial.println(")");
} 
 if (input23 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
   Serial.print("cmd_23("); Serial.print(inString); Serial.println(")");
  }
if (input24 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_24("); Serial.print(inString); Serial.println(")");  
} 
if (input25 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);     
  }
 Serial.print("cmd_25("); Serial.print(inString); Serial.println(")"); 
} 
//---reseved for later use 

if (input26 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);   
  }
  Serial.print("cmd_26("); Serial.print(inString); Serial.println(")");
  }
if (input27 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);      
  }
   Serial.print("cmd_27("); Serial.print(inString); Serial.println(")");
} 
 if (input28 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);    
  }
  Serial.print("cmd_28("); Serial.print(inString); Serial.println(")");
  }
if (input29 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_29("); Serial.print(inString); Serial.println(")");    
} 
if (input30 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_30("); Serial.print(inString); Serial.println(")");
      
} 

if (input31 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
     Serial.print("cmd_31("); Serial.print(inString); Serial.println(")");
  }
  }
if (input32 == topic){
String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_32("); Serial.print(inString); Serial.println(")");
} 
 if (input33 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_33("); Serial.print(inString); Serial.println(")");
  }
if (input34 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
     Serial.print("cmd_34("); Serial.print(inString); Serial.println(")");
} 
if (input35 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_35("); Serial.print(inString); Serial.println(")");
} 

 if (input36 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_36("); Serial.print(inString); Serial.println(")");
  }
if (input37 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_37("); Serial.print(inString); Serial.println(")");
} 
 if (input38 == topic){
  String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
     Serial.print("cmd_38("); Serial.print(inString); Serial.println(")");
  }
if (input39 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_39("); Serial.print(inString); Serial.println(")");
} 
if (input40 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_40("); Serial.print(inString); Serial.println(")");
      
} 

if (input41 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
  Serial.print("cmd_41("); Serial.print(inString); Serial.println(")");
  }
if (input42 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
   Serial.print("cmd_42("); Serial.print(inString); Serial.println(")");
} 
 if (input43 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
   Serial.print("cmd_43("); Serial.print(inString); Serial.println(")");
  }
if (input44 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_44("); Serial.print(inString); Serial.println(")");  
} 
if (input45 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);     
  }
 Serial.print("cmd_45("); Serial.print(inString); Serial.println(")"); 
} 
//---reseved for later use 

if (input46 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);   
  }
  Serial.print("cmd_46("); Serial.print(inString); Serial.println(")");
  }
if (input47 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);      
  }
   Serial.print("cmd_47("); Serial.print(inString); Serial.println(")");
} 
 if (input48 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);    
  }
  Serial.print("cmd_48("); Serial.print(inString); Serial.println(")");
  }
if (input49 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_49("); Serial.print(inString); Serial.println(")");    
} 
if (input50 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
     Serial.print("cmd_50("); Serial.print(inString); Serial.println(")");
      
} 
/// if adding more sensor strings edit publish or remove publish and error commands below for switches 

 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("LCDClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe maxium 7 other wise issues arise
      client.subscribe("/grid");
      client.subscribe("/wind");
      client.subscribe("/temp/#");
      client.subscribe("/enviro/#");
      client.subscribe("/switch/#");
      client.subscribe("/energy/#");
      client.subscribe("/WU/#");

     
     
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}
void loop() {
if(WiFi.status() != WL_CONNECTED) {setup_wifi();}
  if (!client.connected()) {
    reconnect();
 }
  client.loop();

   if(Serial.available())
   {
      char c = Serial.read();
    
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

}


void parseCommand(String com)
{

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  //int test = part1.toInt();
 // Serial.print(part1);
  //Serial.println("#");
  part2 = com.substring(com.indexOf("(")+1);
  //Serial.println(part2);

//--input 
//////////////////////  

  if (part1 == "100")
  {
    String raw_CMD = part2;
         if (client.connected()){
    if (client.publish("/switch/SW1", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }
  if (part1== "101")
    {
      //Serial.println(part2);
     String raw_CMD = part2;
            if (client.connected()){
     if (client.publish("/switch/SW2", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
  }

 if (part1 == "102")
    {
     // Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
     if (client.publish("/switch/SW3", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
  }

  if (part1 == "103")
  {
    String raw_CMD = part2;
    if (client.connected()){
    if (client.publish("/switch/SW4", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
       }
  if (part1== "104")
    {
     // Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
     if (client.publish("/switch/SW5", (char*) raw_CMD.c_str())) {
     Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }

    if (part1== "105")
    {
      //Serial.println(part2);
      String raw_CMD = part2;
   if (client.connected()){
     if (client.publish("/switch/SW6", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
   }
    }
    if (part1== "106")
    {
     //Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
  
    if (client.publish("/switch/SW7", (char*) raw_CMD.c_str())) {
       Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }
}
