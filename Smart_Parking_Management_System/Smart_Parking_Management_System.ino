```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo gateServo;

// IR Sensor Pins
#define ENTRY_SENSOR 2
#define EXIT_SENSOR 3

// Servo Pin
#define SERVO_PIN 9

int totalSlots = 5;
int availableSlots = 5;

void setup() {

  pinMode(ENTRY_SENSOR, INPUT);
  pinMode(EXIT_SENSOR, INPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0); // Gate Closed

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();

  displaySlots();
}

void loop() {

  // Vehicle Entry
  if (digitalRead(ENTRY_SENSOR) == LOW && availableSlots > 0) {

    availableSlots--;

    lcd.clear();
    lcd.print("Vehicle Entry");

    openGate();

    delay(2000);

    displaySlots();
  }

  // Vehicle Exit
  if (digitalRead(EXIT_SENSOR) == LOW && availableSlots < totalSlots) {

    availableSlots++;

    lcd.clear();
    lcd.print("Vehicle Exit");

    openGate();

    delay(2000);

    displaySlots();
  }

  // Parking Full
  if (availableSlots == 0) {

    lcd.setCursor(0, 1);
    lcd.print("Parking Full ");
  }

  delay(300);
}

void openGate() {

  gateServo.write(90); // Open Gate
  delay(3000);

  gateServo.write(0);  // Close Gate
  delay(1000);
}

void displaySlots() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Available:");

  lcd.setCursor(11, 0);
  lcd.print(availableSlots);

  lcd.setCursor(0, 1);
  lcd.print("Total:");
  lcd.print(totalSlots);
}
```
