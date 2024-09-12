#include <ESP8266WiFi.h>            // Ağ kurma bilgileri içeren wifi kütüphanesini yükle
#include <ESP8266WebServer.h>       // Web sayfalarının nasıl sunulacağı bilgilerini içeren sunucu kütüphanesini yükle

const char *ssid = "TTK2024-01";    // Network adını belirle, en az 8 basamaklı olmalı
const char *password = "12345678";  // Network şifresi belirle, en az 8 basamaklı olmalı

const int A_MOTOR_Ileri = 14;
const int A_MOTOR_Geri  = 12;
const int B_MOTOR_Ileri = 13;
const int B_MOTOR_Geri  = 15;

const int KIRMIZI_LED = 3;
const int SARI_LED = 1;
const int YESIL_LED = 0;

// 80 portunda çalışan http ile başlayan sunucu objesi oluştur
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);                         // Serial loglama yapılacağı monitoru başlat

  WiFi.mode(WIFI_AP);                           // Wifi modülünün çalışma modunu belirle (ağa katılmak yerine, kendini ağını kur)
  WiFi.softAP(ssid, password);                  // 4. ve 5. satırda belirlenen sabitler ile, ağa adı ve bu ağa katılmak için gerekli şifre belirlenir

  // Motora bağlı pinleri çıkış olarak ayarla
  pinMode(A_MOTOR_Ileri, OUTPUT);
  pinMode(A_MOTOR_Geri, OUTPUT);
  pinMode(B_MOTOR_Ileri, OUTPUT);
  pinMode(B_MOTOR_Geri, OUTPUT);

  // LED pinlerini çıkış olarak ayarla
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);

  server.on("/", HTTP_GET, anasayfaIcerik);     // 192.168.4.1 ip adresinde, kök dizin "/" üzerinden ulaşılacak sayfanın konumu belirlenir
  server.on("/motor", HTTP_GET, motorIcerik);   // 192.168.4.1/motor üzerinden alınacak yön koutları için adres aç
  server.begin();
}


void loop() {
  server.handleClient();                  // Gelen taleplerin karşılanıp işlenmesi sağlanır
  
  IPAddress IP = WiFi.softAPIP();         // Atanan ip adresi, bir değişkene atanır

  Serial.print("AP IP adresi: ");         // Ip değişkeni serial monitora basıl
  Serial.println(IP);
}

// Web sayfasını oluşturulacak kod aşağıda inşaa edilir
void anasayfaIcerik() {
  String html = "<html><head><style>";
  html += "body { font-family: Roboto }";
  html += "* { margin: 0px; padding: 0px; } button {background: rgba(100, 100, 100, .5); color: white;width:100%; height: 100px; font-size: 72px; border: 2px solid #fff; border-radius: 10px; cursor: pointer; font-family: Arial, sans-serif; }";
  html += ".context {width: 100%;position: absolute;top:10vh;z-index: 1}.area{background:#4e54c8;background:-webkit-linear-gradient(to left,#8f94fb,#4e54c8);width:100%;height:100vh}.circles{position:absolute;top:0;left:0;width:100%;height:100%;overflow:hidden}.circles li{position:absolute;display:block;list-style:none;width:20px;height:20px;background:rgba(255,255,255,.2);animation:25s linear infinite animate;bottom:-150px}.circles li:first-child{left:25%;width:80px;height:80px;animation-delay:0s}.circles li:nth-child(2){left:10%;width:20px;height:20px;animation-delay:2s;animation-duration:12s}.circles li:nth-child(3){left:70%;width:20px;height:20px;animation-delay:4s}.circles li:nth-child(4){left:40%;width:60px;height:60px;animation-delay:0s;animation-duration:18s}.circles li:nth-child(5){left:65%;width:20px;height:20px;animation-delay:0s}.circles li:nth-child(6){left:75%;width:110px;height:110px;animation-delay:3s}.circles li:nth-child(7){left:35%;width:150px;height:150px;animation-delay:7s}.circles li:nth-child(8){left:50%;width:25px;height:25px;animation-delay:15s;animation-duration:45s}.circles li:nth-child(9){left:20%;width:15px;height:15px;animation-delay:2s;animation-duration:35s}.circles li:nth-child(10){left:85%;width:150px;height:150px;animation-delay:0s;animation-duration:11s}@keyframes animate{0%{transform:translateY(0) rotate(0);opacity:1;border-radius:0}100%{transform:translateY(-1000px) rotate(720deg);opacity:0;border-radius:50%}}";
  html += "</style>";
  html += "<meta name='viewport' content='width=device-width', initial-scale=1.0, maximum-scale=1.0, user-scalable=no' />";
  html += "</head><body>";
  html += "<div class='context'>";
  html += "<h1 style='text-align:center; color: white'>Sabanci Universitesi</h1>";
  html += "<h1 style='text-align:center; color: white'>2024 Teknoloji ve Tasarim Kampi</h1>";
  html += "<h1 style='text-align:center; color: white'>Motor Kontrol Paneli</h1>";
  html += "<br>";
  html += "<table width='100%'>";
  html += "<tr>";
  html += "<td width='33%'>&nbsp;</td><td width='34%'><button id='btn_ileri' onmousedown='ileriBasildi()' ontouchstart='ileriBasildi()' onmouseup='butonBirakildi()' ontouchend='butonBirakildi()' oncontextmenu='return false;'><span>&#11014;</span></button></td><td width='33%'>&nbsp;</td>";
  html += "</tr>";
  html += "<tr>";
  html += "<td><button id='btn_sol' onmousedown='solBasildi()' ontouchstart='solBasildi()' onmouseup='butonBirakildi()' ontouchend='butonBirakildi()' oncontextmenu='return false;'><span>&#11013;</span></button></td><td></td><td><button id='btn_sag' onmousedown='sagBasildi()' ontouchstart='sagBasildi()' onmouseup='butonBirakildi()' ontouchend='butonBirakildi()' oncontextmenu='return false;'><span style='display: block; transform: rotate(-180deg)'>&#11013;</span></button></td>";
  html += "</tr>";
  html += "<tr>";
  html += "<td></td><td><button id='btn_geri' onmousedown='geriBasildi()' ontouchstart='geriBasildi()' onmouseup='butonBirakildi()' ontouchend='butonBirakildi()' oncontextmenu='return false;'><span>&#11015;</span></button></td><td></td>";
  html += "</tr>";
  html += "</table>";
  html += "</div>";
  html += "<div class='area' ><ul class='circles'><li></li><li></li><li></li><li></li><li></li><li></li><li></li><li></li><li></li><li></li></ul>";
  html += "</div>";
  html += "<script>";
  html += "function ileriBasildi() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/motor?yon=ileri', true); xhr.send(); }";
  html += "function geriBasildi() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/motor?yon=geri', true); xhr.send(); }";
  html += "function solBasildi() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/motor?yon=sol', true); xhr.send(); }";
  html += "function sagBasildi() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/motor?yon=sag', true); xhr.send(); }";
  html += "function butonBirakildi() { var xhr = new XMLHttpRequest(); xhr.open('GET', '/motor?yon=dur', true); xhr.send(); }";
  html += "document.addEventListener('touchmove', function (event) {if (event.scale !== 1) { event.preventDefault(); }}, { passive: false });";
  html += "</script></body></html>";
  server.send(200, "text/html", html);
}

