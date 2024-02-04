
#define OUTPUT_PORT 12
#define INPUT_PORT 2

int buttonState = 0;
int toggleState = LOW;

void setup()
{
	pinMode(OUTPUT_PORT, OUTPUT);
  pinMode(INPUT_PORT, INPUT);
}

void loop()
{ 
  // Read the value on the INPUT_PORT
	buttonState = digitalRead(INPUT_PORT);
  	
    // If the button is pressed switch the state of the LED
    if (buttonState == HIGH) {
    	toggleState = !toggleState;
      delay(200);
    }

    // Update the state of the LED
  	digitalWrite(OUTPUT_PORT, toggleState);
  
}