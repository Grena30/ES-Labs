#ifndef task3_h
#define task3_h

#define BUTTON1_PORT 5
#define BUTTON2_PORT 6

int lastButtonPressTime = 0;
int debounceDelay = 50;
int previousButton1State = LOW; 
int previousButton2State = LOW;
int button1State = LOW;
int button2State = LOW;

void task3_setup();
void task3_loop();
void incrementBlinkValue();
void dcrementBlinkValue();

#endif