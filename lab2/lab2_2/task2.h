#ifndef task2_h
#define task2_h

#define INTERMITTENT_LED_PORT 2

int previousMillis = 0;
extern int blinkInterval = 1000;

void task2_setup(int offset, int rec);
void task2_loop(void *pvParameters);

#endif
