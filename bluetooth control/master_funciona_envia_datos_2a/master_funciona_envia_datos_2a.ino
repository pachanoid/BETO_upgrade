
//master

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
  Serial.begin(9600);
  Serial.println("ENTER Commands:");
  ArduinoSlave.begin(9600);
}
void loop(){
  
  //read command from keypad

readkeypad();

  
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
