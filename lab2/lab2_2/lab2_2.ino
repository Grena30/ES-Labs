#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task_idle.h"
#include <Arduino_FreeRTOS.h>

// TODO: Change RECs for smoother interaction

#define REC1 2
#define REC2 1
#define REC3 4
#define REC_IDLE 1

#define OFFSET1 2
#define OFFSET2 2
#define OFFSET3 4
#define OFFSET_IDLE 1

int recCounter1 = OFFSET1;
int recCounter2 = OFFSET2;
int recCounter3 = OFFSET3;
int recCounterIdle = OFFSET_IDLE;

void setup() {
  task1_setup(recCounter1, REC1);
  task2_setup(recCounter2, REC2);
  task3_setup(recCounter3, REC3);
  task_idle_setup(recCounterIdle, REC_IDLE);

  xTaskCreate(
    task1_loop
    ,  "ToggleLED" // Name
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority, (0 - 3)
    ,  NULL );

    xTaskCreate(
    task2_loop
    ,  "BlinkLED"
    ,  128
    ,  NULL
    ,  1
    ,  NULL );

    xTaskCreate(
    task3_loop
    ,  "ButtonBlink"
    ,  128  
    ,  NULL
    ,  2
    ,  NULL );

    xTaskCreate(
    task_idle_loop
    ,  "Idle"   
    ,  128
    ,  NULL
    ,  0
    ,  NULL );
  
}

void loop() {

}
