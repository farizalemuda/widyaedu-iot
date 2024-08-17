#define pinRelay 15

void setup() {
  // put your setup code here, to run once:
  pinMode(pinRelay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("=========================");
  Serial.println("EDSPERT - Modul 4 - Relay");
  Serial.println("=========================");
  Serial.println("Relay OFF");
  digitalWrite(pinRelay, LOW);
  delay(2000);
  Serial.println("Relay ON");
  digitalWrite(pinRelay, HIGH);
  delay(2000);
}
