#include <Wire.h>                   // I2C bağlantı kütüphanesini yükle
#include <Adafruit_GFX.h>           // Ekrana şekil çizimi için kütüphane yükle
#include <Adafruit_SSD1306.h>       // Ekrana yazı yazma için kütüphane yükle
#include <Servo.h>                  // Servo için kütüphane yükle

#define SCREEN_WIDTH 128            // Ekran genişiliğini belirle
#define SCREEN_HEIGHT 64            // Ekran yüksekliğini belirle

// SDA ve SCL pinlerini tanımla
#define SDA_PIN 12
#define SCL_PIN 14

// Servonun bağlı olduğu pini belirle
#define SERVO_PIN 5

// Ekran objesini oluştur
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Servo objesi oluştur
Servo servo;

void setup() {
  // Loglama için serial monitoru başlat
  Serial.begin(9600);
  
  // I2C bağlantısını başlat
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // OLED ekranını başlat
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 başlatılamadı!"));
    while(true);
  }

  // Servo ile servo objesi üzerinden bağlantı kur
  servo.attach(SERVO_PIN);

  // Ekranı temizle
  display.clearDisplay();
}

void loop() {
  // Servo motoru hızlı bir şekilde hareket ettir
  for (int angle = 0; angle <= 180; angle += 10) {
    servo.write(angle);
    delay(50);

    // OLED ekranına çubuk şeklinde bir ibre ve servo açısı yaz
    display.clearDisplay();
    int barWidth = map(angle, 0, 180, 0, SCREEN_WIDTH);
    display.fillRect(0, SCREEN_HEIGHT / 2 - 4, barWidth, 8, SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Servo Aci: ");
    display.println(angle);
    display.display();
  }

  // Ters yönde servo motoru hızlı bir şekilde hareket ettir
  for (int angle = 180; angle >= 0; angle -= 10) {
    servo.write(angle);
    delay(50);

    // OLED ekranına çubuk şeklinde bir ibre ve servo açısı yaz
    display.clearDisplay();
    int barWidth = map(angle, 0, 180, 0, SCREEN_WIDTH);
    display.fillRect(0, SCREEN_HEIGHT / 2 - 4, barWidth, 8, SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Servo Aci: ");
    display.println(angle);
    display.display();
  }
}
