
//Slaver



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <Arduino.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);






#include <SoftwareSerial.h>
SoftwareSerial ArduinoMaster(2,3);
String msg;




void setup(){
  Serial.begin(9600);
  ArduinoMaster.begin(9600);

 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
}



void loop(){
  readSerialPort();
oled();




  // Send answer to master
  if(msg!=""){
    Serial.print("Master sent : " );
    Serial.println(msg);
    ArduinoMaster.print(msg);
    msg="";
  }
}
void readSerialPort(){
 while (ArduinoMaster.available()) {
   delay(10);
   if (ArduinoMaster.available() >0) {
     char c = ArduinoMaster.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
     
  display.clearDisplay();
   }
 }
 ArduinoMaster.flush();
}


void oled(){
 // display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(msg);
  display.display(); 
  
}
