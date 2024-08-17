// variable pin buzzer
#define PIN_BUZZER 23

void setup() {
  // inisiasi Serial Communication
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  // inisiasi pin
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  tone(PIN_BUZZER, 500);
  delay(500);
  tone(PIN_BUZZER, 800);
  delay(500);
}