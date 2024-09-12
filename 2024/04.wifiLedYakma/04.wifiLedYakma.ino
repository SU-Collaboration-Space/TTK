#include <ESP8266WiFi.h>            // Ağ kurma bilgileri içeren wifi kütüphanesini yükle
#include <ESP8266WebServer.h>       // Web sayfalarının nasıl sunulacağı bilgilerini içeren sunucu kütüphanesini yükle

const char *ssid = "TTK2024-01";    // Network adını belirle, en az 8 basamaklı olmalı
const char *password = "12345678";  // Network şifresi belirle, en az 8 basamaklı olmalı

// Ledlerin bağlı olduğu pinleri belirle
const int KIRMIZI_LED = 3;
const int SARI_LED = 1;
const int YESIL_LED = 0;

// 80 portunda çalışan http ile başlayan sunucu objesi oluştur
ESP8266WebServer server(80);

// açık/kapalı durumun takibi için boolean oluştur
bool kirmiziDurum = false;
bool sariDurum = false;
bool yesilDurum = false;

void setup() {
  Serial.begin(115200);             // Serial loglama yapılacağı monitoru başlat

  WiFi.mode(WIFI_AP);               // Wifi modülünün çalışma modunu belirle (ağa katılmak yerine, kendini ağını kur)
  WiFi.softAP(ssid, password);      // 4. ve 5. satırda belirlenen sabitler ile, ağa adı ve bu ağa katılmak için gerekli şifre belirlenir

  // LED pinlerini çıkış olarak ayarla
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);

  // Sunucu ayarları
  server.on("/", handleRoot);             // 192.168.1.104 ip adresinde, kök dizin "/" üzerinden ulaşılacak sayfanın konumu belirlenir
  server.on("/kirmizi", handleKirmizi);   // 192.168.1.104/kirmizi adresi üzerinden tetiklenecek "handleKirmizi" fonksiyonu belirlenir
  server.on("/sari", handleSari);         // 192.168.1.104/sari adresi üzerinden tetiklenecek "handleSari" fonksiyonu belirlenir
  server.on("/yesil", handleYesil);       // 192.168.1.104/yesil adresi üzerinden tetiklenecek "handleYesil" fonksiyonu belirlenir
  server.begin();                         // Yukarıdaki parametreler ile server başlatılır
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();                  // Gelen taleplerin karşılanıp işlenmesi sağlanır
  
  IPAddress IP = WiFi.softAPIP();         // Atanan ip adresi, bir değişkene atanır

  Serial.print("AP IP adresi: ");         // Ip değişkeni serial monitora basılır
  Serial.println(IP);
}

// Web sayfasını oluşturulacak kod aşağıda inşaa edilir
void anasayfaIcerik() {
  String kirmiziButtonText = kirmiziDurum ? "KIRMIZI LED KAPAT" : "KIRMIZI LED YAK";  // 16. satırdaki booleanın durumuna gösteren metin belirlenir
  String sariButtonText = sariDurum ? "SARI LED KAPAT" : "SARI LED YAK";              // 17. satırdaki booleanın durumuna gösteren metin belirlenir
  String yesilButtonText = yesilDurum ? "YESIL LED KAPAT" : "YESIL LED YAK";          // 18. satırdaki booleanın durumuna gösteren metin belirlenir
  
  String html = "<html><head><style>";
  html += "button {font-size: 24px; padding: 15px 30px; border: none; border-radius: 5px; cursor: pointer;}";
  html += ".kirmizi {width: 100%; background-color: red; color: white;}";
  html += ".sari {width: 100%; background-color: yellow; color: black;}";
  html += ".yesil {width: 100%; background-color: green; color: white;}";
  html += "</style></head><body>";
  html += "<h1>NodeMCU LED Kontrol Paneli</h1>";
  html += "<table width='100%'>";
  html += "<tr>";
  html += "<td width='33%'><button class='kirmizi' onclick=\"location.href='/kirmizi'\">" + kirmiziButtonText + "</button></td>";   // 51. satırdaki metin, buton içinde gösterilir
  html += "<td width='34%'><button class='sari' onclick=\"location.href='/sari'\">" + sariButtonText + "</button></td>";            // 52. satırdaki metin, buton içinde gösterilir
  html += "<td width='33%'><button class='yesil' onclick=\"location.href='/yesil'\">" + yesilButtonText + "</button></td>";         // 53. satırdaki metin, buton içinde gösterilir
  html += "</tr>";
  html += "</table>";
  html += "</body></html>";
  server.send(200, "text/html", html);     // 32. satırda, http://192.168.1.104/ üzerinden talep edilen içeriği, isteyen cihaza gönderir 
}

// 33. satırda belirlenen 192.168.1.104/kirmizi adresin tetiklenmesi ile çalıştırılacak fonsiyon
void kirmiziTalep() {
  kirmiziDurum = !kirmiziDurum;                             // kapalı iken basılan düğme açık, açık iken basılan düğme de kapalı hale getirilir
  digitalWrite(KIRMIZI_LED, kirmiziDurum ? HIGH : LOW);     // üst satırdaki duruma göre, Led yakılır ya da kapatılır
  server.sendHeader("Location", "/");                       // 192.168.1.104/kirmizi adresinden tekrar anasayfaya yönlendirir
  server.send(303);                                         // Http için yönlendirme kodu
}

// 34. satırda belirlenen 192.168.1.104/sari adresin tetiklenmesi ile çalıştırılacak fonsiyon
void sariTalep() {
  sariDurum = !sariDurum;                                   // kapalı iken basılan düğme açık, açık iken basılan düğme de kapalı hale getirilir
  digitalWrite(SARI_LED, sariDurum ? HIGH : LOW);           // üst satırdaki duruma göre, Led yakılır ya da kapatılır
  server.sendHeader("Location", "/");                       // 192.168.1.104/sari adresinden tekrar anasayfaya yönlendirir
  server.send(303);                                         // Http için yönlendirme kodu
}

// 35. satırda belirlenen 192.168.1.104/yesil adresin tetiklenmesi ile çalıştırılacak fonsiyon
void yesilTalep() {
  yesilDurum = !yesilDurum;                                 // kapalı iken basılan düğme açık, açık iken basılan düğme de kapalı hale getirilir
  digitalWrite(YESIL_LED, yesilDurum ? HIGH : LOW);         // üst satırdaki duruma göre, Led yakılır ya da kapatılır
  server.sendHeader("Location", "/");                       // 192.168.1.104/yesil adresinden tekrar anasayfaya yönlendirir
  server.send(303);                                         // Http için yönlendirme kodu
}
