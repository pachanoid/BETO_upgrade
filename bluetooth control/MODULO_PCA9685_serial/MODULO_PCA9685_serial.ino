#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°

String leido = "";


void setup() {
  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms

 Serial.begin(9600);
  Serial.println("Introduce una cadena de texto: ");
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,pos0, pos180);
  servos.setPWM(n_servo, 0, duty);  
}

void loop() {


  if (Serial.available() > 0) {
    leido = ""; //vacio lo leido
    do {
      char caracter_leido;
      delay(5);
      caracter_leido = Serial.read();
      leido += caracter_leido;
    }  while (Serial.available() > 0);

    Serial.println("He leido la cadena: \"" + leido + "\"");

    if (leido.startsWith("e")){
    //if (leido == "enciende")
      digitalWrite(LED_BUILTIN, HIGH);
    setServo(0,10);
    setServo(1,10);
      
    }
    if (leido.startsWith("a")){
    //if (leido == "apaga")
      digitalWrite(LED_BUILTIN, LOW);

    setServo(0,170);
    setServo(1,170);

  }
    
e}
}
