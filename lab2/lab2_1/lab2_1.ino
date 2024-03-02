#include <Arduino.h>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task_idle.h"
#include <timer-api.h>


// TODO: Change RECs for smoother interaction
#define REC1 2
#define REC2 1
#define REC3 4

#define OFFSET1 2
#define OFFSET2 0
#define OFFSET3 4

int recCounter1 = OFFSET1;
int recCounter2 = OFFSET2;
int recCounter3 = OFFSET3;

int _timer = TIMER_DEFAULT;

void setup() {
  task1_setup();
  task2_setup();
  task3_setup();
  task_idle_setup();
  
  timer_init_ISR_1KHz(_timer);
}

void loop() {
  // Task 1: 12-16 microseconds
  // Task 2: 8 microseconds
  // Task 3: 16 microseconds
  // timeTakenPerTask();
  // delay(5000);

  task_idle_loop();
}

void timer_handle_interrupts(int timer) {
  if (--recCounter1 <= 0) {
      task1_loop();
      recCounter1 = REC1;
  }

  if (--recCounter2 <= 0) {
      task2_loop();
      recCounter2 = REC2;
  }

  if (--recCounter3 <= 0) {
      task3_loop();
      recCounter3 = REC3;
  }
}

void time_per_task() {
  unsigned long start_time, end_time;
  
  // Measure execution time of task 1
  start_time = micros();
  task1_loop();
  end_time = micros();
  Serial.print("Task 1 execution time: ");
  Serial.println(end_time - start_time);

  // Measure execution time of task 2
  start_time = micros();
  task2_loop();
  end_time = micros();
  Serial.print("Task 2 execution time: ");
  Serial.println(end_time - start_time);

  // Measure execution time of task 3
  start_time = micros();
  task3_loop();
  end_time = micros();
  Serial.print("Task 3 execution time: ");
  Serial.println(end_time - start_time);
}