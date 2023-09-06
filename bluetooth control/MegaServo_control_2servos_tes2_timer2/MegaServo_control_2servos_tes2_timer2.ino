#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

#include "MegaServo.h"

MegaServo megaServo;
MegaServo megaServo2;




void setup()
{
  Serial.begin(115200);
    
  megaServo.attach(7, 8, 5, A4);
    megaServo2.attach(9, 10, 6, A4);

  megaServo.write(90);
    megaServo2.write(90);

      myservo.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  if (Serial.available())
  {
    int angle = Serial.parseInt();
    
    Serial.println(angle);
    
    megaServo.write(angle);
  }


  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

  
}
