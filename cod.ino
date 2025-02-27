#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ldrPin = A0;
const int buttonPin = 2;
const int ledPin = 9;
const int ledPin2 = 10;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool isButtonPressed = false;
bool lastButtonState = LOW;
String currentMessage = "";
String message = "";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  delay(3000);
  lcd.clear();
}

void loop()
{
  int ldrValue = analogRead(ldrPin);
  int buttonState = digitalRead(buttonPin);

  if (ldrValue < 200)
  {
    lcd.backlight();
    if (buttonState == HIGH && lastButtonState == LOW)
    {
      isButtonPressed = true;
      startTime = millis();
    }

    if (buttonState == HIGH)
    {
      elapsedTime = millis() - startTime;
      int secondsElapsed = elapsedTime / 1000;

      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(secondsElapsed);
      lcd.print(" sec");
    }
    else if (buttonState == LOW && lastButtonState == HIGH)
    {
      if (isButtonPressed)
      {
        isButtonPressed = false;
        elapsedTime = millis() - startTime;

        lcd.clear();
        if (elapsedTime < 1000)
        {
          lcd.print(".");
          currentMessage += ".";
        } 
        else if (elapsedTime >= 1000 && elapsedTime < 2000)
        {
          lcd.print("-");
          currentMessage += "-";
        } 
        else if (elapsedTime >= 2000 && elapsedTime < 3000)
        {
          char letter = convertToAscii(currentMessage);
          lcd.clear();
          if (letter != '\0')
          {
            lcd.print("Letter: ");
            lcd.print(letter);

            message += letter;

            digitalWrite(ledPin, HIGH);
            delay(1000);
            digitalWrite(ledPin, LOW);
          }
          else 
          {
            lcd.print("Invalid Code!");
          }
          currentMessage = "";
        }
        else if (elapsedTime >= 3000)
        {
          lcd.clear();
          lcd.print("Array: ");
          lcd.setCursor(0, 1);
          lcd.print(message);
          digitalWrite(ledPin2, HIGH);
          delay(1000);
          digitalWrite(ledPin2, LOW);

          message = "";
          currentMessage = "";
        }
      }
    }
    lastButtonState = buttonState;
  }
  else
  {
    lcd.noBacklight();
    lcd.clear();
    lcd.print("Powerful");
    lcd.setCursor(0, 1);
    lcd.print("light!");
    delay(1000);
    lcd.clear();
  }
}

char convertToAscii(String input)
{
  if (input == ".-") return 'A';
  if (input == "-...") return 'B';
  if (input == "-.-.") return 'C';
  if (input == "-..") return 'D';
  if (input == ".") return 'E';
  if (input == "..-.") return 'F';
  if (input == "--.") return 'G';
  if (input == "....") return 'H';
  if (input == "..") return 'I';
  if (input == ".---") return 'J';
  if (input == "-.-") return 'K';
  if (input == ".-..") return 'L';
  if (input == "--") return 'M';
  if (input == "-.") return 'N';
  if (input == "---") return 'O';
  if (input == ".--.") return 'P';
  if (input == "--.-") return 'Q';
  if (input == ".-.") return 'R';
  if (input == "...") return 'S';
  if (input == "-") return 'T';
  if (input == "..-") return 'U';
  if (input == "...-") return 'V';
  if (input == ".--") return 'W';
  if (input == "-..-") return 'X';
  if (input == "-.--") return 'Y';
  if (input == "--..") return 'Z';
  if (input == "----") return ' ';
  return '\0';
}
