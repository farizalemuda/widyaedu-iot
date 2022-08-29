#include <AntaresESP32HTTP.h>
#include "DHTesp.h"

#define ACCESSKEY "your-access-key"       // Ganti dengan access key akun Antares anda
#define WIFISSID "your-wifi-ssid"         // Ganti dengan SSID WiFi anda
#define PASSWORD "your-wifi-pass"     // Ganti dengan password WiFi anda

#define applicationName "your-application-name"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "your-device-name"     // Ganti dengan device Antares yang telah dibuat

// deklarasi pin-pin sensor
#define PIN_DHT 14
#define PIN_LDR A0
#define PIN_MOISTURE A3

// inisialisasi object library
DHTesp dht;
AntaresESP32HTTP antares(ACCESSKEY);

// inisialisasi variable
int moisture = 0;
int ldr = 0;
int temp =0;
int hum = 0;

void setup()
{
  // inisiasi Serial comm dengan baud rate 9600
  Serial.begin(9600);

  // inisiasi pin sensor
  // inisiasi LDR
  pinMode(PIN_LDR, INPUT);
  // inisiasi Moisture
  pinMode(PIN_MOISTURE, INPUT);
  // inisiasi DHT
  dht.setup(PIN_DHT, DHTesp::DHT22);

  // inisiasi wifi antares
  antares.wifiConnection(WIFISSID,PASSWORD);
  // inisiasi debug lib antares
  antares.setDebug(true);
}
 
void loop() {
  // LDR
  ldr = analogRead(PIN_LDR);
  // moisture
  moisture = analogRead(PIN_MOISTURE);
  // DHT
  TempAndHumidity data = dht.getTempAndHumidity();
  // ekstrak data temperature
  temp = data.temperature;
  // ekstrak data humidity
  hum = data.humidity;

  // display data ke serial monitor
  Serial.println("===================");
  Serial.print("LDR: ");
  Serial.println(ldr);
  Serial.print("Suhu: ");
  Serial.println(temp);
  Serial.print("Kelembaban: ");
  Serial.println(hum);
  Serial.print("Moisture: ");
  Serial.println(moisture);
  Serial.println("===================");
  
  // include data ke json
  antares.add("LDR", ldr);
  antares.add("Suhu", temp);
  antares.add("Kelembapan", hum);
  antares.add("Moisture", moisture);

  //Kirim data ke Antares
  antares.send(applicationName, deviceName);
  delay(20000);
}
