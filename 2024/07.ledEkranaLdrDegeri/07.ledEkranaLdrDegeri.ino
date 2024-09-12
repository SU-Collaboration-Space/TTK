#include <Wire.h>                   // I2C bağlantı kütüphanesini yükle
#include <Adafruit_GFX.h>           // Ekrana şekil çizimi için kütüphane yükle
#include <Adafruit_SSD1306.h>       // Ekrana yazı yazma için kütüphane yükle

#define SCREEN_WIDTH 128            // Ekran genişiliğini belirle
#define SCREEN_HEIGHT 64            // Ekran yüksekliğini belirle

// SDA ve SCL pinlerini tanımla
#define SDA_PIN 12
#define SCL_PIN 14

// LDR pinini tanımla
#define LDR_PIN A0                  // Analog pinler daima input olduğundan, setup'ta pinMode ile çalışma türünü belirtmeye gerek kalmaz

// OLED ekranını başlat
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // I2C bağlantısını başlat
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // OLED ekranını başlat
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 başlatılamadı!"));
    while(true);
  }
  
  // Ekranı temizle
  display.clearDisplay();
}

void loop() {
  // LDR değerini oku
  int ldrValue = analogRead(LDR_PIN);
  
  // Ekranı temizle
  display.clearDisplay();
  
  // LDR değerini ekrana yaz
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("LDR Degeri: ");
  display.println(ldrValue);
  
  // Ekranda göster
  display.display();

  // Bekleme
  delay(1000);
}
