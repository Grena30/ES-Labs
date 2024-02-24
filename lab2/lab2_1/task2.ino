#include "task2.h"
#include <Arduino.h>

void task2_setup() {
    pinMode(INTERMITTEN_LED_PORT, OUTPUT);
}

void task2_loop() {
    int currentMillis = millis();

    if (!ledState) {
        if (currentMillis - previousMillis >= blinkInterval) {
            // Save the last time the LED was blinked
            previousMillis = currentMillis;

            digitalWrite(INTERMITTEN_LED_PORT, !digitalRead(INTERMITTEN_LED_PORT));
        }
    } else {
        digitalWrite(INTERMITTEN_LED_PORT, LOW);
    }
}
