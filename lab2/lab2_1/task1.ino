#include "task1.h"
#include <Arduino.h>

bool previousButtonState = LOW;

void task1_setup() {
    pinMode(OUTPUT_PORT, OUTPUT);
    pinMode(INPUT_PORT, INPUT);
}

void task1_loop() {
    buttonState = digitalRead(INPUT_PORT);

    // If the button is pressed and was not pressed previously
    if (buttonState == HIGH && previousButtonState == LOW) {
        ledState = !ledState;
        delay(DELAY_TIME);
    }

    digitalWrite(OUTPUT_PORT, ledState);
    previousButtonState = buttonState;
}
