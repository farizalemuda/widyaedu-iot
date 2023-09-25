#include <LiquidCrystal.h>

LiquidCrystal lcd(23, 22, 21, 19, 18, 5);

void setup() {
  lcd.begin(16, 2);
  // you can now interact with the LCD, e.g.:
  // Print something
  lcd.setCursor(0, 0);
  lcd.print("EDSPERT IOT");
  lcd.setCursor(0, 1);
  lcd.print("Hello World!");
}

void loop() {
  // ...
}