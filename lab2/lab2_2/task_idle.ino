#include "task_idle.h"
#include <Arduino.h>

int taskIdleOffset;
int taskIdleRec;

void task_idle_setup(int offset, int rec) {
    taskIdleOffset = offset;
    taskIdleRec = rec;
    Serial.begin(BAUD_RATE);
}

void task_idle_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(taskIdleOffset);
  for (;;) {
    if (previousLedState != ledState) {
        Serial.print("LED State changed to: ");
        Serial.println(ledState);
        previousLedState = ledState;
    }

    if (previousBlinkInterval != blinkInterval) {
        Serial.print("Blink Interval changed to: ");
        Serial.println(blinkInterval);
        previousBlinkInterval = blinkInterval;
    }

    if (previousButton1StateIdle != button1State) {
        if (button1State == HIGH) {
            Serial.println("Button 1 pressed!");
        }
        previousButton1StateIdle = button1State;
    }

    if (previousButton2StateIdle != button2State) {
        if (button2State == HIGH) {
            Serial.println("Button 2 pressed!");
        }
        previousButton2StateIdle = button2State;
    }
    vTaskDelay(taskIdleRec);
  }
}