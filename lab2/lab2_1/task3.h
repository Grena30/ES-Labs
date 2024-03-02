#ifndef task3_h
#define task3_h

#define BUTTON1_PORT 5
#define BUTTON2_PORT 6
#define DELAY_TIME 100

int previousButton1State = LOW; 
int previousButton2State = LOW;
int button1State = LOW;
int button2State = LOW;
int maxBlinkInterval = 5000;
int minBlinkInterval = 200;
int blinkIntervalStep = 100;

void task3_setup();
void task3_loop();
void incrementBlinkValue();
void decrementBlinkValue();

#endif