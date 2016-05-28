#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 7, 6, 5, 4);


// Max controllers
float current_temperature = 50.0;
float target_temperature = 70.0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("T=XX.XX  A=XX.XX");
  lcd.setCursor(0, 1);
  lcd.print("Aquecedor ligado");
}

void loop() {
  lcd.setCursor(2, 0);
  lcd.print(current_temperature);
  lcd.setCursor(11, 0);
  lcd.print(target_temperature);
  delay(100);
}
