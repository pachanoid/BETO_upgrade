
//Slaver
/*
 * D4 - Clockwise M2
D5 - Enabler M1
D6 - Enabler M2
D7 - Clockwise M1
D8 - Counter clockwise M1
D9 - Counter clockwise M2 
 * 
 */


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
String leido="";



//biceps derecho rango 120 <> 30
//out 1 rojo out2 amarillo
// potenciometro rojo >> grnd---- potenciometro negro 5v 
#include "MegaServo.h"
MegaServo megaServo;
MegaServo megaServo2;
int angle;





void setup(){
  
    
    megaServo.attach(7, 8, 5, A3);  // se cambio de A4 a A3 5>enable motor1 l298A D7 - Clockwise D8 - Counter clockwise M1
    megaServo.write(90);
 
 megaServo2.attach(9, 10, 6, A2);  //  feedback A2 a A3 5>enable motor1 l298A D7 - Clockwise D8 - Counter clockwise M2
    megaServo2.write(90);

    
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  
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
//leecaracter();



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

  Serial.println("He leido la cadena: \"" + leido + "\"");

    //Biceps brazo izquierdo
    if (msg.startsWith("*")){
    //if (leido == "enciende")
      //digitalWrite(LED_BUILTIN, HIGH);
      megaServo.write(120);
     //angle=120;
     //servo();
      Serial.println("megaservo 120");
    }
    
    if (msg.startsWith("-")){
    //if (leido == "apaga")
      //digitalWrite(LED_BUILTIN, LOW);
      megaServo.write(30);
      //angle=30;
     //servo();
  Serial.println("megaservo 30");
    }

  
   //biceps brazo derecho
   
   if (msg.startsWith("6")){
    //if (leido == "enciende")
      digitalWrite(LED_BUILTIN, HIGH);
      megaServo2.write(120);
     //angle=120;
     //servo();
      Serial.println("megaservo2 120");
    }
    
    if (msg.startsWith("9")){
    //if (leido == "apaga")
      digitalWrite(LED_BUILTIN, LOW);
      megaServo2.write(30);
      //angle=30;
     //servo();
  Serial.println("megaservo2 30");

  

   
 }
 ArduinoMaster.flush();
}
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

void servo(){

 //int angle = Serial.parseInt();
    
    Serial.println(angle);
    
    megaServo.write(angle);
  
}
