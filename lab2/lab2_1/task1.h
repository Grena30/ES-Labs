#ifndef task1_h
#define task1_h

#define OUTPUT_PORT 3
#define INPUT_PORT 4

int buttonState = 0;
extern int ledState = LOW;

void task1_setup();
void task1_loop();

#endif
