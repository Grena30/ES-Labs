#include "task3.h"
#include <Arduino.h>

int task3Offset;
int task3Rec;

void task3_setup(int offset, int rec) {
    task3Offset = offset;
    task3Rec = rec;
    pinMode(BUTTON1_PORT, INPUT);
    pinMode(BUTTON2_PORT, INPUT);
}

void task3_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task3Offset);
  for (;;) {
        button1State = digitalRead(BUTTON1_PORT);
        button2State = digitalRead(BUTTON2_PORT);

        if (button1State == HIGH && previousButton1State == LOW) {
            incrementBlinkValue();
            delay(DELAY_TIME);
        }

        previousButton1State = button1State;

        if (button2State == HIGH && previousButton2State == LOW) {
            decrementBlinkValue();
            delay(DELAY_TIME);
        }

        previousButton2State = button2State;
        vTaskDelay(task3Rec);   
  }
}

void incrementBlinkValue() {
    if (blinkInterval < maxBlinkInterval) {
      blinkInterval += blinkIntervalStep;
    }
}

void decrementBlinkValue() {
    if (blinkInterval > minBlinkInterval) { 
      blinkInterval -= blinkIntervalStep;
    }
}

