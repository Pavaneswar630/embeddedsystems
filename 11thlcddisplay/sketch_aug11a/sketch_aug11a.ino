#include <LiquidCrystal.h>

// RS, EN, D4, D5, D6, D7 connections
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);           // 16 columns, 2 rows
  lcd.print("Hello, Proteus!"); // First line
}

void loop() {
  lcd.setCursor(0, 1);        // Column 0, Row 1 (second line)
  lcd.print("Counter: ");
  lcd.print(millis() / 1000); // Seconds since start
  delay(500);
}
