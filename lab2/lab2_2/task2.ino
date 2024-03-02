#include "task2.h"
#include <Arduino.h>

int task2Offset;
int task2Rec;

void task2_setup(int offset, int rec) {
    task2Offset = offset;
    task2Rec = rec;
    pinMode(INTERMITTENT_LED_PORT, OUTPUT);
}

void task2_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task2Offset);
  for (;;) {
    int currentMillis = millis();

    if (!ledState) {
        if (currentMillis - previousMillis >= blinkInterval) {
            // Save the last time the LED was blinked
            previousMillis = currentMillis;

            digitalWrite(INTERMITTENT_LED_PORT, !digitalRead(INTERMITTENT_LED_PORT));
        }
    } else {
        digitalWrite(INTERMITTENT_LED_PORT, LOW);
    }
    vTaskDelay(task2Rec);
  }
}
