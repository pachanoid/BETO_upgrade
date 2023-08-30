
//master

// SE INCLUYE LIBRERÍAS DE LCD
#include <Wire.h> 

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
//#define logo2_width 30
//#define logo2_height 27
//I2C SSD1306 128x32 (search U8g2 examples for other display)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
int dato=0;





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
//String keya;


void setup(){
  u8g2.begin();
  Serial.begin(9600);
  Serial.println("ENTER Commands:");
  ArduinoSlave.begin(9600);
}
void loop(){
  
  //read command from keypad

readkeypad();
oled();
  
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
  keya=key;
  if (key != NO_KEY){//SI ES DIFERENTE DE NULO
    //IMPIRME EN MONITOR SERIE Y EN LCD EL VALOR DE LA TECLA
    Serial.println(key);   
    ArduinoSlave.print(key);
    key="";
  }    
}
void oled(){


  u8g2.firstPage();
  do {
    
 

   
   u8g2.setFont(u8g2_font_helvB14_tr); // size ncenB08   


   

    
    u8g2.setCursor(0, 15);
    u8g2.print(keya);
    
  
} while ( u8g2.nextPage() );
  delay(100);

    
  }
