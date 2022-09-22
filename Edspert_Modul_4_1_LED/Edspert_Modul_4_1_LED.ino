// variable pin led
const int pinLED = 23;

void setup() {
  // inisiasi Serial Communication
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  // inisiasi pin
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // kode menghidupkan LED
  digitalWrite(pinLED, HIGH);
  delay(500);
  // kode mematikan LED
  digitalWrite(pinLED, LOW);
  delay(500);
}
