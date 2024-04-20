#include <LiquidCrystal_I2C.h>

#define BAUD_RATE 9600

#define NORTH_REQ_PIN 8
#define EAST_REQ_PIN 9

#define EAST_GREEN_PIN 2
#define EAST_YELLOW_PIN 3
#define EAST_RED_PIN 4

#define NORTH_GREEN_PIN 5
#define NORTH_YELLOW_PIN 6
#define NORTH_RED_PIN 7

#define NONE_REQ 0b00
#define NORTH_REQ 0b01
#define EAST_REQ 0b10
#define BOTH_REQ 0b11

#define GO_NORTH_STATE 0
#define WAIT_NORTH_STATE 1 
#define GO_EAST_STATE 2
#define WAIT_EAST_STATE 3 

#define GO_NORTH_OUT 0b100001
#define WAIT_NORTH_OUT 0b100010
#define GO_EAST_OUT 0b001100
#define WAIT_EAST_OUT 0b010100

#define GO_NORTH_TIME 2000
#define WAIT_NORTH_TIME 2000
#define GO_EAST_TIME 2000
#define WAIT_EAST_TIME 2000

struct State {
  unsigned long Out; // 6-bit pattern to output
  unsigned long Time; // delay in 10ms units
  unsigned long Next[4];
}; // next state for inputs 0,1,2,3

typedef const struct State STyp;

STyp FSM[4]={
{GO_NORTH_OUT, GO_NORTH_TIME,{GO_NORTH_STATE, WAIT_NORTH_STATE, GO_NORTH_STATE, WAIT_NORTH_STATE }},
{WAIT_NORTH_OUT, WAIT_NORTH_TIME, {GO_EAST_STATE, GO_EAST_STATE, GO_EAST_STATE, GO_EAST_STATE }},
{GO_EAST_OUT, GO_EAST_TIME,{GO_EAST_STATE, GO_EAST_STATE, WAIT_EAST_STATE, WAIT_EAST_STATE }},
{WAIT_EAST_OUT, WAIT_EAST_TIME, {GO_NORTH_STATE, GO_NORTH_STATE, GO_NORTH_STATE, GO_NORTH_STATE }}};

int FSM_State = GO_NORTH_STATE;

int GetInput(void) {
  int northButton = digitalRead(NORTH_REQ_PIN);
  int eastButton = digitalRead(EAST_REQ_PIN);
  if (northButton && eastButton)
    return BOTH_REQ;
  else if (eastButton)
    return EAST_REQ;
  else if (northButton)
    return NORTH_REQ;
  else
    return NONE_REQ; 
}

void SetOutput(int out) {
  int ledState;
  ledState = (out & (1 << 5)) ? HIGH : LOW;
  digitalWrite(EAST_RED_PIN, ledState);
  ledState = (out & (1 << 4)) ? HIGH : LOW;
  digitalWrite(EAST_YELLOW_PIN, ledState);
  ledState = (out & (1 << 3)) ? HIGH : LOW;
  digitalWrite(EAST_GREEN_PIN, ledState);
  ledState = (out & (1 << 2)) ? HIGH : LOW;
  digitalWrite(NORTH_RED_PIN, ledState);
  ledState = (out & (1 << 1)) ? HIGH : LOW;
  digitalWrite(NORTH_YELLOW_PIN, ledState);
  ledState = (out & (1 << 0)) ? HIGH : LOW;
  digitalWrite(NORTH_GREEN_PIN, ledState);
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(NORTH_REQ_PIN, INPUT_PULLUP);
  pinMode(EAST_REQ_PIN, INPUT_PULLUP);

  pinMode(EAST_GREEN_PIN, OUTPUT);
  pinMode(EAST_YELLOW_PIN, OUTPUT);
  pinMode(EAST_RED_PIN, OUTPUT);

  pinMode(NORTH_GREEN_PIN, OUTPUT);
  pinMode(NORTH_YELLOW_PIN, OUTPUT);
  pinMode(NORTH_RED_PIN, OUTPUT);

  FSM_State = GO_NORTH_STATE;
}

void loop() {
  int FSM_Output = FSM[FSM_State].Out;
  SetOutput(FSM_Output);
  delay(FSM[FSM_State].Time);

  int FSM_Inputs = GetInput();
  FSM_State = FSM[FSM_State].Next[FSM_Inputs];
}
