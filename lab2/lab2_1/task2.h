#ifndef task2_h
#define task2_h

#define INTERMITTEN_LED_PORT 2

int previousMillis = 0;
extern int blinkInterval = 1000;

void task2_setup();
void task2_loop();

#endif
