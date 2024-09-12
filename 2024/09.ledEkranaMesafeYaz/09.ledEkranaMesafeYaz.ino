#include <Wire.h>                   // I2C bağlantı kütüphanesini yükle
#include <Adafruit_GFX.h>           // Ekrana şekil çizimi için kütüphane yükle
#include <Adafruit_SSD1306.h>       // Ekrana yazı yazma için kütüphane yükle

#define SCREEN_WIDTH 128            // Ekran genişiliğini belirle
#define SCREEN_HEIGHT 64            // Ekran yüksekliğini belirle

// SDA ve SCL pinlerini tanımla
#define SDA_PIN 12
#define SCL_PIN 14

// Ultrasonik sensörün bağlı olduğu pinleri belirle
#define US_TRIG_PIN 2
#define US_ECHO_PIN 16

// Ekran objesini oluştur
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

  pinMode(US_TRIG_PIN, OUTPUT);                 // Ultrasonik sensörün ses yaymak için kullanacağı pin
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);          // Ultrasonik sensörün yaydığı sesi dinlemek için kullanacağı pin

  display.clearDisplay();                       // ekranı temizle
  display.setTextSize(3);                       // Yazı tipi boyutunu 3 yap
  display.setTextColor(SSD1306_WHITE);          // Yazı rengini belirle
}

void loop() {
  digitalWrite(US_TRIG_PIN, LOW);               // sesi kapat
  delayMicroseconds(2);                         // saniyenin milyonda 2 kadarı kadar bekle
  digitalWrite(US_TRIG_PIN, HIGH);              // sesi aç
  delayMicroseconds(10);                        // saniyenin milyonda 10 kadarı kadar bekle
  digitalWrite(US_TRIG_PIN, LOW);               // sesi kapat

  long duration = pulseIn(US_ECHO_PIN, HIGH);   // Gönderilen ses ile işitilen ses arasındaki zaman farkını değişkene kaydet
  int distance = duration * 0.034 / 2;          // zaman / sesin yayılma hızı ile, mesafeyi bul

  // ekrana yazı yazma parametreleri
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Mesafe: ");
  display.print(distance);
  display.println(" cm");
  display.display();

  delay(1000);
}
