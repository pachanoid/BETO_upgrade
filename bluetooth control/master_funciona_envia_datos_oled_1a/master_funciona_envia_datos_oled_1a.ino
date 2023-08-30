
//master

// SE INCLUYE LIBRERÍAS DE LCD
#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <Arduino.h>
#include <SPI.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#include <SoftwareSerial.h>
SoftwareSerial ArduinoSlave(10,11); //RX, TX arduino 


//SE INCLUYE LIBRERÍA DE TECLADO 
#include <Keypad.h>
const byte ROWS = 4;// Filas
const byte COLS = 4;//Columnas
char keya;
//SE DECLARA ARRAY CON SIMBOLOS CORRESPONDIENTES
char keys[ROWS][COLS] = {//Simbolos
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'=','0','.','/'}
};
// SE DECLARA PINES DIGITALES A UTILIZAR
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
//SE CREA Y CONFIGURA OBJETO KEYPAD 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String answer;
String msg;
//char keya;


void setup(){
  //u8g2.begin();
  Serial.begin(9600);
  Serial.println("ENTER Commands:");
  ArduinoSlave.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}
void loop(){
  
  //read command from keypad

readkeypad();
//oled();
  
  //Read command from monitor
  readSerialPort();
  //Read answer from slave
   while (ArduinoSlave.available()) {
   delay(10);
   if (ArduinoSlave.available() >0) {
     char c = ArduinoSlave.read();  //gets one byte from serial buffer
     answer += c; //makes the string readString
   }
 }
  //Send data to slave
  if(msg!=""){
    Serial.print("Master sent : ");
    Serial.println(msg);
    ArduinoSlave.print(msg);
    msg="";
//display.clearDisplay();
  // oled();
  }
  //Send answer to monitor
  if(answer!=""){
    Serial.print("Slave recieved : ");
    Serial.println(answer);
    answer="";
  }
}
void readSerialPort(){
 while (Serial.available()) {
   delay(10);
   if (Serial.available() >0) {
     char c = Serial.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
     
   }
 }
 Serial.flush();
}

/*void sendkeya(){

keya +=c;
  ArduinoSlave.print(keya);
    keya=""; 
}
*/

void readkeypad(){

   // SE OBTIENE EL VALOR DE LA TECLA OPRIMIDA
  char key = keypad.getKey();
  //keya=key;
  if (key != NO_KEY){//SI ES DIFERENTE DE NULO
    //IMPIRME EN MONITOR SERIE Y EN LCD EL VALOR DE LA TECLA
    Serial.println(key);   
    ArduinoSlave.print(key);
  


display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
    //display.println("test");
  display.println(key);
  display.display(); 

  key="";

    
  }    
}




void oled(){
 

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
    //display.println("test");
  display.println(msg);
  display.display(); 


  
}




  
