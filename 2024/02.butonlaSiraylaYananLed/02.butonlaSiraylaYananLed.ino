#define KIRMIZI_LED 3
#define SARI_LED 1
#define YESIL_LED 0
#define BUZZER 4
#define BUTTON 2

int butonDurumu = 0;
int sonButonDurumu = 0;
int butonSayac = 0;

void setup() {
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  butonDurumu = digitalRead(BUTTON);

  // Buton basili mi kontrol et
  if (butonDurumu == LOW) {
    butonSayac++;
    if (butonSayac > 4) {
      butonSayac = 1;  // 4'ten sonra sayaci sifirla
    }
    delay(100); // Gecikme ekle
  }
  sonButonDurumu = butonDurumu;

  switch (butonSayac) {
    case 1:
      LEDyak(KIRMIZI_LED);
      break;
    case 2:
      LEDyak(SARI_LED);
      break;
    case 3:
      LEDyak(YESIL_LED);
      break;
    case 4:
      LEDleriKapat();
      break;
  }
}

void LEDyak(int ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}

void LEDleriKapat() {
  digitalWrite(KIRMIZI_LED, LOW);
  digitalWrite(SARI_LED, LOW);
  digitalWrite(YESIL_LED, LOW);
}
