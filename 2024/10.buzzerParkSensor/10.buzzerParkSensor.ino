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

// Buzzer'ın bağlı olduğu pini belirle
#define BUZZER 4

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

  // Pinlerin çalışma modunu belirle
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  // Ekranı temizle
  display.clearDisplay();
}

void loop() {
  digitalWrite(US_TRIG_PIN, LOW);               // sesi kapat
  delayMicroseconds(2);                         // saniyenin milyonda 2 kadarı kadar bekle
  digitalWrite(US_TRIG_PIN, HIGH);              // sesi aç
  delayMicroseconds(10);                        // saniyenin milyonda 10 kadarı kadar bekle
  digitalWrite(US_TRIG_PIN, LOW);               // sesi kapat

  long duration = pulseIn(US_ECHO_PIN, HIGH);   // Gönderilen ses ile işitilen ses arasındaki zaman farkını değişkene kaydet
  int distance = duration * 0.034 / 2;          // zaman / sesin yayılma hızı ile, mesafeyi bul

  // Ekranı temizle
  display.clearDisplay();

  // Mesafe değerine göre çubuklu bir grafik oluştur
  int barHeight = map(distance, 0, 50, 0, SCREEN_HEIGHT); // Mesafe değerini ekran yüksekliğine dönüştür
  float reducedHeight = barHeight * 0.5; // Azaltılmış yükseklik değeri

  // Çubukları çiz
  for (int i = 0; i < SCREEN_WIDTH / 10; i++) {
    if (i * 10 <= reducedHeight) {
      display.fillRect(i * 10, SCREEN_HEIGHT - i * 4, 8, i * 4, SSD1306_WHITE); // Çubuğu çiz
    }
  }

  // Ekranda göster
  display.display();

  // Buzzer kontrolü
  controlBuzzer(distance);

  // Bekleme
  delay(100);
}

void controlBuzzer(int distance) {
  if (distance > 100) {
    distance = 100;
  } 
  int frequency = map(distance, 0, 100, 1000, 100); // Mesafe değerini frekansa dönüştür
  int duration = map(distance, 0, 100, 50, 500); // Mesafe değerini süreye dönüştür

  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
  delay(duration);
  Serial.println(distance);
}
