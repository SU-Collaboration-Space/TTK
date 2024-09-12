#include <Servo.h>                  // Servo için kütüphane yükle

#define LDR_PIN A0                  // LDR'nin bağlı olduğu pini belirle
#define SERVO_PIN 5                 // Servonun bağlı olduğu pini belirle

Servo servo;                        // Servo için bir obje oluştur

void setup() {
  Serial.begin(9600);

  servo.attach(SERVO_PIN);          // Servoyu bağla
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  
  // LDR değeri 85'in altındaysa servo motoru 10 dereceye hızlı bir şekilde hareket ettir
  if (ldrValue < 125) {
    servo.write(40);
  } 
  // LDR değeri 86 veya daha yüksekse servo motoru 0 dereceye getir
  else {
    servo.write(0);
  }
  
  // Bekleme
  delay(100);
}

