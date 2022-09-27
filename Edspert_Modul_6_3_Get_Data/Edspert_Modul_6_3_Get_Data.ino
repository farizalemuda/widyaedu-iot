#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "http://platform.antares.id:8080/~/antares-cse/antares-id/your-app-name/your-dev-name/la";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
}

void loop() {
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");

  HTTPClient http;
  http.begin(url);
  http.addHeader("X-M2M-Origin", "your-access-key");
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Accept", "application/json");

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }

  delay(5000);
}