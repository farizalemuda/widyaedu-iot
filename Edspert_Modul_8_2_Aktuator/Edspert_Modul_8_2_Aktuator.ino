#include <AntaresESP32HTTP.h>

#define ACCESSKEY "your-access-key"       // Ganti dengan access key akun Antares anda
#define WIFISSID "your-wifi-ssid"         // Ganti dengan SSID WiFi anda
#define PASSWORD "your-wifi-pass"     // Ganti dengan password WiFi anda

#define applicationName "your-application-name"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "your-device-name"     // Ganti dengan device Antares yang telah dibuat

// LED
#define LEDav 12 // ADC Value
#define LEDt 13 // Suhu
#define LEDmoist 17 // Moisture

// Batas LED Menyala
int batasLDR = 2400; // Batas ADC Value
int batast = 24; // Batas suhu
int batasmoist = 2800; // Batas Moisture

AntaresESP32HTTP antares(ACCESSKEY);      // Buat objek antares

void setup() {
  Serial.begin(9600);     // Buka komunikasi serial dengan baudrate 115200
  
  pinMode(LEDav, OUTPUT);
  pinMode(LEDt, OUTPUT);
  pinMode(LEDmoist, OUTPUT);

  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
}

void loop() {
  // Mengambil data terakhir ke penampungan data
  antares.get(applicationName, deviceName);

  // Mendapatkan data individu
  int LDR = antares.getInt("LDR");
  int suhu = antares.getInt("Suhu");
  int kelembapan = antares.getInt("Kelembapan");
  int moist = antares.getInt("Moisture");

  // Print data ke serial monitor
  Serial.println("ADC Value: " + String(LDR));
  Serial.println("Suhu: " + String(suhu));
  Serial.println("Kelembapan: " + String(kelembapan));
  Serial.println("Moisture: " + String(moist));
  delay(10000); 

  // LED LDR
  if(LDR > batasLDR){
    digitalWrite(LEDav, HIGH);
    Serial.println("Lamp is activated");
  }
  else {
    digitalWrite(LEDav, LOW);
    Serial.println("Lamp is deactivated");
  }

  // LED Suhu
  if(suhu > batast){
    digitalWrite(LEDt, HIGH);
    Serial.println("Fan is activated");
  }
  else {
    digitalWrite(LEDt, LOW);
    Serial.println("Fan is deactivated");
  }
  // LED Moisture
  if(moist > batasmoist){
    digitalWrite(LEDmoist, HIGH);
    Serial.println("Drip irigation is activated");
  }
  else {
    digitalWrite(LEDmoist, LOW);
    Serial.println("Drip irigation is deactivated");
  }
  
}
