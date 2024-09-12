#define BUZZER 4
#define BUTTON 2

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  // Buton basili mi kontrol et
  // Eger basili ise girdi degeri LOW olacaktir
  if (digitalRead(BUTTON) == LOW) {
    // Buzzeri calistir
    digitalWrite(BUZZER, HIGH);
  } else {
    // Buzzeri kapat
    digitalWrite(BUZZER, LOW);
  }
}

// Jumper solda olacak