#include <Wire.h>                   // I2C bağlantı kütüphanesini yükle
#include <Adafruit_GFX.h>           // Ekrana şekil çizimi için kütüphane yükle
#include <Adafruit_SSD1306.h>       // Ekrana yazı yazma için kütüphane yükle

#define SCREEN_WIDTH 128            // Ekran genişiliğini belirle
#define SCREEN_HEIGHT 64            // Ekran yüksekliğini belirle

// SDA ve SCL pinlerini tanımla
#define SDA_PIN 12
#define SCL_PIN 14

// Butonun bağlı olduğu pini belirle
#define BUTTON_PIN 2

// OLED ekranını başlat
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int counter = 0;
int lastButtonState = HIGH; // Buton durumu

void setup() {
  // Serial loglama için monitoru başlat
  Serial.begin(9600);

  // I2C bağlantısını başlat
  Wire.begin(OLED_SDA, OLED_SCL);

  // OLED ekranını başlat
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 başlatılamadı!"));
    while (true);
  }

  // Butonun bağlı olduğu pinin çalışma modunu belirle
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.clearDisplay();                 // Ekranı temizle
  display.setTextSize(2);                 // Yazı boyutunu 2 olarak belirle
  display.setTextColor(SSD1306_WHITE);    // Yazı rengini belirle
}

void loop() {
  // Buton durumunu oku ve buttonState adlı değişkene yaz
  int buttonState = digitalRead(BUTTON_PIN);

  display.clearDisplay();                 // Ekranı temizle
  display.setCursor(0, 0);                // Yazı başlangıcını sol üst köşeye çek

  // buton basıldığında sayacı artır
  if (buttonState == LOW && lastButtonState == HIGH) {
    counter++;
  }

  if (buttonState == LOW) {
    display.print("ACIK..");              // buton basıldığında ekrana yazılacak metin
  } else {
    display.print("KAPALI");              // buton basılmadığında ekrana yazılacak metin
  }

  display.print(" ");                     // ekrana yazılacak metnin sonuna boşluk ekle
  display.print(counter);                 // ekrana yazılacak metnin sonuna sayaç değişkeninin tuttuğu rakamı ekle

  display.display();                      // ekrana yazılacak metni göster

  lastButtonState = buttonState;          // Buton durumunu güncelle

  delay(100);                             // buton durumunun sağlıklı okunabilmesi için 100ms'lik gecikme ekle
}
