// proses include library 
#include "DHTesp.h"
#include "WiFi.h"
#include "HTTPClient.h"

// deklarasi variable
// set pin yang digunakan
#define DHTPIN 15

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// deklarasi object sensor
// set tipe DHT dan pin yang digunakan
DHTesp dht;

// url endpoint data of device
const char* serverName = "http://platform.antares.id:8080/~/antares-cse/antares-id/your-app-name/your-dev-name";

// inisiasi variable 
unsigned long lastTime = 0;
// Setting timer 5 detik
unsigned long timerDelay = 5000;

void setup() {
  // inisiasi interface serial
  Serial.begin(115200);

  Serial.println("EDSPERT - Akuisisi sensor DHT22 via ESP32");

  // inisiasi sensor DHT
  dht.setup(DHTPIN, DHTesp::DHT22);

  // inisiasi WiFi Client
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //rutin melakukan pengiriman data setiap waktu yang diset
  if ((millis() - lastTime) > timerDelay) {
    // deklarasi objek untuk menampung data 
    // temperatur dan kelembapan dari DHT22
    TempAndHumidity data = dht.getTempAndHumidity();

    // ekstrak data temperature
    float temp = data.temperature;
    // ekstrak data humidity
    float hum = data.humidity;

    // menampilkan data di serial
    Serial.println("Suhu: " + String(temp, 2) + "°C");
    Serial.println("Kelembaban: " + String(hum, 1) + "%");
    Serial.println("---");

    // waktu jeda sampling data
    // minimal 2 detik
    delay(5000);

    // mengecek koneksi wifi
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // inisiasi komunikasi http
      http.begin(client, serverName);

      // inisiasi http header
      http.addHeader("X-M2M-Origin", "your-access-key");
      http.addHeader("Content-Type", "application/json;ty=4");
      http.addHeader("Accept", "application/json");
      // inisiasi data yang dikirim di restful api
      String httpRequestData ="{\"m2m:cin\": { \"con\": \"{\\\"temp\\\":\\\"";
      httpRequestData = httpRequestData + String(temp, 2);
      httpRequestData = httpRequestData + "\\\",\\\"hum\\\":\\\"";
      httpRequestData = httpRequestData + String(hum,1);
      httpRequestData = httpRequestData + "\\\"}\"}}";
      // mengirimkan HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // menutup koneksi
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
