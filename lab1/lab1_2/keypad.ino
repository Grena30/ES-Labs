#include <Keypad.h>

const byte rows = 4;
const byte columns = 4;

char keypadArray[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[rows] = {4, 5, 6, 7};
byte columnPins[columns] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keypadArray), rowPins, columnPins, rows, columns);

char getCustomKeypad() {
  return keypad.getKey();
}
