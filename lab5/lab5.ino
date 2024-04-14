#include <LiquidCrystal_I2C.h>

#define BAUD_RATE 9600
#define INPUT_PIN 7
#define MAX_INPUT_LENGTH 10

// LED
#define LED_SETPOINT_PIN A0
#define LED_OUT_PIN 3

#define LED_SETPOINT_MIN 0
#define LED_SETPOINT_MAX 100

#define ADC_MIN 0
#define ADC_MAX 1023

#define LED_OUT_MIN 3000
#define LED_OUT_MAX 5000

// PWM
#define PWM_MIN 0
#define PWM_MAX 255
#define PWM_VOLTAGE_MIN 0
#define PWM_VOLTAGE_MAx 5000

// Temp sensor
const float BETA = 3950;
#define TEMP_SETPOINT_PIN A1
#define NTC_TEMP_PIN A2
#define TEMP_OUT_PIN 5

#define TEMP_DELTA 1
#define TEMP_MAX 80
#define TEMP_MIN -24

#define TEMP_SETPOINT_MIN 0
#define TEMP_SETPOINT_MAX 50

#define TEMP_VOLTAGE_MAX 500
#define TEMP_VOLTAGE_MIN 2000

#define ADC_VOLTAGE_MIN 0
#define ADC_VOLTAGE_MAX 5000


const int lcdDimensions[2] = {16, 2};
LiquidCrystal_I2C lcd(0x27, lcdDimensions[0], lcdDimensions[1]); 

void lcdInit() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED SetPoint:");
}

int getTemp(int analogValue) {
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_OUT_PIN, OUTPUT);
  lcd.begin(lcdDimensions[0], lcdDimensions[1]);
  lcdInit();
  // redirectOutput();

}

void loop() {
  
  // LED Open loop control
  // Read setpoint
  int LED_SetPointRaw = analogRead(LED_SETPOINT_PIN);

  // Convert to (0 - 100) %
  int LED_SetPoint = map(LED_SetPointRaw, ADC_MIN, ADC_MAX, LED_SETPOINT_MIN, LED_SETPOINT_MAX);

  int LED_OutPWM = map(LED_SetPoint, LED_SETPOINT_MIN, LED_SETPOINT_MAX, PWM_MIN, PWM_MAX);
  analogWrite(LED_OUT_PIN, LED_OutPWM);

  // Temp sensor ON/OFF control
  int TEMP_SetPointRaw = analogRead(TEMP_SETPOINT_PIN);
  // Convert raw to setpoint
  int TEMP_SetPoint = map(TEMP_SetPointRaw, ADC_MIN, ADC_MAX, TEMP_SETPOINT_MIN, TEMP_SETPOINT_MAX);

  // Convert voltage to temp
  int NTC_Raw = analogRead(NTC_TEMP_PIN);
  int NTC_Temp = getTemp(NTC_Raw);


  int TempOut = 0;
  if (TEMP_SetPoint < NTC_Temp - TEMP_DELTA) {
    TempOut = HIGH;
  } else if (TEMP_SetPoint > NTC_Temp + TEMP_DELTA) {
    TempOut = LOW;
  }

  Serial.print("Temperature setpoint: ");
  Serial.print(TEMP_SetPoint);
  Serial.println();
  Serial.print("Actual temperature: ");
  Serial.print(NTC_Temp);
  Serial.println();
  digitalWrite(TEMP_OUT_PIN, TempOut);

  // LCD
  lcdInit();
  lcd.print(LED_SetPoint);
  lcd.setCursor(0, 1);
  lcd.print("TEMP Control:");
  if (TempOut == HIGH) {
    lcd.print("On");
  } else {
    lcd.print("Off");
  }

  Serial.println();

  delay(1000);

}
