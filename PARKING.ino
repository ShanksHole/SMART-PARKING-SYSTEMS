// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// Arduino Car Parking System

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the HEX address
#include <Servo.h> 

Servo myservo1;

int IR1 = 2; // IR sensor for car entry
int IR2 = 3; // IR sensor for car exit
int Slot = 3; // Total parking slots (initial value is 3)

int flag1 = 0; // Entry flag
int flag2 = 0; // Exit flag

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  myservo1.attach(4);
  myservo1.write(100); // Gate initially closed

  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() { 
  // Entry Logic
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;          // Entry flag set
      myservo1.write(0);  // Open gate
      Slot--;             // Decrease slot count
      delay(2000);        // Delay for car to pass
      myservo1.write(100); // Close gate
      delay(500);
      flag1 = 0;          // Reset flag
    } else {
      // Display "Parking Full" message
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");  
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  "); 
      delay(2000);
      lcd.clear(); 
    }
  }

  // Exit Logic
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    if (Slot < 3) {       // Prevent Slot from exceeding total
      flag2 = 1;          // Exit flag set
      myservo1.write(0);  // Open gate
      Slot++;             // Increase slot count
      delay(2000);        // Delay for car to pass
      myservo1.write(100); // Close gate
      delay(500);
      flag2 = 0;          // Reset flag
    }
  }

  // Display Remaining Slots
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
}
