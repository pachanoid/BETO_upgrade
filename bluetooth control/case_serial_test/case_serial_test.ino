char x=50;


char c;
String msg;

void setup(){  
    
  Serial.begin(9600);
}
void loop(){
  switch (x) {
    case 20:
      Serial.println("Vale 20 exactamente");
      break;
    case 50:
      Serial.println("Vale 50 exactamente");
      break;
    default:
      Serial.println("No vale ninguna de los valores anteriores");
  }
  delay(10);
}


void readSerialPort(){
 while (Serial.available()) {
   delay(10);
   if (Serial.available() >0) {
      c = Serial.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
     
  
   }
 }
 Serial.flush();
}
