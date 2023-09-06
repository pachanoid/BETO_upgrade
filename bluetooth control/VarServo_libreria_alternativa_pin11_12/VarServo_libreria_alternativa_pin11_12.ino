#include <VarSpeedServo.h> 

// create servo objects
VarSpeedServo myservo1;
VarSpeedServo myservo2;
 
void setup() {
  myservo1.attach(11);
  myservo2.attach(12);
} 
 
void loop() {
  
  int LEF = 0;
  int RIG = 180;
  
  int SPEED1 = 160;
  int SPEED2 = 100;
  
  myservo1.write(LEF, SPEED1);     
  myservo2.write(LEF, SPEED2);
  myservo1.wait(); // wait for servo 1 to finish
  myservo2.wait();  // wait for servo 2 to finish
    
  myservo1.write(RIG, SPEED1);     
  myservo1.wait(); // wait for S1
  
  myservo1.write(LEF, SPEED1); 
  myservo2.write(RIG, SPEED2);  
  myservo1.wait();
  myservo2.wait();    
        
  myservo1.write(RIG, SPEED1);     
  myservo1.wait();
      
  delay(1000);
  
}
