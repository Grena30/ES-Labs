#ifndef task_idle_h
#define task_idle_h

#define BAUD_RATE 9600

int previousBlinkInterval = blinkInterval;
int previousLedState = ledState;
int previousButton1StateIdle = button1State;
int previousButton2StateIdle = button2State;

void task_idle_setup(int offset, int rec);
void task_idle_loop(void *pvParameters);

#endif
