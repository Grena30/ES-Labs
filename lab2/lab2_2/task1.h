#ifndef task1_h
#define task1_h

#define OUTPUT_PORT 3
#define INPUT_PORT 4
#define DELAY_TIME 0

int buttonState = 0;
extern int ledState = LOW;

void task1_setup(int offset, int rec);
void task1_loop(void *pvParameters);

#endif
