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
  // Yazı tipi boyutunu ayarla
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);

  // Ekranı temizle
  display.clearDisplay();

  // Yazı tipi boyutunu ayarla
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // LDR değerini ekrana yaz
  display.setCursor(0, 0);
  display.print("LDR Degeri: ");
  display.println(ldrValue);

  // Aydınlığa göre hava durumu mesajını ekrana yaz
  if (ldrValue > 100) {
    display.setCursor(0, 20);
    display.println("Hava Acik");
  } else if (ldrValue < 99) {
    display.setCursor(0, 20);
    display.println("Hava Kapali");
  }
  
  // Ekranda göster
  display.display();

  // Bekleme
  delay(1000);
}