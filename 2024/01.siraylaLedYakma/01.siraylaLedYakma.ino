#define KIRMIZI_LED 3
#define SARI_LED 1
#define YESIL_LED 0
#define BUZZER 4

void setup() {
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Kırmızı LED'i aç ve kapat
  digitalWrite(KIRMIZI_LED, HIGH);
  delay(1000);
  digitalWrite(KIRMIZI_LED, LOW);
  delay(1000);

  // Sarı LED'i aç ve kapat
  digitalWrite(SARI_LED, HIGH);
  delay(1000);
  digitalWrite(SARI_LED, LOW);
  delay(1000);

  // Yeşil LED'i aç ve kapat
  digitalWrite(YESIL_LED, HIGH);
  delay(1000);
  digitalWrite(YESIL_LED, LOW);
  delay(1000);

  // BUZZER'i aç ve kapat
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  delay(1000);
}