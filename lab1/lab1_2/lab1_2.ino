#include <Adafruit_LiquidCrystal.h>
#include <stdio.h>
#include <string.h>

#define BAUD_RATE 4800
#define MAX_INPUT_LENGTH 10
#define SUCCESS_PIN 15
#define ERROR_PIN 14

const int rs = 12, enable = 11, db4 = 5, db5 = 4, db6 = 3, db7 = 2;
const int lcdDimensions[2] = {16, 2};
Adafruit_LiquidCrystal lcd(rs, enable, db4, db5, db6, db7); 
char input[MAX_INPUT_LENGTH];
int inputLen = 0;
char enterKey = '#';
char backspaceKey = '*';
char passCode[] = "ABCD";

void clearLcd() {
  // Set the init LCD text
  lcd.clear();
  lcd.begin(lcdDimensions[0], lcdDimensions[1]);
  lcd.print("Enter passcode\n");

  // Clear the input 
  memset(input, '\0', sizeof(input));
  inputLen = 0;
}

void setup() {
  pinMode(SUCCESS_PIN, OUTPUT);
  pinMode(ERROR_PIN, OUTPUT);
  Serial.begin(BAUD_RATE);
  redirectOutput();
  printf("Enter your passcode using the 4x4 keypad.\n");
  printf("Help: # - Enter, * - Backspace. \n");
  clearLcd();

}

void loop() {

  // Get the pressed key
  char customKey = getCustomKeypad();
  lcd.setCursor(inputLen, 1);

  if (customKey && inputLen < MAX_INPUT_LENGTH - 1 && customKey != enterKey && customKey != backspaceKey) {
        input[inputLen] = customKey;
        inputLen++;
        lcd.print(customKey);

  } else if (customKey == enterKey){
    input[inputLen] = '\0';
    printf("Input code: %s\n", input);

    if (strcmp(input, passCode) != 0) {
      digitalWrite(ERROR_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Incorrect Code!");

    } else {
      digitalWrite(SUCCESS_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Code Approved!");
    }

    delay(2000);
    clearLcd();
    digitalWrite(ERROR_PIN, LOW);
    digitalWrite(SUCCESS_PIN, LOW);

  } else if (customKey == backspaceKey && inputLen > 0) {
    inputLen--;
    input[inputLen] = '\0';
    lcd.setCursor(inputLen, 1);
    lcd.print(' ');
    lcd.setCursor(inputLen, 1);

  }
}

