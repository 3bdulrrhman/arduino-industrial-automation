
// *Abdelrhaman Ali  tarafından hazırlanmıştır.*
// e-mail: *2021734034@cumhuriyet.edu.tr*


#include <LiquidCrystal.h>
#include <DHT.h>

// LCD Ayarları (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Pin Tanımlamaları
#define BUZZER_PIN 13
#define MOTOR_PIN  8
#define VALF_PIN   10
#define DHTPIN     9      
#define DHTTYPE    DHT22 

DHT dht(DHTPIN, DHTTYPE);

// Sistem Değişkenleri
volatile boolean sistem_acik = 0;
unsigned long previousMillis = 0;
int displayState = 0; 

void setup() {
  // Dış Kesme Ayarı (Pin 2)
  attachInterrupt(digitalPinToInterrupt(2), sensorKesme, FALLING);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(VALF_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  dht.begin();
  
  lcd.clear();
  lcd.print("Sistem Kapali");
}

void loop() {
  if (sistem_acik) {
    float t = dht.readTemperature(); // Sıcaklık oku
    float h = dht.readHumidity();    // Nem oku
    int ppm = (int)(200 + (analogRead(A1) / 1023.0 * 2000)); 

    // Sıcaklık Kontrolü (23 Derece)
    if (!isnan(t)) {
      if (t > 23.0) { 
        digitalWrite(MOTOR_PIN, HIGH); 
        digitalWrite(BUZZER_PIN, HIGH); 
      }
      else { 
        digitalWrite(MOTOR_PIN, LOW); 
        digitalWrite(BUZZER_PIN, LOW); 
      }
    }

    // Gaz Kontrolü (1000 ppm)
    digitalWrite(VALF_PIN, (ppm > 1000) ? HIGH : LOW);

    // ==========================================
    // Ekran Yönetimi
    // ==========================================
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      displayState++; 
      if (displayState > 2) displayState = 0; 
      lcd.clear(); 
    }

    // Durum 0: Sıcaklık ve Nem Gösterimi
    if (displayState == 0) {
      lcd.setCursor(0, 0); 
      lcd.print("Sicaklik: "); 
      if (isnan(t)) lcd.print("Hata"); else { lcd.print(t, 1); lcd.write(223); lcd.print("C"); }
      
      lcd.setCursor(0, 1); 
      lcd.print("Nem Orani: %"); 
      if (isnan(h)) lcd.print("Hata"); else { lcd.print(h, 1); }
    } 
    // Durum 1: Gaz Konsantrasyonu Gösterimi
    else if (displayState == 1) {
      lcd.setCursor(0, 0); 
      lcd.print("Gaz Kons.:");
      lcd.setCursor(0, 1); 
      lcd.print(ppm); lcd.print(" ppm        ");
    }
    // Durum 2: Nem Uyarısı
    else if (displayState == 2) {
      if (!isnan(h) && h > 70.0) {
        lcd.setCursor(0, 0); lcd.print("Dikkat!"); 
        lcd.setCursor(0, 1); lcd.print("Ortam Nemli");
      } else {
        displayState = 0; 
        previousMillis = currentMillis;
      }
    }
  } else {
    // Sistem Kapalı Modu
    digitalWrite(MOTOR_PIN, LOW); 
    digitalWrite(BUZZER_PIN, LOW); 
    digitalWrite(VALF_PIN, LOW);
    
    lcd.setCursor(0, 0); 
    lcd.print("Sistem Kapali! ");
    lcd.setCursor(0, 1); 
    lcd.print("                "); 
  }
}

//  KESME FONKSİYONU
void sensorKesme() {
  static unsigned long son_kesme_zamani = 0;
  unsigned long kesme_zamani = millis();

  if (kesme_zamani - son_kesme_zamani > 300) { // Debounce süresi artırıldı
    sistem_acik = !sistem_acik; 
    
    // Proteus ekran senkronizasyonu için sıfırlama
    displayState = 0;
    
    // Ekranı temizlemeden önce tüm çıkışları durdur (opsiyonel)
    if (!sistem_acik) {
       // Sistem kapanırken temiz bir ekran mesajı
    }
  }
  son_kesme_zamani = kesme_zamani;
}