// 37. satırda belirlenen adres üzerinden yakalanan içerik talep istemlerini işlemek için gerekli fonksiyon
void motorIcerik() {
  if (server.hasArg("yon")) {                 // yakalan içerik isteminde "yon" adlı parametre var mı? İçerik talepleri 81-84. satırlar üzerinden oluşturuluyor. Bunlar ise basılan buton ile tetikleniyor.
    String yon = server.arg("yon");           // var ise, değeri "yon" adlı değişkene yazılır
    if (yon == "ileri") {                     // "yon" değeri "ileri" ise aşağdaki şekilde pinlere elektrik verilir
      digitalWrite(A_MOTOR_Ileri, HIGH);
      digitalWrite(B_MOTOR_Ileri, HIGH);
      digitalWrite(A_MOTOR_Geri, LOW);
      digitalWrite(B_MOTOR_Geri, LOW);
      digitalWrite(KIRMIZI_LED, HIGH);
      digitalWrite(YESIL_LED, HIGH);
      digitalWrite(SARI_LED, LOW);
    } else if (yon == "geri") {               // "yon" değeri "geri" ise aşağdaki şekilde pinlere elektrik verilir
      digitalWrite(A_MOTOR_Ileri, LOW);
      digitalWrite(B_MOTOR_Ileri, LOW);
      digitalWrite(A_MOTOR_Geri, HIGH);
      digitalWrite(B_MOTOR_Geri, HIGH);
      digitalWrite(SARI_LED, HIGH);
      digitalWrite(KIRMIZI_LED, LOW);
      digitalWrite(YESIL_LED, LOW);
    } else if (yon == "sol") {                // "yon" değeri "sol" ise aşağdaki şekilde pinlere elektrik verilir
      digitalWrite(A_MOTOR_Ileri, LOW);
      digitalWrite(B_MOTOR_Ileri, HIGH);
      digitalWrite(A_MOTOR_Geri, HIGH);
      digitalWrite(B_MOTOR_Geri, LOW);
      digitalWrite(KIRMIZI_LED, HIGH);
      digitalWrite(YESIL_LED, LOW);
      digitalWrite(SARI_LED, LOW);
    } else if (yon == "sag") {                // "yon" değeri "sag" ise aşağdaki şekilde pinlere elektrik verilir
      digitalWrite(A_MOTOR_Ileri, HIGH);
      digitalWrite(B_MOTOR_Ileri, LOW);
      digitalWrite(A_MOTOR_Geri, LOW);
      digitalWrite(B_MOTOR_Geri, HIGH);
      digitalWrite(KIRMIZI_LED, LOW);
      digitalWrite(YESIL_LED, HIGH);
      digitalWrite(SARI_LED, LOW);
    } else if (yon == "dur") {                // "yon" değeri "dur" ise aşağdaki şekilde pinlere elektrik verilir
      digitalWrite(A_MOTOR_Ileri, LOW);
      digitalWrite(B_MOTOR_Ileri, LOW);
      digitalWrite(A_MOTOR_Geri, LOW);
      digitalWrite(B_MOTOR_Geri, LOW);
      digitalWrite(KIRMIZI_LED, LOW);
      digitalWrite(YESIL_LED, LOW);
      digitalWrite(SARI_LED, LOW);
    }
  }
  server.send(200, "text/plain", "");         // 37. satırda, http://192.168.4.1/ üzerinden talep edilen içeriği, isteyen cihaza gönderir 
}