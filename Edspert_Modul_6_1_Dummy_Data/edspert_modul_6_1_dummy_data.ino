#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// url endpoint data of device
const char* serverName = "http://platform.antares.id:8080/~/antares-cse/antares-id/your-app-name/your-dev-name";

// inisiasi variable 
unsigned long lastTime = 0;
// Setting timer 5 detik
unsigned long timerDelay = 5000;

void setup() {
  // inisiasi serial port
  Serial.begin(115200);

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
      String httpRequestData ="{\"m2m:cin\": { \"con\": \"{\\\"status\\\":\\\"0\\\"}\"}}";
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