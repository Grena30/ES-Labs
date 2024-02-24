#include "task2.h"
#include "task3.h"
#include <Arduino.h>

void task3_setup()
{
    pinMode(BUTTON1_PORT, INPUT);
    pinMode(BUTTON2_PORT, INPUT);
}

void task3_loop()
{
    int currentMillis = millis();

    if (currentMillis - lastButtonPressTime >= debounceDelay){
        button1State = digitalRead(BUTTON1_PORT);
        button2State = digitalRead(BUTTON2_PORT);

        if (button1State == HIGH && previousButton1State == LOW)
        {
            incrementBlinkValue();
        }

        previousButton1State = button1State;

        if (button2State == HIGH && previousButton2State == LOW)
        {
            decrementBlinkValue();
        }

        previousButton2State = button2State;

        lastButtonPressTime = currentMillis;
    }
}

void incrementBlinkValue()
{
    if (blinkInterval < 5000) {
      blinkInterval += 100;
    }
}

void decrementBlinkValue()
{
    if (blinkInterval > 200){ 
      blinkInterval -= 100;
    }
}
