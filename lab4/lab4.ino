#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define enA 10
#define in1 7
#define in2 6
#define INPUT_PIN 9
#define LCD_ADDRESS 32
#define BAUD_RATE 9600
#define MAX_INPUT_LENGTH 10
#define LED_ON "relay on"
#define LED_OFF "relay off"

String input;
const int defaultSpeed = 255;
const int minSpeed = -100;
const int nullSpeed = 0;
const int maxSpeed = 100;
const int lcdDimensions[2] = {16, 2};
const float normalizeFactor = 0.01;

LiquidCrystal_I2C lcd(LCD_ADDRESS, lcdDimensions[0], lcdDimensions[1]);
FILE f_out;
int sput(char c, __attribute__((unused)) FILE* f) {return !Serial.write(c);}

class LCDController {
public:

  void init() {
    lcd.begin(lcdDimensions[0],lcdDimensions[1]);
    lcd.init();
    lcd.backlight();
    displayInitialMessage();
  }
  
  void displayInitialMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter the speed");
  }
  
  void displaySpeed(int speed) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed set to: ");
    lcd.setCursor(0, 1);
    lcd.print(speed);
    lcd.print("%");
    delay(300);
    displayInitialMessage();
  }

  void displayErrorMessage() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Out of range!");
    lcd.setCursor(0, 1);
    lcd.print("Range:-100...100");
    delay(300);
    displayInitialMessage();
  }
};

class L293DController {
public:
  
  void init() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
  }
  
  void setCounterClockwiseSpeed(int speed) {
    analogWrite(enA, (speed * normalizeFactor) * defaultSpeed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  void setClockwiseSpeed(int speed) {
    analogWrite(enA, (abs(speed) * normalizeFactor) * defaultSpeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  
};

class MotorController {
public:

  L293DController driverController;
  
  void init() {
    driverController.init();
  }
  
  void changeSpeed(int speed) {
    if (speed >= 0){
    	driverController.setCounterClockwiseSpeed(speed);
    } else if (speed < 0){
    	driverController.setClockwiseSpeed(speed);
    }
  }
};

MotorController motorController;
LCDController lcdController;

void redirectOutput(){
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);
  stdout = &f_out;
}

void setup() {
  pinMode(INPUT_PIN, OUTPUT);
  motorController.init();
  Serial.begin(BAUD_RATE);
  lcdController.init();
  redirectOutput();
  printf("Help:\n");
  printf("relay on - turns the Relay on\n");
  printf("relay off - turns the Relay off\n");
  printf("Speed range from -100 to +100\n");
  printf("Write any number within the range\n");
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();
    if (input == LED_ON) {
    	printf("Command received: LED ON\n");
      	digitalWrite(INPUT_PIN, HIGH);
    } else if (input == LED_OFF) {
     	printf("Command received: LED OFF\n");
      	digitalWrite(INPUT_PIN, LOW);
    } else {
      int speed = input.toInt();
      if (speed >= nullSpeed && speed <= maxSpeed) {
        motorController.changeSpeed(speed);
        lcdController.displaySpeed(speed);

      } else if (speed >= minSpeed && speed <= nullSpeed) {
        motorController.changeSpeed(speed);
        lcdController.displaySpeed(speed);

      } else {
        lcdController.displayErrorMessage();
      }
    }
  }
}