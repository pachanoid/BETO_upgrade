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
}

void loop()
{
  if (Serial.available())
  {
    int angle = Serial.parseInt();
    
    Serial.println(angle);
    
    megaServo.write(angle);
  }
}
