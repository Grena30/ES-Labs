
#include <stdio.h>
#include <string.h>

#define OUTPUT_PORT 12
#define MAX_INPUT_LENGTH 10
#define LED_ON_MSG "led on"
#define LED_OFF_MSG "led off"
#define BAUD_RATE 4800

int toggleState = LOW;
char input[MAX_INPUT_LENGTH];

void setup() {
  Serial.begin(BAUD_RATE);
  redirectOutput();
  pinMode(OUTPUT_PORT, OUTPUT);
}

void loop() {
  
  // Set all elements to null char
  memset(input, '\0', sizeof(input));
  
  printf("Enter a command: \n");
  
  while (Serial.available() == 0) {
    // Wait for input
  }

  // Read input from serial monitor
  Serial.readBytesUntil('\n', input, sizeof(input));

  // Compare input with one of the known commands
  if (strcmp(input, LED_ON_MSG) == 0) {
    printf("Command received: LED ON\n");
    toggleState = HIGH;
    
  } else if (strcmp(input, LED_OFF_MSG) == 0) {
    printf("Command received: LED OFF\n");
    toggleState = LOW;
    
  } else {
    printf("Unknown command: %s\n", input);

  }
	
  // Update the state of the LED
  digitalWrite(OUTPUT_PORT, toggleState);

  delay(1000);
}