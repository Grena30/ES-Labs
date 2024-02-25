#include "task3.h"
#include <Arduino.h>

void task3_setup() {
    pinMode(BUTTON1_PORT, INPUT);
    pinMode(BUTTON2_PORT, INPUT);
}

void task3_loop() {
        button1State = digitalRead(BUTTON1_PORT);
        button2State = digitalRead(BUTTON2_PORT);

        if (button1State == HIGH && previousButton1State == LOW) {
            incrementBlinkValue();
            delay(200);
        }

        previousButton1State = button1State;

        if (button2State == HIGH && previousButton2State == LOW) {
            decrementBlinkValue();
            delay(200);
        }

        previousButton2State = button2State;

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
