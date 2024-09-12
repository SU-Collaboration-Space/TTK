#include <Wire.h>                   // I2C bağlantı kütüphanesini yükle
#include <Adafruit_GFX.h>           // Ekrana şekil çizimi için kütüphane yükle
#include <Adafruit_SSD1306.h>       // Ekrana yazı yazma için kütüphane yükle

#define SCREEN_WIDTH 128            // Ekran genişiliğini belirle
#define SCREEN_HEIGHT 64            // Ekran yüksekliğini belirle

// SDA ve SCL pinlerini tanımla
#define SDA_PIN 12
#define SCL_PIN 14

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
  
  // Büyük harflerle "TTK-2024" metnini ekrana yaz
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("TTK-2024");
  
  // Ekranda göster
  display.display();
}

void loop() {
  // "TTK-2024" metnini yanıp sönme efekti ile göster
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);
}
