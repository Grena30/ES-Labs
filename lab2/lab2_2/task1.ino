#include "task1.h"
#include <Arduino.h>

bool previousButtonState = LOW;
int task1Offset;
int task1Rec;

void task1_setup(int offset, int rec) {
    task1Offset = offset;
    task1Rec = rec;
    pinMode(OUTPUT_PORT, OUTPUT);
    pinMode(INPUT_PORT, INPUT);
}

void task1_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task1Offset);
  for (;;) {
    buttonState = digitalRead(INPUT_PORT);

    // If the button is pressed and was not pressed previously
    if (buttonState == HIGH && previousButtonState == LOW) {
        ledState = !ledState;
        delay(DELAY_TIME);
    }

    digitalWrite(OUTPUT_PORT, ledState);
    previousButtonState = buttonState;
    vTaskDelay(task1Rec);
  }
}
