#include <ESP8266WiFi.h>            // Ağ kurma bilgileri içeren wifi kütüphanesini yükle
#include <ESP8266WebServer.h>       // Web sayfalarının nasıl sunulacağı bilgilerini içeren sunucu kütüphanesini yükle

#include "pitches.h"                // Notalar için kütüphane yükle

int melody[] = {                    // Notaları bir değişkene yükle
  REST, REST, REST, REST, NOTE_E4, NOTE_A4, NOTE_C5,
  
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,

  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,

  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4,

  NOTE_E4, REST, NOTE_E4, NOTE_A4, NOTE_C5,

  //repeat
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_E4, NOTE_A4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E4, NOTE_DS4,

  NOTE_D4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_B4, NOTE_D4, NOTE_F4, NOTE_GS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_GS4,

  NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_GS4,
  NOTE_G4, NOTE_B4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_DS4,

  NOTE_E4
};

int durations[] = {                 // Nota sürelerini gir
  4, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8,

  2, 8, 8, 8, 8,

  //repeats
  8, 8, 8, 8, 8, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,

  2, 8, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8,
  2, 8, 8, 8, 8,

  2
};

#define KIRMIZI_LED 3
#define SARI_LED 1
#define YESIL_LED 0
#define BUZZER 4

const char *ssid = "TTK2024-01";    // Network adını belirle, en az 8 basamaklı olmalı
const char *password = "12345678";  // Network şifresi belirle, en az 8 basamaklı olmalı

// 80 portunda çalışan http ile başlayan sunucu objesi oluştur
ESP8266WebServer server(80);

bool kirmiziDurum = false;
bool sariDurum = false;
bool yesilDurum = false;
bool buzzerDurum = false;

void setup() {
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  server.on("/", anasayfaIcerik);
  server.on("/kirmizi", kirmiziTalep);
  server.on("/sari", sariTalep);
  server.on("/yesil", yesilTalep);
  server.on("/buzzer", buzzerTalep);
  server.begin();

}

void loop() {
  server.handleClient();
}

void anasayfaIcerik() {
  String kirmiziButtonText = kirmiziDurum ? "KIRMIZI LED KAPAT" : "KIRMIZI LED YAK";
  String sariButtonText = sariDurum ? "SARI LED KAPAT" : "SARI LED YAK";
  String yesilButtonText = yesilDurum ? "YESIL LED KAPAT" : "YESIL LED YAK";
  String buzzerButtonText = yesilDurum ? "BUZZER SUS" : "BUZZER ÖT";
  
  String html = "<html><head><style>";
  html += "button {font-size: 24px; padding: 15px 30px; border: none; border-radius: 5px; cursor: pointer;}";
  html += ".kirmizi {width: 100%; background-color: red; color: white;}";
  html += ".sari {width: 100%; background-color: yellow; color: black;}";
  html += ".yesil {width: 100%; background-color: green; color: white;}";
  html += ".buzzer {width: 100%; background-color: blue; color: white;}";
  html += "</style></head><body>";
  html += "<h1>NodeMCU LED Kontrol Paneli</h1>";
  html += "<table width='100%'>";
  html += "<tr>";
  html += "<td width='25%'><button class='kirmizi' onclick=\"location.href='/kirmizi'\">" + kirmiziButtonText + "</button></td>";
  html += "<td width='25%'><button class='sari' onclick=\"location.href='/sari'\">" + sariButtonText + "</button></td>";
  html += "<td width='25%'><button class='yesil' onclick=\"location.href='/yesil'\">" + yesilButtonText + "</button></td>";
  html += "<td width='25%'><button class='buzzer' onclick=\"location.href='/buzzer'\">" + buzzerButtonText + "</button></td>";
  html += "</tr>";
  html += "</table>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void kirmiziTalep() {
  kirmiziDurum = !kirmiziDurum;
  digitalWrite(KIRMIZI_LED, kirmiziDurum ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void sariTalep() {
  sariDurum = !sariDurum;
  digitalWrite(SARI_LED, sariDurum ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void yesilTalep() {
  yesilDurum = !yesilDurum;
  digitalWrite(YESIL_LED, yesilDurum ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void buzzerTalep() {
  buzzerDurum = !buzzerDurum;
  if(buzzerDurum) {
    buzzerSong();
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void buzzerSong() {
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
